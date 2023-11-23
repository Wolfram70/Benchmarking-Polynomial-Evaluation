#include <chrono>
#include <iostream>
#include <random>
#include <stdint.h>
#include <vector>

extern double evaluate_naive(const std::vector<uint64_t> &coefficients,
                             double x);
extern double evaluate_horner(const std::vector<uint64_t> &coefficients,
                              double x);
extern double evaluate_parallel(std::vector<uint64_t> &coefficients, double x);
extern int NUM_PROCS;

int main() {
  std::vector<uint64_t> coefficients(1000000, 1);
  // Initialising the coefficients vector with random integers between -100 and
  // 100
  std::cout << "Generating random coefficients..." << std::endl;
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);
  for (int i = 0; i < coefficients.size(); i++)
    coefficients[i] = dis(gen);
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::cout << "Done! ("
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << "ms)" << std::endl
            << std::endl;
  double x = 0.96f;

  // Benchmarking all three methods of polynomial evaluation for different
  // values of NUM_PROCS and pretty tabulating the results
  std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+"
            << std::endl;
  std::cout << "|"
            << "No. Threads" << std::string(15 - 11, ' ') << "|"
            << "Naive" << std::string(15 - 5, ' ') << "|"
            << "Horner" << std::string(15 - 6, ' ') << "|"
            << "Parallel" << std::string(15 - 8, ' ') << "|" << std::endl;
  std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+"
            << std::endl;
  for (int i = 1; i <= 16; i++) {
    // Generate a random double x between 0.5 and 0.95
    std::uniform_real_distribution<> dis(0.5, 0.95);
    x = dis(gen);

    NUM_PROCS = i;
    auto start = std::chrono::high_resolution_clock::now();
    evaluate_naive(coefficients, x);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> naive_time = end - start;
    int naive_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(naive_time)
            .count();

    start = std::chrono::high_resolution_clock::now();
    evaluate_horner(coefficients, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> horner_time = end - start;
    int horner_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(horner_time)
            .count();

    start = std::chrono::high_resolution_clock::now();
    evaluate_parallel(coefficients, x);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallel_time = end - start;
    int parallel_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(parallel_time)
            .count();

    std::cout
        << "|" << NUM_PROCS
        << std::string(15 - std::to_string(NUM_PROCS).length(), ' ') << "|"
        << naive_time_ms << "ms"
        << std::string(15 - std::to_string(naive_time_ms).length() - 2, ' ')
        << "|" << horner_time_ms << "ms"
        << std::string(15 - std::to_string(horner_time_ms).length() - 2, ' ')
        << "|" << parallel_time_ms << "ms"
        << std::string(15 - std::to_string(parallel_time_ms).length() - 2, ' ')
        << "|" << std::endl;
  }
  std::cout << "+" << std::string(15, '-') << "+" << std::string(15, '-') << "+"
            << std::string(15, '-') << "+" << std::string(15, '-') << "+"
            << std::endl;
  return 0;
}