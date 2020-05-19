#include <iostream>
#include <string>

void Fuc(std::string a){

}

int main(int argc, char* argv[]) {
    auto i{1};
    std::string a = "111111";

    std::cout <<a;
    static_assert(sizeof(i) == 4);
    return 0;
}