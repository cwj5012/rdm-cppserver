#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum {
    max_length = 1024
};

void echo_client(std::string host, std::string port) {
    try {
        boost::asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s,  resolver.resolve(host, port));

        char request[] = "1234567890";
        size_t request_length = std::strlen(request);

        for (int i = 0; i < 1000 * 100; ++i) {
            boost::asio::write(s, boost::asio::buffer(request, request_length));

            char reply[max_length];
            boost::asio::read(s, boost::asio::buffer(reply, request_length));
            // size_t reply_length =
            // std::cout.write(reply, reply_length);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

