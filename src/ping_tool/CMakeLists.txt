add_executable(
        ping_tool
        main.cpp
)

target_link_libraries(
        ping_tool
        ${Boost_LIBRARIES}
)