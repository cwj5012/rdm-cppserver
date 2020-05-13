#pragma once

#include <cstdint>
#include <vector>
#include <thread>
#include <functional>

#include <boost/asio.hpp>

namespace rdm {

class ThreadPool {
public:
    explicit ThreadPool(int32_t num);

    explicit ThreadPool(boost::asio::io_service* ios, int32_t num);

    ~ThreadPool();

    template<typename F, typename...Args>
    void post(F&& f, Args&& ...args) {
        ios_->post(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    }

    void stop();

private:
    bool isStop_;
    int32_t num_;
    std::vector<std::shared_ptr<std::thread>> threads_;
    boost::asio::io_service* ios_;
    boost::asio::io_service::work* work_;
};

}