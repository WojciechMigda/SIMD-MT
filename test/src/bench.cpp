#include "mt.hpp"
#include "reference.hpp"

#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>

static void BM_IRNG_next(benchmark::State& state)
{
    IRNG rng(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(rng.next());
    }
}
BENCHMARK(BM_IRNG_next);


static void BM_FRNG_next(benchmark::State& state)
{
    FRNG rng(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(rng.next());
    }
}
BENCHMARK(BM_FRNG_next);


static void BM_reference_next(benchmark::State& state)
{
    ref::RNG rng(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(rng.next());
    }
}
BENCHMARK(BM_reference_next);


static void BM_reference_nextFloat(benchmark::State& state)
{
    ref::RNG rng(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(rng.nextFloat());
    }
}
BENCHMARK(BM_reference_nextFloat);


static void BM_posix_random(benchmark::State& state)
{
    srandom(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(random());
    }
}
BENCHMARK(BM_posix_random);


static void BM_lrand48(benchmark::State& state)
{
    srand48(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(lrand48());
    }
}
BENCHMARK(BM_lrand48);


static void BM_drand48(benchmark::State& state)
{
    srand48(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(drand48());
    }
}
BENCHMARK(BM_drand48);


static void BM_mt19937(benchmark::State& state)
{
    std::mt19937 gen(1);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(gen());
    }
}
BENCHMARK(BM_mt19937);


static void BM_uniform_real_distribution(benchmark::State& state)
{
    std::mt19937 gen(1);
    std::uniform_real_distribution<float> dis;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(dis(gen));
    }
}
BENCHMARK(BM_uniform_real_distribution);


BENCHMARK_MAIN();
