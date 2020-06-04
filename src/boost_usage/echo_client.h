#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include "../rdm/util/Time.h"

using boost::asio::ip::tcp;

enum {
    max_length = 1024
};

void echo_client(std::string host, std::string port, int count) {
    try {
        boost::asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s,  resolver.resolve(host, port));

        char request[] = "1234567890";
        size_t request_length = std::strlen(request);

        for (int i = 0; i < count; ++i) {
            // rdm::StopWatch sw;
            // sw.restart();
            // 测试时间开始 ==============================

            boost::asio::write(s, boost::asio::buffer(request, request_length));

            char reply[max_length];
            boost::asio::read(s, boost::asio::buffer(reply, request_length));

            // 测试时间结束 ==============================
            // sw.end();
            // std::cout << sw.durationUs() << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

