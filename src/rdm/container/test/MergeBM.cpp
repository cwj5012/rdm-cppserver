#include <algorithm>
#include <vector>
#include <utility>

#include <benchmark/benchmark.h>

#include "../Merge.h"

static void BM_Merge(benchmark::State &state) {
    std::vector<std::pair<int, int>> a = {{1, 1},
                                          {2, 2},
                                          {3, 3}};
    std::vector<std::pair<int, int>> b = {{1, 2},
                                          {2, 3}};

    std::vector<std::pair<int, int>> c = {{1, 1},
                                          {1, 2},
                                          {2, 2},
                                          {2, 3},
                                          {3, 3}};

    std::vector<std::pair<int, int>> dst;



    rdm::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(dst));

    for (auto _ : state) {
        rdm::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(dst));
    }
}
BENCHMARK(BM_Merge);