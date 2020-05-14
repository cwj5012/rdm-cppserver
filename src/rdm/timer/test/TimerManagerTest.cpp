//#include <iostream>
//
//#include <gtest/gtest.h>
//
//#include <LibServer/timer/TimerManager.h>
//#include <LibServer/thread/ThreadUtil.h>
//#include <LibServer/core/GtestExt.h>
//
//using namespace rdm;
//
//namespace TimerManager_bind_test
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
//    TEST(TimerManager, bind)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TimerManager tm(&ios);
//                        tm.add(1, 1000, 1000, funcA);
//                        tm.add(2, 1000, 1000, funcB);
//                        tm.bind(1, funcC);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//
//}
//
//namespace TimerManager_pause_test
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
//    TEST(TimerManager, pause)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TimerManager tm(&ios);
//                        tm.add(1, 1000, 1000, funcA);
//                        tm.add(2, 1000, 1000, funcB);
//                        tm.bind(1, funcC);
//                        tm.pause(1);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 0);
//    }
//
//}
//
//namespace TimerManager_cancel_test
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
//    TEST(TimerManager, cancel)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TimerManager tm(&ios);
//                        tm.add(1, 1000, 1000, funcA);
//                        tm.add(2, 1000, 1000, funcB);
//                        tm.bind(1, funcC);
//                        tm.cancel(1);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 0);
//    }
//
//}
//
//namespace TimerManager_keepOn_test
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
//    TEST(TimerManager, keepOn)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TimerManager tm(&ios);
//                        tm.add(1, 1000, 1000, funcA);
//                        tm.add(2, 1000, 1000, funcB);
//                        tm.bind(1, funcC);
//                        tm.pause(1);
//                        tm.keepOn(1);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(3000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//
//}