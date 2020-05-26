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
        pthread
        dl
        ${Boost_LIBRARIES}
        ${Protobuf_LIBRARIES}
        rdm
        mysqlcppconn # g++ mysqlcppconn 写在 rdm 后面才能编译成功
)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/src
)