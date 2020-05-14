﻿#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "NetConnection.h"

using boost::asio::ip::tcp;
using boost::asio::ip::address;

namespace rdm {

class NetAcceptor : public std::enable_shared_from_this<NetAcceptor> {
public:

    /**
     * 初始化 Acceptor
     * @param io_service
     */
    explicit NetAcceptor(boost::asio::io_service& io_service);

    /**
     * 初始化 Acceptor，并启动监听
     * @param io_service
     * @param addr
     * @param port
     */
    explicit NetAcceptor(boost::asio::io_service& io_service,
                         const std::string& addr,
                         uint16_t port);

    ~NetAcceptor();

    /**
     * 绑定 io_service，地址和端口
     * @param io_service
     * @param addr
     * @param port
     */
    void bind(boost::asio::io_service& io_service, const std::string& addr, uint16_t port);

    NetConnection::ptrConnection getConnection(tcp::socket* s);

    /**
     * 获取一条连接，无条件限制
     * @return
     */
    NetConnection::ptrConnection getConnection();

    /**
     * 获取所有连接
     * @return
     */
    std::vector<NetConnection::ptrConnection> getConnections();

private:
    void startAccept();

    void handleAccept(NetConnection::ptrConnection new_connection,
                      const boost::system::error_code& ec);

    std::shared_ptr<tcp::acceptor> mAcceptor;
    std::shared_ptr<tcp::endpoint> mEndpoint;
    std::shared_ptr<address> mAddress;

    boost::asio::io_context& mIoContext;
    std::map<tcp::socket*, NetConnection::ptrConnection> mSocketConnection;

};

} // namespace rdm
