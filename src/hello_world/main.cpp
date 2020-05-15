#include <iostream>
#include "../rdm/submodule/SubClass.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto a = SubClass();
    a.print();
    return 0;
}
