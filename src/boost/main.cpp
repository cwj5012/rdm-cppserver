#include <iostream>

#include <boost/version.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[]) {
    std::cout << "boost version: " << BOOST_VERSION << std::endl;

    std::string path = "/home/me/test";
    boost::filesystem::path dir_path(path);

    if (boost::filesystem::exists(dir_path))  //判断文件存在性
    {
        std::cout << path <<" dir exist." << std::endl;
    } else {
        std::cout << path <<" dir not exist." << std::endl;
        boost::filesystem::create_directory(dir_path);
        std::cout << path <<" dir created." << std::endl;
    }

    return 0;
}
