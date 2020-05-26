#include <benchmark/benchmark.h>

static void BM_NoneFunction(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
    }
}
// Register the function as a benchmark
BENCHMARK(BM_NoneFunction);

static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state)
        std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}

BENCHMARK(BM_StringCopy);

static void BM_For(benchmark::State& state) {
    std::vector<int> vec(1000 * 1000, 0);
    int i = 0;
    for (auto _ : state) {
        i += vec.size();
    }
    int c = i;
}

BENCHMARK(BM_For);

static void BM_For2(benchmark::State& state) {
    std::vector<int> vec(1000, 0);
    int i = 0;
    auto size = vec.size();
    for (auto _ : state) {
        i += size;
    }
    int c = i;
}

BENCHMARK(BM_For2);

static void BM_CreateUint8(benchmark::State& state) {
    std::vector<int> vec(1000, 0);
    auto size = vec.size();
    for (auto _ : state) {
        uint8_t i = 100;
    }
}

BENCHMARK(BM_CreateUint8);

class A {

};

static void BM_CreateClass(benchmark::State& state) {
    std::vector<int> vec(1000, 0);
    auto size = vec.size();
    for (auto _ : state) {
       auto a = A();
    }
}

BENCHMARK(BM_CreateClass);

static void BM_CreateClassHeap(benchmark::State& state) {
    std::vector<int> vec(1000, 0);
    auto size = vec.size();
    for (auto _ : state) {
       auto a = new A();
       delete a;
    }
}

BENCHMARK(BM_CreateClassHeap);

// Run the benchmark
BENCHMARK_MAIN();