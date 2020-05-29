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

file(
        GLOB CPP_PROTOBUF_FILES
        ${CMAKE_SOURCE_DIR}/src/rdm/protocol/*.pb.h
        ${CMAKE_SOURCE_DIR}/src/rdm/protocol/*.pb.cc
)

add_executable(
        chat_server
        ${CPP_FILES}
        ${CPP_PROTOBUF_FILES}
)

add_dependencies(
        chat_server
        rdm
)

target_link_libraries(
        chat_server
        inih
        jsoncpp
        tinyxml2
        pthread
        dl
        boost_filesystem
        protobuf
        rdm
        mysqlcppconn # g++ mysqlcppconn 写在 rdm 后面才能编译成功
        yaml-cpp
)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/src
)

link_directories(
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Boost_LIBRARY_DIR}
)