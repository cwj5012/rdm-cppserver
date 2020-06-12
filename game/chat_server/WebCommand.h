#pragma once

#include <memory>

#include <rdm/observer/Observer.h>
#include <rdm/module/MessageModule.h>
#include <rdm/service/Service.h>

class ChatServer;
class WebCommand :
        public rdm::IObserver,
        public rdm::MessageModule {
public:
    using uptr = std::unique_ptr<WebCommand>;

    explicit WebCommand(const std::shared_ptr<ChatServer>& service);
    virtual ~WebCommand();

    void doOnMessage(const rdm::NetMsg* net_msg) override;

    bool init() override;
    void release() override;
    uint8_t status() const override;

private:
    std::weak_ptr<ChatServer> service_;
};


