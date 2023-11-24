# Benchmarking-Polynomial-Evaluation
Benchmarking different polynomial evaluation algorithms: Naive evalulation, Horner's method, and a parallel algorithm from "Optimal Algorithms for Parallel Polynomial Evaluation", Munro et al.

## Results
The benchmark is performed by evaluating a polynomials of very high degrees (100,000 - 100,000,000) at random points. The evaluation is performed with different number of threads (different number for CPU and GPU) for parallelization to see the effects of the number of processors on the parallel algorithm.
<br><br>
The benchmark is performed on a machine with the following specifications:
<br>
<b>CPU:</b> AMD Ryzen 7 5800H <i>(8 cores, 16 threads)</i><br>
<b>GPU:</b> Radeon RX 6700M

<i>Note on terminology:</i> <b><i>ROCM-WT</i></b> includes the time taken by the <code>hipMemcpy()</code> function calls while <b><i>ROCM-WOT</i></b> does not.
<br><br>
<i>Note:</i> Both OpenMP and ROCM implement the same parallel algorithm (Algorithm B from [Munro et al.]).

### Benchmark 1 (Polynomial Degree 10<sup>5</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) | Naive | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:-----:|:------:|:------------:|:-------------:|:--------------:|
|    0.80   |        1        |        1        |  2ms  |   0ms  |      0ms      |     1201ms     |     1053ms     |
|    0.64   |        2        |        2        |  1ms  |   0ms  |      0ms      |      3ms      |       3ms      |
|    0.92   |        3        |        4        |  1ms  |   0ms  |      0ms      |      4ms      |       4ms      |
|    0.77   |        4        |        8        |  1ms  |   0ms  |      0ms      |      3ms      |       3ms      |
|    0.78   |        5        |       16        |  1ms  |   0ms  |      0ms      |      2ms      |       2ms      |
|    0.90   |        6        |       32        |  1ms  |   0ms  |      0ms      |      1ms      |       1ms      |
|    0.84   |        7        |       64        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.60   |        8        |      128        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.88   |        9        |      256        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.60   |       10        |      512        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.51   |       11        |     1024        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.69   |       12        |     2048        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.62   |       13        |     4096        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.66   |       14        |     8192        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.67   |       15        |    16384        |  1ms  |   0ms  |      0ms      |      0ms      |       0ms      |
|    0.74   |       16        |    32768        |  1ms  |   0ms  |      0ms      |      2ms      |       2ms      |


### Benchmark 2 (Polynomial Degree 10<sup>6</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) |  Naive | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:------:|:------:|:------------:|:-------------:|:--------------:|
|   0.59    |        1        |        1        |  17ms  |   1ms  |      5ms      |      40ms      |      39ms      |
|   0.74    |        2        |        2        |  16ms  |   1ms  |      1ms      |      18ms      |      17ms      |
|   0.72    |        3        |        4        |  16ms  |   1ms  |      1ms      |      12ms      |      11ms      |
|   0.77    |        4        |        8        |  16ms  |   1ms  |      1ms      |       8ms      |       7ms      |
|   0.73    |        5        |       16        |  16ms  |   1ms  |      1ms      |       7ms      |       6ms      |
|   0.86    |        6        |       32        |  18ms  |   1ms  |      1ms      |       4ms      |       3ms      |
|   0.58    |        7        |       64        |  18ms  |   1ms  |      1ms      |       2ms      |       1ms      |
|   0.94    |        8        |      128        |  16ms  |   1ms  |      1ms      |       2ms      |       1ms      |
|   0.54    |        9        |      256        |  16ms  |   1ms  |      1ms      |       1ms      |       0ms      |
|   0.89    |       10        |      512        |  17ms  |   1ms  |      1ms      |       1ms      |       0ms      |
|   0.89    |       11        |     1024        |  16ms  |   1ms  |      1ms      |       1ms      |       0ms      |
|   0.65    |       12        |     2048        |  17ms  |   1ms  |      1ms      |       1ms      |       0ms      |
|   0.93    |       13        |     4096        |  15ms  |   1ms  |      1ms      |       1ms      |       0ms      |
|   0.73    |       14        |     8192        |  16ms  |   1ms  |      1ms      |       2ms      |       1ms      |
|   0.61    |       15        |    16384        |  17ms  |   1ms  |      1ms      |       1ms      |       0ms      |
|   0.84    |       16        |    32768        |  15ms  |   1ms  |      1ms      |       1ms      |       0ms      |


### Benchmark 3 (Polynomial Degree 10<sup>7</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) |  Naive | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:------:|:------:|:------------:|:-------------:|:--------------:|
|   0.67    |        1        |        1        | 162ms  |  13ms  |      55ms      |     441ms      |     426ms      |
|   0.93    |        2        |        2        | 148ms  |  13ms  |      33ms      |     315ms      |     304ms      |
|   0.73    |        3        |        4        | 157ms  |  13ms  |      33ms      |     244ms      |     233ms      |
|   0.80    |        4        |        8        | 162ms  |  13ms  |      34ms      |     217ms      |     206ms      |
|   0.70    |        5        |       16        | 162ms  |  13ms  |      33ms      |     199ms      |     188ms      |
|   0.89    |        6        |       32        | 147ms  |  13ms  |      34ms      |     104ms      |      93ms      |
|   0.85    |        7        |       64        | 163ms  |  13ms  |      35ms      |      57ms      |      46ms      |
|   0.93    |        8        |      128        | 164ms  |  13ms  |      38ms      |      28ms      |      17ms      |
|   0.92    |        9        |      256        | 133ms  |  13ms  |      38ms      |      20ms      |       9ms      |
|   0.66    |       10        |      512        | 163ms  |  13ms  |      39ms      |      16ms      |       5ms      |
|   0.60    |       11        |     1024        | 165ms  |  13ms  |      39ms      |      14ms      |       3ms      |
|   0.81    |       12        |     2048        | 165ms  |  13ms  |      40ms      |      13ms      |       2ms      |
|   0.52    |       13        |     4096        | 146ms  |  13ms  |      40ms      |      13ms      |       2ms      |
|   0.79    |       14        |     8192        | 158ms  |  13ms  |      40ms      |      13ms      |       2ms      |
|   0.87    |       15        |    16384        | 140ms  |  13ms  |      40ms      |      13ms      |       2ms      |
|   0.81    |       16        |    32768        | 174ms  |  13ms  |      41ms      |      13ms      |       2ms      |

### Benchmark 4 (Polynomial Degree 10<sup>8</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) |   Naive  |  Horner  | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:--------:|:--------:|:------------:|:-------------:|:--------------:|
|   0.92    |        1        |        1        | 1622ms  |  136ms  |     563ms     |     5130ms     |     4980ms     |
|   0.83    |        2        |        2        | 1631ms  |  136ms  |     333ms     |     3845ms     |     3733ms     |
|   0.89    |        3        |        4        | 1616ms  |  137ms  |     336ms     |     3112ms     |     3000ms     |
|   0.90    |        4        |        8        | 1618ms  |  137ms  |     335ms     |     2898ms     |     2786ms     |
|   0.72    |        5        |       16        | 1617ms  |  137ms  |     336ms     |     2686ms     |     2574ms     |
|   0.88    |        6        |       32        | 1663ms  |  138ms  |     344ms     |     1457ms     |     1345ms     |
|   0.92    |        7        |       64        | 1640ms  |  137ms  |     382ms     |      718ms     |      606ms     |
|   0.87    |        8        |      128        | 1651ms  |  138ms  |     404ms     |      386ms     |      274ms     |
|   0.91    |        9        |      256        | 1642ms  |  137ms  |     415ms     |      223ms     |      111ms     |
|   0.91    |       10        |      512        | 1666ms  |  137ms  |     422ms     |      151ms     |       39ms     |
|   0.66    |       11        |     1024        | 1631ms  |  137ms  |     428ms     |      134ms     |       22ms     |
|   0.73    |       12        |     2048        | 1609ms  |  137ms  |     433ms     |      128ms     |       16ms     |
|   0.65    |       13        |     4096        | 1660ms  |  138ms  |     437ms     |      124ms     |       12ms     |
|   0.76    |       14        |     8192        | 1680ms  |  138ms  |     440ms     |      123ms     |       11ms     |
|   0.54    |       15        |    16384        | 1656ms  |  137ms  |     441ms     |      123ms     |       11ms     |
|   0.81    |       16        |    32768        | 1635ms  |  137ms  |     435ms     |      123ms     |       11ms     |
