#include "WebCommand.h"

#include <rdm/log/Logger.h>
#include <rdm/net/NetServer.h>
#include <rdm/net/NetManager.h>
#include <rdm/message/Codec.h>
#include <rdm/protocol/command.pb.h>

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
    auto opcode = static_cast<MessageType>(rdm::byte4ToUint32(*net_msg->getBuf()));
    switch (opcode) {
        case MessageType::kCommand: {
            rdm::pb::Command out;
            if (rdm::decodeE(*net_msg->getBuf(), &out)) {
                LOG_INFO("{}", out.args());
            } else {
                LOG_ERROR("decode error, opcode {}", opcode);
            }
        }
            break;
        case MessageType::kNone: {

        }
            break;
        default:
            break;
    }
}

bool WebCommand::init() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    service_.lock()->getNetServer()->registMessage(static_cast<uint32_t>(MessageType::kCommand), this);

    return true;
}

void WebCommand::release() {

}

uint8_t WebCommand::status() const {
    return 0;
}



