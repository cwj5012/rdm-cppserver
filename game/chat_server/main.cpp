#include "ChatServer.h"

int main(int argc, char* argv[]) {
    auto service = std::make_shared<ChatServer>();
    service->setConfigKey("chat_server");
    service->setConfigPath("../../config/all.yaml");
    service->init();
    service->run();
    return 0;
}