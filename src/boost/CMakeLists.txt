add_executable(
        boost
        main.cpp
        echo_client.h
        echo_server.h
)

target_link_libraries(
        boost
        ${Boost_LIBRARIES}
        pthread
)