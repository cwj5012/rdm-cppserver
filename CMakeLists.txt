cmake_minimum_required(VERSION 3.16)
project(learn_cpp)

set(CMAKE_CXX_STANDARD 17)

set(Boost_VERSION 1.71.0)
set(Boost_DEBUG ON)
set(BOOST_ROOT /home/me/boost_1_71_0/)
set(BOOST_INCLUDEDIR /usr/local/include/boost/)
set(BOOST_LIBRARYDIR /usr/local/lib/)
set(Boost_NO_BOOST_CMAKE ON)
# set(Boost_DIR /usr/local/lib/cmake/Boost-1.71.0/)

find_package(benchmark 1.5.0 REQUIRED)
find_package(boost 1.71.0 REQUIRED COMPONENTS system filesystem)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/third_party
)

if (Boost_FOUND)
    message(STATUS "Boost_FOUND")
endif ()

message(STATUS ${Boost_LIBRARIES})
message(STATUS ${Boost_INCLUDE_DIRS})
message(STATUS ${CMAKE_SOURCE_DIR})

add_subdirectory(src/benchmark)
add_subdirectory(src/boost)
add_subdirectory(src/hello_world)
add_subdirectory(src/rdm)
add_subdirectory(src/test)
