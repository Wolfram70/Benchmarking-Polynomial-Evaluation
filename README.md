# Benchmarking-Polynomial-Evaluation
Benchmarking different polynomial evaluation algorithms: Naive evalulation, Horner's method, and a parallel algorithm from "Optimal Algorithms for Parallel Polynomial Evaluation", Munro et al.

## Results
The benchmark is performed by evaluating a polynomial of degree 1,000,000 at random points. The evaluation is performed with different number of threads (up till a limit of the number of cores tested on) for parallelization to see the effects of the number of processors on the parallel algorithm.

| No. of Threads|    Naive      |    Horner     |   Parallel    |
|:-------------:|:-------------:|:-------------:|:-------------:|
|       1       |     37ms      |      7ms      |     18ms      |
|       2       |     37ms      |      7ms      |      7ms      |
|       3       |     37ms      |      7ms      |      6ms      |
|       4       |     37ms      |      7ms      |      5ms      |
|       5       |     37ms      |      7ms      |      5ms      |
|       6       |     38ms      |      7ms      |      4ms      |
|       7       |     38ms      |      7ms      |      4ms      |
|       8       |     38ms      |      7ms      |      3ms      |
|       9       |     37ms      |      7ms      |      4ms      |
|      10       |     38ms      |      7ms      |      3ms      |
|      11       |     37ms      |      7ms      |      3ms      |
|      12       |     37ms      |      7ms      |      3ms      |
|      13       |     37ms      |      7ms      |      2ms      |
|      14       |     38ms      |      7ms      |      2ms      |
|      15       |     37ms      |      7ms      |      2ms      |
|      16       |     37ms      |      7ms      |      3ms      |
