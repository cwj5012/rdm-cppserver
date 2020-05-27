#include "ChatServer.h"
#include <rdm/config/YamlConfig.h>

int main(int argc, char* argv[]) {
    std::string path{"/home/me/test/test.yaml"};
    auto yaml = rdm::YamlConfig(std::move(path));
    yaml.parse();


    auto service = std::make_shared<ChatServer>();
    service->init();
    service->run();

    return 0;
}