#include "ChatServer.h"

#include <rdm/log/Logger.h>

ChatServer::ChatServer() {

}

ChatServer::~ChatServer() {

}

bool ChatServer::onInit() {
    LOG_INFO("ChatServer::onInit");
    return true;
}

void ChatServer::onRun() {

}

bool ChatServer::onExit() {
    return true;
}
