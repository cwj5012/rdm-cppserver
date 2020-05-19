/**
 * 面试题1：赋值运算符函数
 * 题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数。
 *
 * #include<cstring>
 * #include<cstdio>
 *
 * class CMyString
 * {
 * public:
 *     CMyString(char* pData = nullptr);
 *     CMyString(const CMyString& str);
 *     ~CMyString(void);
 *
 *     CMyString& operator = (const CMyString& str);
 *
 *     void Print();
 *
 * private:
 *     char* m_pData;
 * };
 */

#include <catch2/catch.hpp>
#include<cstring>
#include<algorithm>

class CMyString {
public:
    explicit CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString();

    CMyString& operator=(const CMyString& str);

    [[nodiscard]] char* getData() const;

private:
    char* m_pData;
};

CMyString::CMyString(char* pData) {
    if (pData == nullptr) {
        m_pData = new char[1];
        m_pData[0] = '\0';
    } else {
        m_pData = new char[strlen(pData) + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString& str) {
    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString() {
    delete[] m_pData;
}

CMyString& CMyString::operator=(const CMyString& str) {
    CMyString temp(str);
    std::swap(m_pData, temp.m_pData);
    return *this;
}

char* CMyString::getData() const {
    return m_pData;
}

TEST_CASE("01_AssignmentOperator_1") {
    char text[] = "Hello world";
    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    REQUIRE(strcmp(text, str2.getData()) == 0);
}

TEST_CASE("01_AssignmentOperator_2") {
    char text[] = "Hello world";
    CMyString str1(text);
    str1 = str1;

    REQUIRE(strcmp(text, str1.getData()) == 0);
}

TEST_CASE("01_AssignmentOperator_3") {
    char text[] = "Hello world";
    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;

    REQUIRE(strcmp(text, str2.getData()) == 0);
    REQUIRE(strcmp(text, str3.getData()) == 0);
}
