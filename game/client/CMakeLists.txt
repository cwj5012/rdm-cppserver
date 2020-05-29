
file(
        GLOB CPP_FILES
        "./*.h"
        "./*.cpp"
        "./*/*.h"
        "./*/*.cpp"
        "./*/*/*.h"
        "./*/*/*.cpp"
        "./*/*/*/*.h"
        "./*/*/*/*.cpp"
)

add_executable(
        client
        ${CPP_FILES}
)

add_dependencies(
        client
        rdm
)

target_link_libraries(
        client
        ${RDM_SHARED}
)

link_directories(
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Boost_LIBRARY_DIR}
)