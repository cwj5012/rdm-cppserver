set(TARGET_NAME api_service)

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
        ../protocol/MessageType.h
)

file(
        GLOB CPP_PROTOBUF_FILES
        ${CMAKE_SOURCE_DIR}/src/rdm/protocol/*.pb.h
        ${CMAKE_SOURCE_DIR}/src/rdm/protocol/*.pb.cc
)

add_executable(
        ${TARGET_NAME}
        ${CPP_FILES}
        ${CPP_PROTOBUF_FILES}
)

add_dependencies(
        ${TARGET_NAME}
        rdm
)

if (WIN32)
    target_link_libraries(
            ${TARGET_NAME}
            #        inih
            #        jsoncpp
            #        tinyxml2
            #        pthread
            #        dl
            #        boost_filesystem
            #        protobuf
            #        rdm
            #        mysqlcppconn # g++ mysqlcppconn 写在 rdm 后面才能编译成功
            #        yaml-cpp

            ${RDM_SHARED}
    )
else ()
    target_link_libraries(
            ${TARGET_NAME}
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
endif ()


include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/src
        ../protocol
)

link_directories(
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Boost_LIBRARY_DIR}
)