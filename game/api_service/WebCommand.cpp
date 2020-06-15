#include "WebCommand.h"

#include <rdm/log/Logger.h>
#include <rdm/net/NetServer.h>

#include "MessageType.h"
#include "ApiService.h"

WebCommand::WebCommand(const std::shared_ptr<ApiService>& service)
        : service_(service) {

}

WebCommand::~WebCommand() {
    std::stringstream ss;
    ss << this;
    LOG_DEBUG("{}, {}", __PRETTY_FUNCTION__, ss.str());
}

void WebCommand::doOnMessage(const rdm::NetMsg* net_msg) {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

bool WebCommand::init() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    service_.lock()->getNetServer()->registMessage(static_cast<uint32_t>(MessageType::kCommand), this);
    service_.lock()->getNetServer()->registMessage(111, this);

    return true;
}

void WebCommand::release() {

}

uint8_t WebCommand::status() const {
    return 0;
}



