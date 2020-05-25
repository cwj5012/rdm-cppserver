# 获取目录下所有 *.h / *.cpp 文件
# 记得要编译用到的所有 proto 文件，不然动态解析的时候，无法识别这些消息
file(
        GLOB CPP_FILES
        "*.h"
        "*.cpp"
        "*/*.h"
        "*/*.cpp"
        "*/*/*.h"
        "*/*/*.cpp"
        "*/*/*/*.h"
        "*/*/*/*.cpp"
)

# 获取目录下所有测试文件 *Test.cpp 文件
file(
        GLOB TEST_CPP_FILES
        "*Test.cpp"
        "*/*Test.cpp"
        "*/*/*Test.cpp"
        "*/*/*/*Test.cpp"
)

# 获取目录下所有测试文件 *BM.cpp 文件
file(
        GLOB BM_CPP_FILES
        "*BM.cpp"
        "*/*BM.cpp"
        "*/*/*BM.cpp"
        "*/*/*/*BM.cpp"
)

# 编译文件，排除目录下所有测试文件 *Test.cpp 文件
# 注意，有的 cmake 版本要这么写
# list(REMOVE_ITEM CPP_FILES TEST_CPP_FILES)
list(REMOVE_ITEM CPP_FILES ${TEST_CPP_FILES})
list(REMOVE_ITEM CPP_FILES ${BM_CPP_FILES})

##########################################
# rdm lib
##########################################

add_library(
        rdm STATIC
        ${CPP_FILES}
)

target_link_libraries(
        rdm
        inih
        jsoncpp
        tinyxml2
        ${Boost_LIBRARIES}
)

add_dependencies(
        rdm
        inih
)

set_target_properties(
        rdm
        PROPERTIES LINKER_LANGUAGE CXX
)

##########################################
# rdm test exe
##########################################

add_executable(
        rdm_test
        ${TEST_CPP_FILES}
)

add_dependencies(
        rdm_test
        rdm
)

target_link_libraries(
        rdm_test
        pthread
        dl
        ${Boost_LIBRARIES}
        mysqlcppconn
        rdm
)

##########################################
# rdm benchmark exe
##########################################

add_executable(
        rdm_benchmark
        ${BM_CPP_FILES}
)

add_dependencies(
        rdm_benchmark
        rdm
)

target_link_libraries(
        rdm_benchmark PRIVATE
        pthread
        dl
        benchmark::benchmark
        ${Boost_LIBRARIES}
)

add_subdirectory(submodule)