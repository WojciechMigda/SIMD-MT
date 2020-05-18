[![Build Status](https://travis-ci.com/WojciechMigda/SIMD-MT.svg?branch=master)](https://travis-ci.com/WojciechMigda/SIMD-MT)

# Why?
If you would like to speed up generating pseudo-random integers and floats in your code this might be what you are looking for.

The most common approaches to pseudo-random number generation is to use readily available library solutions. Then, if that appears too slow, one might resort to using open source Mersenne Twister implementations and pull them directly into your code. These, however, commonly are written using loops that are hard to vectorize by the compiler.

In this library I took one of such Mersenne Twister implementations (it is included in this repository and can be found in the `test/src/reference.hpp` file) and rewrote introducing several Mersenne Twister engines to generate pseudo-random numbers.

By doing that it was possible to rewrite the loops in a way that encourages the compiler to use SIMD parallelism during code optimization.

# How?
This is a header-only library and all you need to do is to copy contents of the `include` folder somewhere into your own repository.

`mt.hpp` introduces two generators, one for integers and one for floats.

These two are built upon two class templates, `basic_IRNG` and `basic_FRNG`, respectively.
Their two template parameters control alignment of the internal PRNG state (`Alignment`) and number of Mersenne Twister streams (`NumberOfStreams`). If you would like to search for more optimal values for your specific hardware you can tweak these two parameters.

Default values (`Alignment=64` and `NumberOfStreams=8`) are used to define two types: `IRNG` and `FRNG`.

# How fast is it?
Full build of the library includes microbenchmark using google's `benchmark` library. You can execute measurements invoking `make run_benchmark`.

Most recent values reported during travis build are:
```
$ make run_benchmark
Scanning dependencies of target run_benchmark
[100%] Running google benchmarks
2020-05-18 18:45:33
Running ./simd-mt-bench
Run on (2 X 2800.17 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x1)
  L1 Instruction 32 KiB (x1)
  L2 Unified 1024 KiB (x1)
  L3 Unified 33792 KiB (x1)
Load Average: 0.87, 0.27, 0.09
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
BM_IRNG_next                       2.32 ns         2.32 ns    308260367
BM_FRNG_next                       2.31 ns         2.31 ns    303615475
BM_reference_next                  3.45 ns         3.45 ns    202998530
BM_reference_nextFloat             3.75 ns         3.75 ns    186813956
BM_posix_random                    5.65 ns         5.65 ns    123828430
BM_lrand48                         5.47 ns         5.47 ns    127350759
BM_drand48                         6.19 ns         6.19 ns    113458286
BM_mt19937                         6.33 ns         6.32 ns    110624848
BM_uniform_real_distribution       6.84 ns         6.83 ns    102346236
[100%] Built target run_benchmark
The command "make run_benchmark" exited with 0.
```
The two first entries correspond to this implementation, integer and float generators, respectively. The next two are for the reference non-SIMD implementation. Subsequent entries show how well perform common library PRNGs.

Numbers above show that on the hardware used by travis this library performs significantly better than others. On my laptop edge over the reference implementation is smaller, though - your mileage may vary.