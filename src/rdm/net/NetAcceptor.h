﻿#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "NetConnection.h"

using boost::asio::ip::tcp;
using boost::asio::ip::address;

namespace rdm {

class NetAcceptor : public std::enable_shared_from_this<NetAcceptor> {
public:
    using sptr = std::shared_ptr<NetAcceptor>;

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

    NetConnection::sptr getConnection(tcp::socket* s);

    /**
     * 获取一条连接，无条件限制
     * @return
     */
    NetConnection::sptr getConnection();

    /**
     * 获取所有连接
     * @return
     */
    std::vector<NetConnection::sptr> getConnections();

private:
    void startAccept();

    void handleAccept(NetConnection::sptr new_connection,
                      const boost::system::error_code& ec);

    std::shared_ptr<tcp::acceptor> accecptor_;
    std::shared_ptr<tcp::endpoint> endpoint_;
    std::shared_ptr<address> addr_;

    boost::asio::io_context& io_context_;
    std::map<tcp::socket*, NetConnection::sptr> conns_;

};

} // namespace rdm
