#include <iostream>
#include <string>
#include <vector>

#include "DebugPrint.h"

namespace rdm {

std::string DebugPrint::StringToByteSet(const std::string& cstr) {
    std::string out;
    for (auto& item : StringToByte(cstr)) {
        out.append(item);
        out.append("-");
    }
    return out.substr(0, out.length() - 1);
}

std::string DebugPrint::StringToOctSet(const std::string& cstr) {
    std::string out;
    for (auto& item : StringToOct(cstr)) {
        out.append(item);
        out.append("-");
    }
    return out.substr(0, out.length() - 1);
}

std::string DebugPrint::StringToDecSet(const std::string& cstr) {
    std::string out;
    for (auto& item : StringToDec(cstr)) {
        out.append(item);
        out.append("-");
    }
    return out.substr(0, out.length() - 1);
}

std::string DebugPrint::StringToHexSet(const std::string& cstr) {
    std::string out;
    for (auto& item : StringToHex(cstr)) {
        out.append(item);
        out.append("-");
    }
    return out.substr(0, out.length() - 1);
}

std::vector<std::string> DebugPrint::StringToByte(const std::string& cstr) {
    std::vector<std::string> vec;
    for (int j = 0; j < cstr.length(); ++j) {
        vec.push_back(CharToByte(cstr[j]));
    }
    return std::move(vec);
}

std::vector<std::string> DebugPrint::StringToOct(const std::string& cstr) {
    std::vector<std::string> vec;
    for (int j = 0; j < cstr.length(); ++j) {
        vec.push_back(CharToOct(cstr[j]));
    }
    return std::move(vec);
}

std::vector<std::string> DebugPrint::StringToDec(const std::string& cstr) {
    std::vector<std::string> vec;
    for (int j = 0; j < cstr.length(); ++j) {
        vec.push_back(CharToDec(cstr[j]));
    }
    return std::move(vec);
}

std::vector<std::string> DebugPrint::StringToHex(const std::string& cstr) {
    std::vector<std::string> vec;
    for (int j = 0; j < cstr.length(); ++j) {
        vec.push_back(CharToHex(cstr[j]));
    }
    return std::move(vec);
}

std::string DebugPrint::CharToByte(const char ch) {
    char temp_ch[9];
    for (int8_t i = 0; i < 8; ++i) {
        sprintf(temp_ch + i, "%d", ((ch << i) & 0x80) != 0);
    }
    return std::move(std::string(temp_ch));
}

std::string DebugPrint::CharToOct(const char ch) {
    char temp_ch[9];
    sprintf(temp_ch, "%o", ch);
    return std::move(std::string(temp_ch));
}

std::string DebugPrint::CharToDec(const char ch) {
    char temp_ch[9];
    sprintf(temp_ch, "%d", ch);
    return std::move(std::string(temp_ch));
}

std::string DebugPrint::CharToHex(const char ch) {
    char temp_ch[9];
    sprintf(temp_ch, "%x", ch);
    return std::move(std::string(temp_ch));
}

}

