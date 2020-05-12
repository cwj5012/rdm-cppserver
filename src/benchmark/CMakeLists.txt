add_executable(
        benchmark1
        main.cpp
)

target_link_libraries(
        benchmark1
        PRIVATE benchmark::benchmark
)