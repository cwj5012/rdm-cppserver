#include <catch2/catch.hpp>

#include "../FileSystem.h"
#include "../../log/Logger.h"

using namespace rdm;

TEST_CASE("FileSystem-test", "[]") {
    LOG_DEBUG("program path: {}", FileSystem::getProgramPath());
    LOG_DEBUG("program dir: {}", FileSystem::getProgramDir());
    FileSystem::setCurrentPath();
}

TEST_CASE("FileSystem-getFileExt", "[]") {
    std::string path = "c:/a/b/c.txt.bak";
    REQUIRE(".bak" == FileSystem::getFileExt(path));
}