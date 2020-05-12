# rdm lib
add_library(
        rdm
        container/Merge.h
        container/SparseByteSet.h
)

set_target_properties(
        rdm
        PROPERTIES LINKER_LANGUAGE CXX
)

# rdm test exe
add_executable(
        rdm_test
        Test.cpp
        container/test/MergeTest.cpp
        container/test/SparseByteSetTest.cpp
)

# rdm benchmark exe
add_executable(
        rdm_benchmark
        Benchmark.cpp
        container/test/SparseByteSetBM.cpp
        container/test/MergeBM.cpp
)

add_dependencies(
        rdm_benchmark
        rdm
)

target_link_libraries(
        rdm_benchmark
        PRIVATE benchmark::benchmark
)