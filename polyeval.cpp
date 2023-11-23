#include <math.h>
#include <omp.h>
#include <stdint.h>
#include <vector>

int NUM_PROCS = 1;

double evaluate_naive(const std::vector<uint64_t> &coefficients, double x) {
  double result = 0.0f;
  for (int i = 0; i < coefficients.size(); ++i)
    result += coefficients[i] * pow(x, i);
  return result;
}

double evaluate_horner(const std::vector<uint64_t> &coefficients, double x) {
  double result = 0.0f;
  for (int i = coefficients.size() - 1; i >= 0; --i)
    result = result * x + coefficients[i];
  return result;
}

double evaluate_parallel(std::vector<uint64_t> &coefficients, double x) {
  int n = coefficients.size() - 1;
  coefficients.push_back(0);

  std::vector<double> even_powers(NUM_PROCS + 1, 0);
  even_powers[0] = 1;
  double init = x * x;
  for (int i = 1; i <= NUM_PROCS; ++i)
    even_powers[i] = even_powers[i - 1] * init;

  std::vector<double> pre_compute(n, 0);
#pragma omp parallel for num_threads(NUM_PROCS)
  for (int i = 0; i <= n / 2; ++i) {
    pre_compute[i] = coefficients[2 * i] + x * coefficients[2 * i + 1];
  }

  std::vector<double> part_solns(NUM_PROCS, 0);
  double x_new = even_powers[NUM_PROCS];
  double t, result;
#pragma omp parallel for num_threads(NUM_PROCS) private(t, result)
  for (int i = 0; i < NUM_PROCS; i++) {
    t = n / (2 * NUM_PROCS);
    result = pre_compute[NUM_PROCS * t + i];
    for (int j = (n / (2 * NUM_PROCS)) - 1; j >= 0; j--) {
      result = result * x_new + pre_compute[j * NUM_PROCS + i];
    }
    part_solns[i] = result;
  }

  double f_result = 0.0f;
#pragma omp parallel for num_threads(NUM_PROCS) reduction(+ : f_result)
  for (int i = 0; i < NUM_PROCS; i++)
    f_result += part_solns[i] * even_powers[i];

  coefficients.pop_back();
  return f_result;
}