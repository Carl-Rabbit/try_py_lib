#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

std::string cpp_internal_logic(const std::string &input) {
    if (input.empty()) {
        throw std::runtime_error("Input string cannot be empty in C++");
    }
    // 假设这里有一些复杂的 C++ 处理
    return "Processed '" + input + "' in C++";
}

int cpp_add_numbers(int a, int b) {
    return a + b;
}