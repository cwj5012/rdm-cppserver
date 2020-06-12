#include "Client.h"

int main(int argc, char* argv[]) {
    auto service = std::make_shared<Client>();
    service->setConfigKey("master_server");
    service->setConfigPath("../../config/all.yaml");
    service->init();
    service->run();
    return 0;
}