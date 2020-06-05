#include "MasterServer.h"
#include <rdm/config/YamlConfig.h>

int main(int argc, char* argv[]) {
    auto service = std::make_shared<MasterServer>();
    service->setConfigPath("../../config/master.yaml");
    service->init();
    service->run();
    return 0;
}