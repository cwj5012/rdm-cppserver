#include "ChatServer.h"

int main(int argc, char* argv[]) {
    auto service = ChatServer();
    service.init();
    service.run();
    service.exit();
    return 0;
}