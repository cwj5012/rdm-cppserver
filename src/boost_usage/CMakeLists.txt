add_executable(
        boost_usage
        main.cpp
        echo_client.h
        echo_server.h
)

target_link_libraries(
        boost_usage
        ${Boost_LIBRARIES}
        # pthread
)

#include_directories(D:/Users/cwj/Desktop/vcpkg/installed/x64-windows/include)