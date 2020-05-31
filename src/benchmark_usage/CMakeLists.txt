add_executable(
        benchmark_usage
        main.cpp
)

target_link_libraries(
        benchmark_usage
        PRIVATE benchmark::benchmark
)