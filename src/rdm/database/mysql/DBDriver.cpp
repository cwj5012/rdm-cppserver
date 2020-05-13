#include "DBDriver.h"

namespace rdm {

DBDriver::DBDriver() {
    driver_mutex.lock();
    mDriver = get_driver_instance();
    driver_mutex.unlock();
}

int32_t DBDriver::getMajorVersion() {
    return mDriver->getMajorVersion();
}

int32_t DBDriver::getMinorVersion() {
    return mDriver->getMinorVersion();
}

int32_t DBDriver::getPatchVersion() {
    return mDriver->getPatchVersion();
}

const std::string DBDriver::getName() {
    return mDriver->getName();
}

void DBDriver::threadInit() {
    mDriver->threadInit();
}

void DBDriver::threadEnd() {
    mDriver->threadEnd();
}

sql::Driver* DBDriver::getDriver() {
    return mDriver;
}

}