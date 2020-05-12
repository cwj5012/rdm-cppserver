#include <iostream>

#include <boost/version.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char *argv[]) {
    std::cout << BOOST_VERSION << std::endl;

    boost::filesystem::path dir_path("/home/me/test");

    if (boost::filesystem::exists(dir_path))  //判断文件存在性
    {
        std::cout << "directory exist." << std::endl;
    } else {
        std::cout << "directory not exist." << std::endl;
        boost::filesystem::create_directory(dir_path);
        std::cout << "directory created." << std::endl;
    }

    return 0;
}
