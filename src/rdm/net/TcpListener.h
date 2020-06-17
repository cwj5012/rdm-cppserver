#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "TcpConn.h"

using boost::asio::ip::tcp;
using boost::asio::ip::address;

namespace rdm {

class TcpListener : public std::enable_shared_from_this<TcpListener> {
public:
    using sptr = std::shared_ptr<TcpListener>;

    /**
     * 初始化 TcpListener
     * @param io_service
     */
    explicit TcpListener(boost::asio::io_service& io_service);

    /**
     * 初始化 TcpListener，并启动监听
     * @param io_service
     * @param addr
     * @param port
     */
    explicit TcpListener(boost::asio::io_service& io_service,
                         const std::string& addr,
                         uint16_t port);

    ~TcpListener();

    /**
     * 绑定 io_service，地址和端口
     * @param io_service
     * @param addr
     * @param port
     */
    void bind(boost::asio::io_service& io_service, const std::string& addr, uint16_t port);

    TcpConn::sptr getConnection(uint32_t conn_id);

    /**
     * 获取一条连接，无条件限制
     * @return
     */
    TcpConn::sptr getConnection();

    /**
     * 获取所有连接
     * @return
     */
    std::vector<TcpConn::sptr> getConnections();

    int32_t fd() const;

private:
    void accept();

    void handleAccept(const TcpConn::sptr& new_conn,
                      const boost::system::error_code& ec);

    std::unique_ptr<tcp::acceptor> accecptor_; // 内部包含 1 个 socket
    std::unique_ptr<tcp::endpoint> endpoint_;

    boost::asio::io_context& io_context_;
    std::map<uint32_t, TcpConn::sptr> conns_;
    std::map<uint32_t, TcpConn::sptr> auth_conns_;
};

} // namespace rdm
