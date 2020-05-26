#pragma once

#include <memory>

#include <rdm/observer/Observer.h>
#include <rdm/module/DataModule.h>
#include <rdm/service/Service.h>

#include "User.h"

class ChatRoom final : public rdm::IObserver, rdm::DataModule {
public:
    using uptr = std::unique_ptr<ChatRoom>;

    explicit ChatRoom(rdm::Service* service, uint64_t id);
    ~ChatRoom() override;

    void doOnMessage(const rdm::NetMsg* net_msg) override;

private:
    bool init() override;
    bool loadData() override;
    void release() override;
    [[nodiscard]] uint8_t status() const override;

private:
    uint64_t id_{0};
    std::map<uint64_t, std::unique_ptr<User>> users_;
    std::shared_ptr<rdm::Service> service_;
};


