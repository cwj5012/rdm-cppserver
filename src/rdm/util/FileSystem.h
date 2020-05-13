#pragma once

#include <string>

namespace rdm
{

    class FileSystem
    {
    public:
        FileSystem() = delete;

        ~FileSystem() = default;

        /**
         * 设置程序可执行文件所在目录，为工作路径
         */
        static void setCurrentPath();

        /**
         * 设置程序工作路径
         * @param path
         */
        static void setCurrentPath(const std::string& path);

        /**
         * 获取程序可执行文件的完整路径，包括文件名
         * @return
         */
        static std::string getProgramPath();

        /**
         * 获取程序可执行文件所在目录
         * @return
         */
        static std::string getProgramDir();

        /**
         * 获取文件扩展名
         * @param path
         * @return
         */
        static std::string getFileExt(const std::string& path);

    private:

    };

}