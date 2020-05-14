#include <benchmark/benchmark.h>

static void BM_NoneFunction(benchmark::State &state) {
    for (auto _ : state) {

    }
}
BENCHMARK(BM_NoneFunction);

BENCHMARK_MAIN();