#include <iostream>
#include "../rdm/submodule/SubClass.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto a = SubClass();
    a.print();

    // 测试产生 core dump
    // int *p = NULL;
    // *p = 0;

    return 0;
}
