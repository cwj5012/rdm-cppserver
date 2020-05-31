cmake_minimum_required(VERSION 3.16)
project(learn_cpp)

set(CMAKE_CXX_STANDARD 17)

# 如果动态链接库失败，尝试下面设置
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake/)

# set(Boost_USE_STATIC_LIBS ON)
find_package(benchmark 1.5.0 REQUIRED)
find_package(Protobuf 3.6.1 REQUIRED)
find_package(Boost 1.71.0 REQUIRED system filesystem)
# find_package(Boost 1.73.0 REQUIRED COMPONENTS system filesystem)
find_package(jsoncpp REQUIRED)
# find_package(tinyxml2 REQUIRED)
# find_package(yaml-cpp REQUIRED)
# find_package(mysqlcppconn REQUIRED)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/third_party
        ${CMAKE_SOURCE_DIR}/third_party/yaml-cpp/include
        /usr/local/include/mongocxx/v_noabi
        /usr/local/include/bsoncxx/v_noabi
)

if (Boost_FOUND)
    message(STATUS "boost found:")
    foreach (library : ${Boost_LIBRARIES})
        if (NOT ${library} STREQUAL ":")
            MESSAGE(STATUS "    " ${library})
        endif ()
    endforeach ()
endif ()

if (Protobuf_FOUND)
    message(STATUS "protobuf found:")
    message(STATUS "    prorobuf version: " ${Protobuf_VERSION})
    message(STATUS "    protoc version: " ${_PROTOBUF_PROTOC_EXECUTABLE_VERSION})
    MESSAGE(STATUS "    " ${Protobuf_LIBRARIES})
endif ()

message(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})

##########################################
# 输出路径
##########################################

if (NOT DEFINED CLION)
    set(CLION 1)
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)  # exec
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)     # shared
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # static

if (CLION)
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})     # exec
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})     # shared
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})  # static
endif ()

##########################################
# 编译项目
##########################################

set(
        RDM_SHARED
        rdm
        mongocxx
        bsoncxx
        mysqlcppconn
        boost_filesystem
        protobuf
        inih
        jsoncpp
        tinyxml2
        yaml-cpp
)


add_subdirectory(game/chat_server)
add_subdirectory(game/client)
add_subdirectory(game/login_server)

add_subdirectory(src/benchmark)
add_subdirectory(src/boost)
add_subdirectory(src/coding_interview)
add_subdirectory(src/hello_world)
add_subdirectory(src/leetcode)
add_subdirectory(src/rdm)
add_subdirectory(src/test)

add_subdirectory(third_party/inih)
add_subdirectory(third_party/yaml-cpp)
