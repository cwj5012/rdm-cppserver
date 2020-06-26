/*
 * 客户端网络类
 *
 * 跟客户端通信的消息，用枚举来识别消息类型（服务器内部则用 protobuf 的消息名来识别消息类型）
 */

#pragma once

#include <deque>

#include <boost/asio.hpp>

#include "../message/MsgEnum.h"
#include "../observer/MessageSubject.h"
#include "../observer/Observer.h"

using boost::asio::ip::tcp;

namespace rdm {

class NetClient {
public:
    /**
     * 创建一个 TCP 客户端实例
     * @param io_context
     */
    explicit NetClient(boost::asio::io_service* io_context);

    /**
     * 创建一个 TCP 客户端实例，并连接到目标
     * @param io_context
     * @param ip
     * @param port
     */
    explicit NetClient(boost::asio::io_service* io_context,
                       const std::string& ip,
                       const std::string& port);

    /**
     * 创建一个 TCP 客户端实例，并连接到目标
     * @param io_context
     * @param endpoints
     */
    explicit NetClient(boost::asio::io_service* io_context,
                       const tcp::resolver::results_type& endpoints);

    void write(const std::string& msg);

    void close();
    void start();
    void stop();
    void restart();

    void registMessage(const std::string& message_name, IObserver* observer);
    void registMessage(const MsgEnum& msg_enum, IObserver* observer);

    std::shared_ptr<MessageSubject> getMessageSubject();

    bool isConnected() const;

    /**
     * 根据已有的 endpoints，调用这个方法连接主机
     */
    void doConnect();

private:
    /**
     * 连接到目标主机
     * @param ip
     * @param port
     */
    void doConnect(const std::string& ip,
                   const std::string& port);

    /**
     * 连接到目标主机
     * 其他重载方法，最终都调用这个方法来连接主机
     * @param endpoints
     */
    void doConnect(const tcp::resolver::results_type& endpoints);

    void handleConnect(const boost::system::error_code& ec,
                       tcp::resolver::iterator endpoint_iter);

    void doRead();
    void handleRead(const boost::system::error_code& ec, std::size_t bytes_transferred);

    void doWrite();

    enum {
        MESSAGE_LENGTH_MAX = 1024
    };

    bool stopped_{false};
    boost::asio::io_service* io_context_;
    boost::asio::ip::tcp::socket* socket_;
    char read_message_[MESSAGE_LENGTH_MAX];
    std::deque<std::string> write_message_;
    std::string read_message_buffer_; // 消息缓冲区，如果接受到的消息不完整，先存起来等下个 TCP 包

    std::shared_ptr<MessageSubject> message_subject_;
    bool is_connected_;
    boost::asio::ip::tcp::resolver::results_type endpoints_;

    boost::asio::deadline_timer reconnect_timer_;
};

}