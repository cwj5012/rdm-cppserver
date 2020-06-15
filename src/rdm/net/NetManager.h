/*
 * 管理 boost::asio::io_service 对象
 */

#pragma once

#include <boost/asio.hpp>

#include "../observer/MessageSubject.h"
#include "../observer/Observer.h"

namespace rdm {

class NetManager {
public:
    NetManager();

    ~NetManager();

    static NetManager& inst() {
        static NetManager obj;
        return obj;
    }

    boost::asio::io_service& getService();

    void run();

    void registMessage(const uint32_t message_type, IObserver* observer);
    void registMessage(const std::string& message_name, IObserver* observer);

    std::shared_ptr<MessageSubject> getMessageSubject();

private:
    uint32_t conn_uid_{0};
    boost::asio::io_service io_service_;
    MessageSubject::sptr message_subject_;
};

}