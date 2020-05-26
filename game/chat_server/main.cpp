#include "ChatServer.h"

int main(int argc, char* argv[]) {
    auto service = std::make_shared<ChatServer>();
    service->init();
    service->run();

    return 0;
}