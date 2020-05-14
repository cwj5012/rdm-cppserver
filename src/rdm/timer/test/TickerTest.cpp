///**
// * 多个测试都有创建 boost::asio::io_service 时，尽量不要操作相同的函数或者变量，
// * 不然会出现后面的测试运行时，前面的 io_service 也在运行，影响测试结果
// *
// * 解决方法，不同的测试用单独的命名空间，这样同名的函数和变量就不会影响了
// */
//
//#include <iostream>
//
//#include <gtest/gtest.h>
//
//#include <LibServer/timer/Ticker.h>
//#include <LibServer/thread/ThreadUtil.h>
//#include <LibServer/core/GtestExt.h>
//
//using namespace rdm;
//
//namespace Ticker_bind_test
//{
//
//    static int32_t num1 = 0;
//    static int32_t num2 = 0;
//    static int32_t num3 = 0;
//
//    void funcA()
//    {
//        num1 += 1;
//    }
//
//    void funcB()
//    {
//        num2 += 2;
//    }
//
//    void funcC()
//    {
//        num3 += 3;
//    }
//
//    TEST(Ticker, bind)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        Ticker t1(&ios, 1000);
//                        t1.bind(funcA);
//                        t1.bind(funcB);
//                        t1.bind(funcC);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//}
//
//namespace Ticker_pause_test
//{
//
//    static int32_t num1 = 0;
//    static int32_t num2 = 0;
//    static int32_t num3 = 0;
//
//    void funcA()
//    {
//        num1 += 1;
//    }
//
//    void funcB()
//    {
//        num2 += 2;
//    }
//
//    void funcC()
//    {
//        num3 += 3;
//    }
//
//    TEST(Ticker, pause)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        Ticker t1(&ios, 1000);
//                        t1.bind(funcA);
//                        t1.bind(funcB);
//                        t1.bind(funcC);
//                        ThreadUtil::sleep(500);
//                        t1.pause();
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 0);
//        EXPECT_EQ(num3, 0);
//    }
//}
//
//namespace Ticker_cancel_test
//{
//
//    static int32_t num1 = 0;
//    static int32_t num2 = 0;
//    static int32_t num3 = 0;
//
//    void funcA()
//    {
//        num1 += 1;
//    }
//
//    void funcB()
//    {
//        num2 += 2;
//    }
//
//    void funcC()
//    {
//        num3 += 3;
//    }
//
//    TEST(Ticker, cancel)
//    {
//        boost::asio::io_service ios;
//        Ticker t1(&ios, 1000);
//        t1.bind(funcA);
//        t1.bind(funcB);
//        t1.bind(funcC);
//        t1.cancel();
//        ios.run();
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 0);
//        EXPECT_EQ(num3, 0);
//    }
//}
//
//namespace Ticker_keepOn_test
//{
//
//    static int32_t num1 = 0;
//    static int32_t num2 = 0;
//    static int32_t num3 = 0;
//
//    void funcA()
//    {
//        num1 += 1;
//    }
//
//    void funcB()
//    {
//        num2 += 2;
//    }
//
//    void funcC()
//    {
//        num3 += 3;
//    }
//
//    TEST(Ticker, keepOn)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        Ticker t1(&ios, 1000);
//                        t1.bind(funcA);
//                        t1.bind(funcB);
//                        t1.bind(funcC);
//                        t1.pause();
//                        t1.keepOn();
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//}