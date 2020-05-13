#include <catch2/catch.hpp>

#include "../DebugPrint.h"

using namespace rdm;

TEST_CASE("DebugPrint-StringToByteSet") {
    std::string s1 = "09AZaz";
    std::string s2 = "00110000-00111001-01000001-01011010-01100001-01111010";
    REQUIRE(DebugPrint::StringToByteSet(s1) == s2);
}

TEST_CASE("DebugPrint-StringToOctSet", "[]") {
    std::string s1 = "09AZaz";
    std::string s2 = "60-71-101-132-141-172";
    REQUIRE(DebugPrint::StringToOctSet(s1) == s2);
}

TEST_CASE("DebugPrint-StringToDecSet", "[]") {
    std::string s1 = "09AZaz";
    std::string s2 = "48-57-65-90-97-122";
    REQUIRE(DebugPrint::StringToDecSet(s1) == s2);
}

TEST_CASE("DebugPrint-StringToHexSet", "[]") {
    std::string s1 = "09AZaz";
    std::string s2 = "30-39-41-5a-61-7a";
    REQUIRE(DebugPrint::StringToHexSet(s1) == s2);
}

TEST_CASE("DebugPrint-StringToByte", "[]") {
    std::vector<std::string> vec;
    vec.emplace_back("00110000");
    vec.emplace_back("00111001");
    vec.emplace_back("01000001");
    vec.emplace_back("01011010");
    vec.emplace_back("01100001");
    vec.emplace_back("01111010");

    std::string s1 = "09AZaz";
    REQUIRE(DebugPrint::StringToByte(s1) == vec);
}

TEST_CASE("DebugPrint-StringToOct", "[]") {
    std::vector<std::string> vec;
    vec.emplace_back("60");
    vec.emplace_back("71");
    vec.emplace_back("101");
    vec.emplace_back("132");
    vec.emplace_back("141");
    vec.emplace_back("172");

    std::string s1 = "09AZaz";
    REQUIRE(DebugPrint::StringToOct(s1) == vec);
}

TEST_CASE("DebugPrint-StringToDec", "[]") {
    std::vector<std::string> vec;
    vec.emplace_back("48");
    vec.emplace_back("57");
    vec.emplace_back("65");
    vec.emplace_back("90");
    vec.emplace_back("97");
    vec.emplace_back("122");

    std::string s1 = "09AZaz";
    REQUIRE(DebugPrint::StringToDec(s1) == vec);
}

TEST_CASE("DebugPrint-StringToHex", "[]") {
    std::vector<std::string> vec;
    vec.emplace_back("30");
    vec.emplace_back("39");
    vec.emplace_back("41");
    vec.emplace_back("5a");
    vec.emplace_back("61");
    vec.emplace_back("7a");

    std::string s1 = "09AZaz";
    REQUIRE(DebugPrint::StringToHex(s1) == vec);
}

TEST_CASE("DebugPrint-CharToByte", "[]") {
    REQUIRE(DebugPrint::CharToByte('0') == "00110000");
    REQUIRE(DebugPrint::CharToByte('9') == "00111001");
    REQUIRE(DebugPrint::CharToByte('A') == "01000001");
    REQUIRE(DebugPrint::CharToByte('Z') == "01011010");
    REQUIRE(DebugPrint::CharToByte('a') == "01100001");
    REQUIRE(DebugPrint::CharToByte('z') == "01111010");
}

TEST_CASE("DebugPrint-CharToOct", "[]") {
    REQUIRE(DebugPrint::CharToOct('0') == "60");
    REQUIRE(DebugPrint::CharToOct('9') == "71");
    REQUIRE(DebugPrint::CharToOct('A') == "101");
    REQUIRE(DebugPrint::CharToOct('Z') == "132");
    REQUIRE(DebugPrint::CharToOct('a') == "141");
    REQUIRE(DebugPrint::CharToOct('z') == "172");
}

TEST_CASE("DebugPrint-CharToDec", "[]") {
    REQUIRE(DebugPrint::CharToDec('0') == "48");
    REQUIRE(DebugPrint::CharToDec('9') == "57");
    REQUIRE(DebugPrint::CharToDec('A') == "65");
    REQUIRE(DebugPrint::CharToDec('Z') == "90");
    REQUIRE(DebugPrint::CharToDec('a') == "97");
    REQUIRE(DebugPrint::CharToDec('z') == "122");
}

TEST_CASE("DebugPrint-CharToHex", "[]") {
    REQUIRE(DebugPrint::CharToHex('0') == "30"); //0x30
    REQUIRE(DebugPrint::CharToHex('9') == "39"); //0x39
    REQUIRE(DebugPrint::CharToHex('A') == "41"); //0x41
    REQUIRE(DebugPrint::CharToHex('Z') == "5a"); //0x5a
    REQUIRE(DebugPrint::CharToHex('a') == "61"); //0x61
    REQUIRE(DebugPrint::CharToHex('z') == "7a"); //0x7a
}
