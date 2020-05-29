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
        login_server
        ${CPP_FILES}
)

add_dependencies(
        login_server
        rdm
)

target_link_libraries(
        login_server
         ${RDM_SHARED}
)