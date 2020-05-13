#pragma once

#include <string>
#include <vector>

namespace rdm {

class DebugPrint {
public:

    /**
      * 获取字符串每一位（二进制）
      * 格式： xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx
      * @param cstr
      */
    static std::string StringToByteSet(const std::string& cstr);

    /**
      * 获取字符串每一位（八进制）
      * 格式： xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx
      * @param cstr
      */
    static std::string StringToOctSet(const std::string& cstr);

    /**
     * 获取字符串每一位（十进制）
     * 格式： xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx
     * @param cstr
     * @return
     */
    static std::string StringToDecSet(const std::string& cstr);

    /**
     * 获取字符串每一位（十六进制）
     * 格式： xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx
     * @param cstr
     * @return
     */
    static std::string StringToHexSet(const std::string& cstr);

    /**
     * 获取字符串每一位（二进制）
     * @param cstr
     */
    static std::vector<std::string> StringToByte(const std::string& cstr);

    /**
     * 获取字符串每一位（八进制）
     * @param cstr
     * @todo 有问题
     */
    static std::vector<std::string> StringToOct(const std::string& cstr);

    /**
     * 获取字符串每一位（十进制）
     * @param cstr
     * @todo 有问题
     */
    static std::vector<std::string> StringToDec(const std::string& cstr);

    /**
     * 获取字符串每一位（十六进制）
     * @param cstr
     * @todo 有问题
     */
    static std::vector<std::string> StringToHex(const std::string& cstr);

    /**
     * 获取字符的二进制表示
     * @param ch
     * @return
     */
    static std::string CharToByte(const char ch);

    /**
     * 获取字符的八进制表示
     * @param ch
     * @return
     */
    static std::string CharToOct(const char ch);

    /**
     * 获取字符的十进制表示
     * @param ch
     * @return
     */
    static std::string CharToDec(const char ch);

    /**
     * 获取字符的十六进制表示
     * @param ch
     * @return
     */
    static std::string CharToHex(const char ch);
};

}


