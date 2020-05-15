add_executable(
        hello_world
        main.cpp
)

target_link_libraries(
        hello_world
        rdm::submodule
)

add_dependencies(
        hello_world
        rdm::submodule
)