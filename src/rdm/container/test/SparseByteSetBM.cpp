#include <benchmark/benchmark.h>

#include "../SparseByteSet.h"

static void BM_SparseByteSet(benchmark::State &state) {
    for (auto _ : state) {
        rdm::SparseByteSet s;
        for (int i = 0; i < 255; ++i) {
            s.add(i);
            s.contains(i);
        }
    }
}
BENCHMARK(BM_SparseByteSet);