/**
 * todo cwj 目前没用到这个类
 * 记录所有 socket 连接
 */

#pragma once

#include <map>
#include <cstdint>

#include "TcpConn.h"

namespace rdm {

class NetConnectionManager {
public:
    NetConnectionManager();
    ~NetConnectionManager();

    /**
     * 获取服务器连接
     * @param type 服务器类型
     * @param id 服务器 ID
     * @return
     */
    TcpConn::sptr getServerConnection(uint32_t type, uint32_t id) const;

    /**
     * 获取客户端连接
     * @param id 玩家 ID
     * @return
     */
    TcpConn::sptr getClientConnection(uint32_t id) const;

    /**
     * 获取服务端连接数量
     * @param type 服务器类型
     * @return
     */
    int32_t getServerConnectionCount(uint32_t type) const;

    /**
     * 获取客户端连接数量
     * @return
     */
    int32_t getClientConnectionCount() const;

    /**
     * 添加服务器连接
     * @param conn
     * @param type
     * @param id
     * @return
     *  true 添加成功
     *  false 如果已经存在相同类型和 ID 的记录，则失败
     */
    bool pushServerConnection(TcpConn::sptr conn, uint32_t type, uint32_t id);

    /**
     * 添加服客户端连接
     * @param conn
     * @param id
     * @return
     *  true 添加成功
     *  false 如果已经存在相同 ID 的记录，则失败
     */
    bool pushClientConnection(TcpConn::sptr conn, uint32_t id);

    bool release();

private:
    uint32_t server_uid_{0};
    uint32_t client_uid_{0};
    std::map<uint32_t, std::map<uint32_t, TcpConn::sptr>> server_connections_;
    std::map<uint32_t, TcpConn::sptr> client_connections_;
};

}
