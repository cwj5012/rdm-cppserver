#include "ThreadPool.h"
#include "../log/Logger.h"

namespace rdm {

ThreadPool::ThreadPool(int32_t num) : num_(num),
                                      isStop_(false) {
    // 如果创建了 work，需要在析构函数中删除对象，否则无法退出
    work_ = new boost::asio::io_service::work(*ios_);

    ios_ = new boost::asio::io_service();
    for (int32_t i = 0; i < num_; ++i) {
        threads_.push_back(std::make_shared<std::thread>(
                [&]() { ios_->run(); }
        ));
        LOG_INFO("create thread pool, num: {}", i + 1);
    }
}

ThreadPool::ThreadPool(boost::asio::io_service* ios, int32_t num)
        : num_(num),
          isStop_(false),
          ios_(ios) {
    // 如果创建了 work，需要在析构函数中删除对象，否则无法退出
    work_ = new boost::asio::io_service::work(*ios_);

    for (int32_t i = 0; i < num_; ++i) {
        threads_.push_back(std::make_shared<std::thread>(
                [&]() { ios_->run(); }
        ));
        LOG_INFO("create thread pool, num: {}", i + 1);
    }
}

ThreadPool::~ThreadPool() {
    LOG_INFO("ThreadPool::~ThreadPool");
    stop();
}

void ThreadPool::stop() {
    if (!isStop_) {
        LOG_INFO("ThreadPool::stop");
        ios_->stop();
        for (auto th: threads_) {
            th->join();
        }
        isStop_ = true;

        // 如果构造函数创建了 work 对象，调用 io_service::stop
        // 方法以后需要手动删除该对象，才能让 io_service 退出
        delete work_;
    }
}

}