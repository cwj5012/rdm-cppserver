#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

#include "FileSystem.h"

namespace rdm {

void FileSystem::setCurrentPath() {
    setCurrentPath(FileSystem::getProgramDir());
}

void FileSystem::setCurrentPath(const std::string& path) {
    boost::filesystem::current_path(path);
}

std::string FileSystem::getProgramPath() {
    return boost::dll::program_location().string();
}

std::string FileSystem::getProgramDir() {
    return boost::dll::program_location().parent_path().string();
}

std::string FileSystem::getFileExt(const std::string& path) {
    boost::filesystem::path p(path);
    return p.extension().string();
}
}