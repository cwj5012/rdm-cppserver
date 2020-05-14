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

add_executable(
        game_server
        ${CPP_FILES}
)

add_dependencies(
        game_server
        rdm
)

target_link_libraries(
        game_server
        pthread
        dl
        mysqlcppconn
        boost_filesystem
        rdm
)