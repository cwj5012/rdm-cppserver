#pragma once

#include <string>
#include <vector>
#include <regex>

namespace rdm {

class StringUtil {
public:
    StringUtil() = delete;

    ~StringUtil() = default;

    /**
     * 字符串分割
     * @param input
     * @param regex
     * @return
     * @todo 测试 inline 的性能
     */
    inline static std::vector<std::string> split(const std::string& input, const std::string& regex) {
        // passing -1 as the submatch index parameter performs splitting
        std::regex re(regex);
        std::sregex_token_iterator first{input.begin(),
                                         input.end(),
                                         re,
                                         -1};
        std::sregex_token_iterator last;

        return {first, last};
    }

    /**
     * 整数转为二进制形式
     * @param ch
     * @return
     *
     * @details 将字符依次向左移动一位，跟 10000000 与运算，得到每一位的二进制数字
     */
    static std::string charToBinary(char ch) {
        char out[9] = {0};
        for (int8_t i = 0; i < 8; i++) {
            sprintf(out + i, "%d", ((ch << i) & 0x80) != 0);
        }
        return std::string(out);
    }

};


}