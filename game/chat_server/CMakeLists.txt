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
        mysqlcppconn
        rdm
)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/src
)