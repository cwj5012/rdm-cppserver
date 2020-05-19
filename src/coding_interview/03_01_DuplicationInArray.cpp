/**
 * 面试题3（一）：找出数组中重复的数字
 * 题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
 * 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
 * 那么对应的输出是重复的数字2或者3。
 *
 * 参数:
 *        numbers:     一个整数数组
 *        length:      数组的长度
 *        duplication: (输出) 数组中的一个重复的数字
 * 返回值:
 *        true  - 输入有效，并且数组中存在重复的数字
 *        false - 输入无效，或者数组中没有重复的数字
 * bool duplicate(int numbers[], int length, int* duplication)
 */

#include <catch2/catch.hpp>
#include <algorithm>

bool duplicate(int numbers[], int length, int* duplication) {
    if (numbers == nullptr || length <= 0)
        return false;

    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0 || numbers[i] > length - 1)
            return false;
    }

    for (int i = 0; i < length; ++i) {
        if (numbers[i] != i) {
            if (numbers[i] == numbers[numbers[i]]) {
                *duplication = numbers[i];
                return true;
            }
            std::swap(numbers[i] , numbers[numbers[i]]);
        }
    }
    return false;
}

/************************************************************************
 ********************************* 测试 *********************************
 ************************************************************************/

bool contains(const int array[], int length, int number) {
    for (int i = 0; i < length; ++i) {
        if (array[i] == number)
            return true;
    }
    return false;
}

bool test(int numbers[], int lengthNumbers, int expected[], int expectedExpected, bool validArgument) {
    int duplication;
    bool validInput = duplicate(numbers, lengthNumbers, &duplication);

    if (validArgument == validInput) {
        if (validArgument) {
            return contains(expected, expectedExpected, duplication);
        } else
            return true; // Passed
    } else {
        return false; // FAILED
    }
}

TEST_CASE("03_01_DuplicationInArray_1") {
    int numbers[] = {2, 1, 3, 1, 4};
    int duplications[] = {1};
    REQUIRE(test(numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true));
}

TEST_CASE("03_01_DuplicationInArray_2") {
    int numbers[] = {2, 4, 3, 1, 4};
    int duplications[] = {4};
    REQUIRE(test(numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true));
}

TEST_CASE("03_01_DuplicationInArray_3") {
    int numbers[] = {2, 4, 2, 1, 4};
    int duplications[] = {2, 4};
    REQUIRE(test(numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true));
}

TEST_CASE("03_01_DuplicationInArray_4") {
    int numbers[] = {2, 1, 3, 0, 4};
    int duplications[] = {-1}; // not in use in the test function
    REQUIRE(test(numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false));
}

TEST_CASE("03_01_DuplicationInArray_5") {
    int numbers[] = {2, 1, 3, 5, 4};
    int duplications[] = {-1}; // not in use in the test function
    REQUIRE(test(numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false));
}

TEST_CASE("03_01_DuplicationInArray_6") {
    int* numbers = nullptr;
    int duplications[] = {-1}; // not in use in the test function
    REQUIRE(test(numbers, 0, duplications, sizeof(duplications) / sizeof(int), false));
}
