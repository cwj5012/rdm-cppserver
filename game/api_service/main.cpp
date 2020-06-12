#include "ApiService.h"
#include <rdm/config/YamlConfig.h>

int main(int argc, char* argv[]) {
    auto service = std::make_shared<ApiService>();
    service->setConfigKey("api_service");
    service->setConfigPath("../../config/all.yaml");
    service->init();
    service->run();
    return 0;
}