cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME learn_cpp)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# 根据实际路径配置
set(USER_LOCAL_PATH
        d:/usr/local)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

if (MSVC)
    # cmake 默认项目放在 CMake 解决方案文件夹中
    # set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
    # Visual Studio 多核编译
    # add_definitions("/MP")
    # dispaly folder in MSVS
    SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
    # C/C++ -> 所有选项 -> 附加选项
    # 修复 Visual Studio 编译 utf8 文件报错的问题
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    # nmake 不支持，所以在 clion 中编译，还是单线程
    set(MSVC_COMPILE_FLAGS "/MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_COMPILE_FLAGS}")
endif ()

##########################################
# 输出路径
##########################################

if (NOT DEFINED CLION)
    set(CLION 1)
endif ()

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 不同 IDE 配置
if (VISUAL_STUDIO)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)     # exec
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)     # shared
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)     # static
elseif (CLION)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})     # exec
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})     # shared
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})     # static
else ()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)     # exec
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)     # shared
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)     # static
endif ()

# 如果动态链接库失败，尝试下面设置
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# use ubuntu apt install benchmark
# if open blow comment, project use benchmark will cause core dump
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake/)

set(CMAKE_INCLUDE_PATH
        ${CMAKE_INCLUDE_PATH}
        ${USER_LOCAL_PATH}/include)

set(CMAKE_LIBRARY_PATH
        ${CMAKE_LIBRARY_PATH}
        ${USER_LOCAL_PATH}/lib/${CMAKE_BUILD_TYPE})

# set(Boost_USE_STATIC_LIBS ON)
if (WIN32)
    # vcpkg install benchmark:x64-windows
    # vcpkg install protobuf:x64-windows
    # vcpkg install boost-system:x64-windows
    # vcpkg install boost-filesystem:x64-windows
    # vcpkg install boost-asio:x64-windows
    # vcpkg install boost-dll:x64-windows
    # vcpkg install jsoncpp:x64-windows
    # vcpkg install tinyxml2:x64-windows
    # vcpkg install yaml-cpp:x64-windows
    # vcpkg install inih:x64-windows
    # vcpkg install mongo-cxx-driver:x64-windows
    # vcpkg install spdlog:x64-windows
    find_package(benchmark REQUIRED)
    find_package(Protobuf REQUIRED)
    find_package(Boost 1.73.0 REQUIRED COMPONENTS system filesystem program_options)
    find_package(jsoncpp REQUIRED)
    find_package(tinyxml2 REQUIRED)
    find_package(yaml-cpp REQUIRED)
    find_package(inih REQUIRED)
    find_package(spdlog CONFIG REQUIRED)
    find_package(mysqlcppconn REQUIRED)
    find_package(mongocxx REQUIRED)
else ()
    find_package(benchmark 1.5.0 REQUIRED)
    find_package(Protobuf 3.6.1 REQUIRED)
    find_package(Boost 1.71.0 REQUIRED system filesystem)
    # find_package(Boost 1.73.0 REQUIRED COMPONENTS system filesystem)
endif ()

if (Boost_FOUND)
    message(STATUS "中文 boost found:")
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
    foreach (library : ${Protobuf_LIBRARIES})
        if (NOT ${library} STREQUAL ":")
            MESSAGE(STATUS "    " ${library})
        endif ()
    endforeach ()
endif ()

message(STATUS "cmake source dir: " ${CMAKE_SOURCE_DIR})

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/third_party
        ${CMAKE_SOURCE_DIR}/third_party/win
        ${CMAKE_SOURCE_DIR}/third_party/yaml-cpp/include
        /usr/local/include/mongocxx/v_noabi
        /usr/local/include/bsoncxx/v_noabi
        ${USER_LOCAL_PATH}/vcpkg/installed/x64-windows/include
)

if (WIN32)
    add_definitions(-D__PRETTY_FUNCTION__=__FUNCSIG__)
    add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif ()



##########################################
# 编译项目
##########################################

set(
        RDM_SHARED
        rdm
        ${MONGOCXX_LIBRARYS}
        ${MYSQLCPPCONN_LIBRARYS}
        ${Boost_LIBRARIES}
        ${Protobuf_LIBRARIES}
        ${Spdlog_LIBRARIES}
        jsoncpp_lib
        tinyxml2::tinyxml2
        benchmark::benchmark benchmark::benchmark_main
        spdlog::spdlog spdlog::spdlog_header_only
        yaml-cpp
        ${INIH_LIBRARYS}
)


add_subdirectory(game/chat_server)
add_subdirectory(game/client)
add_subdirectory(game/login_server)

add_subdirectory(src/benchmark_usage)
add_subdirectory(src/boost_usage)
add_subdirectory(src/coding_interview)
add_subdirectory(src/hello_world)
if (WIN32)
    add_subdirectory(src/imgui_opengl3)
endif ()
add_subdirectory(src/leetcode)
add_subdirectory(src/rdm)
add_subdirectory(src/test)

if (WIN32)
else ()
    # add_subdirectory(third_party/linux/inih)
    # add_subdirectory(third_party/linux/yaml-cpp)
endif ()