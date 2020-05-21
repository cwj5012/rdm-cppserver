﻿//#include <iostream>
//
//#include <gtest/gtest.h>
//
//#include <LibServer/timer/TickerManager.h>
//#include <LibServer/thread/ThreadUtil.h>
//#include <LibServer/core/GtestExt.h>
//
//using namespace rdm;
//
//namespace TickerManager_bind_test
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
//    TEST(TickerManager, bind)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TickerManager tm(&ios);
//                        tm.add(1, 1000, funcA);
//                        tm.add(2, 1000, funcB);
//                        tm.bind(1, funcC);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//
//}
//
//namespace TickerManager_pause_test
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
//    TEST(TickerManager, pause)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TickerManager tm(&ios);
//                        tm.add(1, 1000, funcA);
//                        tm.add(2, 1000, funcB);
//                        tm.bind(1, funcC);
//                        tm.pause(1);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 0);
//    }
//
//}
//
//namespace TickerManager_cancel_test
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
//    TEST(TickerManager, cancel)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TickerManager tm(&ios);
//                        tm.add(1, 1000, funcA);
//                        tm.add(2, 1000, funcB);
//                        tm.bind(1, funcC);
//                        tm.cancel(1);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 0);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 0);
//    }
//
//}
//
//namespace TickerManager_keepOn_test
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
//    TEST(TickerManager, keepOn)
//    {
//        TEST_TIMEOUT_BEGIN
//                    {
//                        boost::asio::io_service ios;
//                        TickerManager tm(&ios);
//                        tm.add(1, 1000, funcA);
//                        tm.add(2, 1000, funcB);
//                        tm.bind(1, funcC);
//                        tm.pause(1);
//                        tm.keepOn(1);
//                        ios.run();
//                    }
//        TEST_TIMEOUT_SUCCESS_END(2000)
//
//        ThreadUtil::sleep(50);
//        EXPECT_EQ(num1, 3);
//        EXPECT_EQ(num2, 6);
//        EXPECT_EQ(num3, 9);
//    }
//
//}