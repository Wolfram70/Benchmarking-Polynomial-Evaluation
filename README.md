# Benchmarking-Polynomial-Evaluation
Benchmarking different polynomial evaluation algorithms: Naive evalulation, Horner's method, and a parallel algorithm from "Optimal Algorithms for Parallel Polynomial Evaluation", Munro et al.

## Results
The benchmark is performed by evaluating a polynomials of very high degrees (100,000 - 100,000,000) at random points. The evaluation is performed with different number of threads (different number for CPU and GPU) for parallelization to see the effects of the number of processors on the parallel algorithm.
<br><br>
The benchmark is performed on a machine with the following specifications:
<br>
<b>CPU:</b> AMD Ryzen 7 5800H <i>(8 cores, 16 threads)</i><br>
<b>GPU:</b> Radeon RX 6700M

<i>Note on terminology:</i> <b><i>ROCM-WT</i></b> includes the time taken by the <code>hipMemcpy()</code> function calls while <b><i>ROCM-WOT</i></b> does not. <b><i>EvalPoint</i></b> is the point at which the random polynomial was evaluated to measure the time taken.
<br><br>
<i>Note:</i> Both OpenMP and ROCM implement the same parallel algorithm (Algorithm B from [Munro et al.]).

### Benchmark 1 (Polynomial Degree 10<sup>5</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) | Naive | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:-----:|:------:|:------------:|:-------------:|:--------------:|
|   0.66    |        1        |        1        |  3ms  |   0ms  |      2ms      |     1206ms     |     1048ms     |
|   0.85    |        2        |        2        |  3ms  |   0ms  |      0ms      |       8ms      |       8ms      |
|   0.63    |        3        |        4        |  3ms  |   0ms  |      0ms      |       5ms      |       5ms      |
|   0.81    |        4        |        8        |  3ms  |   0ms  |      0ms      |       3ms      |       3ms      |
|   0.69    |        5        |       16        |  3ms  |   0ms  |      0ms      |       2ms      |       2ms      |
|   0.75    |        6        |       32        |  3ms  |   0ms  |      0ms      |       1ms      |       1ms      |
|   0.59    |        7        |       64        |  3ms  |   0ms  |      0ms      |       1ms      |       1ms      |
|   0.89    |        8        |      128        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.86    |        9        |      256        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.79    |       10        |      512        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.72    |       11        |     1024        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.51    |       12        |     2048        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.86    |       13        |     4096        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.82    |       14        |     8192        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.84    |       15        |    16384        |  3ms  |   0ms  |      0ms      |       0ms      |       0ms      |
|   0.52    |       16        |    32768        |  3ms  |   0ms  |      2ms      |       1ms      |       1ms      |


### Benchmark 2 (Polynomial Degree 10<sup>6</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) |  Naive | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:------:|:------:|:------------:|:-------------:|:--------------:|
|   0.55    |        1        |        1        |  31ms  |   6ms  |     16ms      |      70ms      |      68ms      |
|   0.60    |        2        |        2        |  32ms  |   5ms  |      4ms      |      18ms      |      17ms      |
|   0.64    |        3        |        4        |  32ms  |   5ms  |      3ms      |      12ms      |      11ms      |
|   0.52    |        4        |        8        |  32ms  |   5ms  |      3ms      |       8ms      |       7ms      |
|   0.89    |        5        |       16        |  32ms  |   6ms  |      2ms      |       7ms      |       6ms      |
|   0.81    |        6        |       32        |  32ms  |   5ms  |      2ms      |       4ms      |       3ms      |
|   0.77    |        7        |       64        |  33ms  |   6ms  |      2ms      |       3ms      |       2ms      |
|   0.89    |        8        |      128        |  33ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.64    |        9        |      256        |  33ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.80    |       10        |      512        |  31ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.92    |       11        |     1024        |  31ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.61    |       12        |     2048        |  31ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.84    |       13        |     4096        |  32ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.74    |       14        |     8192        |  32ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.77    |       15        |    16384        |  32ms  |   6ms  |      2ms      |       2ms      |       1ms      |
|   0.50    |       16        |    32768        |  33ms  |   6ms  |      2ms      |       2ms      |       1ms      |


### Benchmark 3 (Polynomial Degree 10<sup>7</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) |  Naive | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:------:|:------:|:------------:|:-------------:|:--------------:|
|   0.77    |        1        |        1        | 308ms  |  55ms  |    133ms      |      447ms     |      429ms     |
|   0.64    |        2        |        2        | 308ms  |  55ms  |     62ms      |      314ms     |      303ms     |
|   0.72    |        3        |        4        | 308ms  |  55ms  |     53ms      |      242ms     |      231ms     |
|   0.86    |        4        |        8        | 309ms  |  55ms  |     49ms      |      212ms     |      201ms     |
|   0.58    |        5        |       16        | 307ms  |  56ms  |     48ms      |      195ms     |      184ms     |
|   0.76    |        6        |       32        | 308ms  |  55ms  |     48ms      |      103ms     |       92ms     |
|   0.63    |        7        |       64        | 314ms  |  55ms  |     48ms      |       58ms     |       47ms     |
|   0.91    |        8        |      128        | 319ms  |  55ms  |     48ms      |       25ms     |       14ms     |
|   0.73    |        9        |      256        | 322ms  |  55ms  |     48ms      |       19ms     |        8ms     |
|   0.76    |       10        |      512        | 314ms  |  55ms  |     48ms      |       16ms     |        5ms     |
|   0.53    |       11        |     1024        | 313ms  |  55ms  |     35ms      |       14ms     |        3ms     |
|   0.89    |       12        |     2048        | 315ms  |  55ms  |     34ms      |       14ms     |        3ms     |
|   0.59    |       13        |     4096        | 315ms  |  55ms  |     34ms      |       13ms     |        2ms     |
|   0.90    |       14        |     8192        | 317ms  |  55ms  |     35ms      |       13ms     |        2ms     |
|   0.60    |       15        |    16384        | 317ms  |  55ms  |     34ms      |       13ms     |        2ms     |
|   0.88    |       16        |    32768        | 319ms  |  56ms  |     34ms      |       13ms     |        2ms     |

### Benchmark 4 (Polynomial Degree 10<sup>8</sup>)

| EvalPoint | ThreadNum (CPU) | ThreadNum (GPU) |  Naive  | Horner | OpenMP (CPU) | ROCM-WT (GPU) | ROCM-WOT (GPU) |
|:---------:|:---------------:|:---------------:|:-------:|:------:|:------------:|:-------------:|:--------------:|
|   0.57    |        1        |        1        | 3078ms  | 554ms  |    1105ms     |      5148ms    |      4987ms    |
|   0.76    |        2        |        2        | 3070ms  | 555ms  |     558ms     |      3842ms    |      3729ms    |
|   0.80    |        3        |        4        | 3071ms  | 555ms  |     459ms     |      3114ms    |      3001ms    |
|   0.79    |        4        |        8        | 3076ms  | 558ms  |     403ms     |      2895ms    |      2782ms    |
|   0.54    |        5        |       16        | 3080ms  | 556ms  |     374ms     |      2705ms    |      2592ms    |
|   0.55    |        6        |       32        | 3083ms  | 558ms  |     352ms     |      1494ms    |      1381ms    |
|   0.88    |        7        |       64        | 3077ms  | 556ms  |     338ms     |       724ms    |       611ms    |
|   0.86    |        8        |      128        | 3088ms  | 556ms  |     327ms     |       397ms    |       284ms    |
|   0.63    |        9        |      256        | 3076ms  | 557ms  |     361ms     |       232ms    |       119ms    |
|   0.89    |       10        |      512        | 3086ms  | 558ms  |     350ms     |       157ms    |        44ms    |
|   0.61    |       11        |     1024        | 3081ms  | 557ms  |     343ms     |       136ms    |        23ms    |
|   0.87    |       12        |     2048        | 3084ms  | 556ms  |     336ms     |       129ms    |        16ms    |
|   0.92    |       13        |     4096        | 3128ms  | 559ms  |     336ms     |       125ms    |        12ms    |
|   0.89    |       14        |     8192        | 3130ms  | 560ms  |     331ms     |       124ms    |        11ms    |
|   0.69    |       15        |    16384        | 3132ms  | 562ms  |     330ms     |       124ms    |        11ms    |
|   0.82    |       16        |    32768        | 3129ms  | 561ms  |     333ms     |       123ms    |        10ms    |
