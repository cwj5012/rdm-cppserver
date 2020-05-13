#include <catch2/catch.hpp>

#include "../ThreadPool.h"
#include "../ThreadUtil.h"
#include "../../log/Logger.h"

using namespace rdm;

namespace {

void func1(int32_t num) {
    ThreadUtil::sleep(1000);
    num += 1;
    LOG_INFO("{}", num);
}

void func2(int32_t num) {
    ThreadUtil::sleep(2000);
    num += 2;
    LOG_INFO("{}", num);
}

void func3(int32_t num) {
    ThreadUtil::sleep(3000);
    num += 3;
    LOG_INFO("{}", num);
}

} // namespace

TEST_CASE("ThreadPool", "[]") {
    boost::asio::io_service io_service;
    ThreadPool tp(&io_service, 4);

    tp.post(func1, 10);
    tp.post(func2, 20);
    tp.post(func3, 20);

    ThreadUtil::sleep(5000);
    tp.stop();
}
