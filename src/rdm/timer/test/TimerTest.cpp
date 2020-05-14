//#include <iostream>
//
//#include <gtest/gtest.h>
//
//#include <LibServer/timer/Timer.h>
//#include <LibServer/thread/ThreadUtil.h>
//#include <LibServer/core/GtestExt.h>
//
//using namespace rdm;
//
//namespace Timer_bind_test
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
//    TEST(Timer, bind)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        Timer t1(&ios, 1000, 1000);
//                        t1.bind(funcA);
//                        t1.bind(funcB);
//                        t1.bind(funcC);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//}
//
//namespace Timer_pause_test
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
//    TEST(Timer, pause)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        Timer t1(&ios, 1000, 1000);
//                        t1.bind(funcA);
//                        t1.bind(funcB);
//                        t1.bind(funcC);
//                        ThreadUtil::sleep(1500);
//                        t1.pause();
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 0);
//        EXPECT_EQ(num3, 0);
//    }
//}
//
//namespace Timer_cancel_test
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
//    TEST(Timer, cancel)
//    {
//        boost::asio::io_service ios;
//        Timer t1(&ios, 1000, 1000);
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
//namespace Timer_keepOn_test
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
//    TEST(Timer, keepOn)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        Timer t1(&ios, 1000, 1000);
//                        t1.bind(funcA);
//                        t1.bind(funcB);
//                        t1.bind(funcC);
//                        t1.pause();
//                        t1.keepOn();
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//}