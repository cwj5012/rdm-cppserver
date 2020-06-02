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
        "protocol/*.pb.h"
        "protocol/*.pb.cc"
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
# list(REMOVE_ITEM CPP_FILES BM_CPP_FILES)
list(REMOVE_ITEM CPP_FILES ${TEST_CPP_FILES})
list(REMOVE_ITEM CPP_FILES ${BM_CPP_FILES})

##########################################
# rdm lib
##########################################

if (WIN32)
    add_library(
            rdm STATIC
            ${CPP_FILES}
    )
else ()
    add_library(
            rdm SHARED
            ${CPP_FILES}
    )

    add_dependencies(
            rdm
            inih
            yaml-cpp
    )

    target_link_libraries(
            rdm
    )
endif ()


set_target_properties(
        rdm
        PROPERTIES LINKER_LANGUAGE CXX
)


if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    # CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    # if (_cpp_latest_flag_supported)
        #        add_compile_options("/std:c++latest")
    # endif ()
endif ()

# 连接器，命令行添加 /ignore:4099
set_target_properties(rdm PROPERTIES LINK_FLAGS "/ignore:4819 /ignore:4566")
# 目标平台 win7 及以上
add_definitions(-D _WIN32_WINNT=0x0601)
add_definitions(-D _CRT_SECURE_NO_WARNINGS)

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

if (WIN32)
    target_link_libraries(
            rdm_test
            ${RDM_SHARED}
    )
else ()
    target_link_libraries(
            rdm_test
            ${RDM_SHARED}
            pthread
            dl
    )
endif ()

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

if (WIN32)
    target_link_libraries(
            rdm_benchmark PRIVATE
            ${RDM_SHARED}
    )
else ()
    target_link_libraries(
            rdm_benchmark PRIVATE
            ${RDM_SHARED}
            pthread
            dl
    )
endif ()


add_subdirectory(submodule)