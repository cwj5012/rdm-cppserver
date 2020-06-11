#include <iostream>
#include "../rdm/submodule/SubClass.h"

#include <rdm/util/ExceptionHandle.h>

const int* get() {
    return new int(1);
}

int main() {
    // 初始化异常处理
    // rdm::ExceptionHandle::InitProcessExceptionHandler();
    // rdm::ExceptionHandle::InitThreadExceptionHandler();
    //
    // std::cout << "Hello, World!" << std::endl;
    // auto a = SubClass();
    // a.print();

    // 测试产生 core dump
    // int *p = NULL;
    // *p = 0;

    const int* const a = get();
    const int* b = get();


    std::cout << *a <<std::endl;
    std::cout << *b <<std::endl;
    delete a;

    return 0;
}
