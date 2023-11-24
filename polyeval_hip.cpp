#include <chrono>
#include <hip/hip_runtime.h>
#include <vector>
#include <iostream>

int NUM_GPU_PROCS = 4096; // Update the value as needed

#define HIP_CHECK(error)                                                       \
  if (error != hipSuccess) {                                                   \
    std::cerr << "HIP error: " << hipGetErrorString(error) << " at line "      \
              << __LINE__ << std::endl;                                        \
    exit(EXIT_FAILURE);                                                        \
  }

__global__ void preComputeKernel(const uint64_t *coefficients,
                                 double *pre_compute, int n, double x) {
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  if (i <= n / 2) {
    pre_compute[i] = coefficients[2 * i] + x * coefficients[2 * i + 1];
  } else {
    pre_compute[i] = 0;
  }
}

__global__ void evaluateKernel(const double *pre_compute, double *part_solns,
                               int n, double x_new, int NUM_GPU_PROCS) {
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  if (i < NUM_GPU_PROCS) {
    int t = n / (2 * NUM_GPU_PROCS);
    double result = pre_compute[NUM_GPU_PROCS * t + i];
    for (int j = (n / (2 * NUM_GPU_PROCS)) - 1; j >= 0; j--) {
      result = result * x_new + pre_compute[j * NUM_GPU_PROCS + i];
    }
    part_solns[i] = result;
  }
}

__global__ void reduceKernel(const double *part_solns,
                             const double *even_powers, double *f_result,
                             int NUM_GPU_PROCS) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i < NUM_GPU_PROCS)
    atomicAdd(f_result, part_solns[i] * even_powers[i]);
}

double evaluate_parallel_hip(std::vector<uint64_t> &coefficients, double x,
                             int &time_lost) {
  int n = coefficients.size() - 1;
  coefficients.push_back(0);

  std::vector<double> even_powers(NUM_GPU_PROCS + 1, 0);
  even_powers[0] = 1;
  double init = x * x;
  for (int i = 1; i <= NUM_GPU_PROCS; ++i)
    even_powers[i] = even_powers[i - 1] * init;

  // Allocate device memory
  uint64_t *d_coefficients;
  double *d_pre_compute;
  double *d_part_solns;
  double *d_even_powers;
  double *d_f_result;

  HIP_CHECK(hipMalloc(&d_coefficients, coefficients.size() * sizeof(uint64_t)));
  HIP_CHECK(hipMalloc(&d_pre_compute, n * sizeof(double)));
  HIP_CHECK(hipMalloc(&d_part_solns, NUM_GPU_PROCS * sizeof(double)));
  HIP_CHECK(hipMalloc(&d_even_powers, (NUM_GPU_PROCS + 1) * sizeof(double)));
  HIP_CHECK(hipMalloc(&d_f_result, sizeof(double)));

  // Transfer data to the device
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  HIP_CHECK(hipMemcpy(d_coefficients, coefficients.data(),
                      coefficients.size() * sizeof(uint64_t),
                      hipMemcpyHostToDevice));
  HIP_CHECK(hipMemcpy(d_even_powers, even_powers.data(),
                      (NUM_GPU_PROCS + 1) * sizeof(double),
                      hipMemcpyHostToDevice));
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> transfer_time = end - start;
  time_lost =
      std::chrono::duration_cast<std::chrono::milliseconds>(transfer_time)
          .count();

  // Launch pre-compute kernel
  hipLaunchKernelGGL(preComputeKernel, dim3((n + 255) / 256), dim3(256), 0, 0,
                     d_coefficients, d_pre_compute, n, x);
  HIP_CHECK(hipDeviceSynchronize());

  // Launch evaluate kernel
  double x_new = even_powers[NUM_GPU_PROCS];
  hipLaunchKernelGGL(evaluateKernel, dim3((NUM_GPU_PROCS + 255) / 256),
                     dim3(256), 0, 0, d_pre_compute, d_part_solns, n, x_new,
                     NUM_GPU_PROCS);
  HIP_CHECK(hipDeviceSynchronize());

  // Launch reduction kernel
  hipLaunchKernelGGL(reduceKernel, dim3((NUM_GPU_PROCS + 255) / 256), dim3(256),
                     0, 0, d_part_solns, d_even_powers, d_f_result,
                     NUM_GPU_PROCS);
  HIP_CHECK(hipDeviceSynchronize());

  // Transfer result back to host
  double f_result;
  HIP_CHECK(
      hipMemcpy(&f_result, d_f_result, sizeof(double), hipMemcpyDeviceToHost));

  // Cleanup
  coefficients.pop_back();
  HIP_CHECK(hipFree(d_coefficients));
  HIP_CHECK(hipFree(d_pre_compute));
  HIP_CHECK(hipFree(d_part_solns));
  HIP_CHECK(hipFree(d_even_powers));
  HIP_CHECK(hipFree(d_f_result));

  return f_result;
}