add_executable(
        hello_world
        main.cpp
)

target_link_libraries(
        hello_world
        rdm::submodule
        ${RDM_SHARED}
)

add_dependencies(
        hello_world
        rdm::submodule
)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ${CMAKE_SOURCE_DIR}/src
)