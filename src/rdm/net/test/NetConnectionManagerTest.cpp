//#include <gtest/gtest.h>
//
//#include <LibServer/net/NetConnectionManager.h>
//#include <LibServer/util/Logger.h>
//
//using namespace rdm;
//
//TEST(NetConnectionManager, test)
//{
//    NetConnectionManager nconnm;
//    boost::asio::io_service io_service;
//    auto netConn = NetConnection::create(io_service);
//    auto netConnA = NetConnection::create(io_service);
//
//    nconnm.pushClientConnection(netConn, 1);
//    nconnm.pushClientConnection(netConn, 2);
//    nconnm.pushClientConnection(netConn, 3);
//    EXPECT_FALSE(nconnm.pushClientConnection(netConnA, 3));
//
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getClientConnection(1).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getClientConnection(2).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getClientConnection(3).get());
//
//    EXPECT_EQ(0, (uint64_t) nconnm.getClientConnection(4).get());
//
//    nconnm.pushServerConnection(netConn, 1, 1);
//    nconnm.pushServerConnection(netConn, 1, 2);
//    EXPECT_FALSE(nconnm.pushServerConnection(netConnA, 1, 2));
//
//    nconnm.pushServerConnection(netConn, 2, 1);
//    nconnm.pushServerConnection(netConn, 2, 2);
//    EXPECT_FALSE(nconnm.pushServerConnection(netConnA, 2, 2));
//
//    nconnm.pushServerConnection(netConn, 3, 1);
//    nconnm.pushServerConnection(netConn, 3, 2);
//    EXPECT_FALSE(nconnm.pushServerConnection(netConnA, 3, 2));
//
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getServerConnection(1, 1).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getServerConnection(1, 2).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getServerConnection(2, 1).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getServerConnection(2, 2).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getServerConnection(3, 1).get());
//    EXPECT_EQ((uint64_t) netConn.get(), (uint64_t) nconnm.getServerConnection(3, 2).get());
//
//    EXPECT_EQ(0, (uint64_t) nconnm.getServerConnection(1, 3).get());
//    EXPECT_EQ(0, (uint64_t) nconnm.getServerConnection(2, 3).get());
//    EXPECT_EQ(0, (uint64_t) nconnm.getServerConnection(3, 3).get());
//
//    // 主动调用 release，先释放管理器中的对象，接着 netConn 和 netConnA 自动析构，最后 connm 自动析构
//    // 如果没按这个步骤，首先 netConn 和 netConnA 自动析构，然后 connm 自动析构的时候会报错
//    nconnm.release();
//}