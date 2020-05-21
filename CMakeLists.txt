cmake_minimum_required(VERSION 3.16)
project(learn_cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake/)

set(Boost_USE_STATIC_LIBS ON)
find_package(benchmark 1.5.0 REQUIRED)
find_package(Boost 1.73.0 REQUIRED COMPONENTS system filesystem)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/third_party
)

if (Boost_FOUND)
    message(STATUS "boost found:")
    foreach (library : ${Boost_LIBRARIES})
        if (NOT ${library} STREQUAL ":")
            MESSAGE(STATUS "    " ${library})
        endif ()
    endforeach ()
endif ()

message(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})

add_subdirectory(game/client)
add_subdirectory(game/login_server)

add_subdirectory(src/benchmark)
add_subdirectory(src/boost)
add_subdirectory(src/coding_interview)
add_subdirectory(src/game_server)
add_subdirectory(src/hello_world)
add_subdirectory(src/leetcode)
add_subdirectory(src/rdm)
add_subdirectory(src/test)

add_subdirectory(third_party/inih)

configure_file(${CMAKE_SOURCE_DIR}/src/rdm/config/test/test.ini /home/me/test COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/rdm/config/test/test.json /home/me/test COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/rdm/config/test/test.xml /home/me/test COPYONLY)
