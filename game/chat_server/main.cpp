#include "ChatServer.h"
#include <rdm/config/YamlConfig.h>

int main(int argc, char* argv[]) {
    auto service = std::make_shared<ChatServer>();
    service->setConfigPath("/home/me/clion-dev/learn-cpp/config/chat_room.yaml");
    service->init();
    service->run();

    return 0;
}