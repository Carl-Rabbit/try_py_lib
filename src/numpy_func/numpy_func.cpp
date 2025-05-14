#include <iostream>
#include <vector>
#include <stdexcept> // 用于 std::runtime_error

#include "numpy_func/numpy_func.h"

// pybind11 namespace alias
namespace py = pybind11;

// C++ 函数，处理一个 NumPy 数组 (int类型)
py::array_t<int> cpp_numpy_array_plus(py::array_t<int> arr, int value) {
    // 获取 NumPy 数组的缓冲区信息
    py::buffer_info buf = arr.request();
    
    // 检查数组的类型是否为 int
    if (buf.format != py::format_descriptor<int>::format()) {
        throw std::runtime_error("Input array must be of type int");
    }
    
    // 获取数组的指针和大小
    int *ptr = static_cast<int *>(buf.ptr);
    size_t size = buf.size;

    // 遍历数组并加上指定的值
    for (size_t i = 0; i < size; ++i) {
        ptr[i] += value;
    }

    std::cout << "C++ (lib): cpp_numpy_array_plus 已处理数组，添加了 " << value << "。" << std::endl;
    return arr;
}

// C++ 函数，创建一个NumPy数组 (double类型) 并返回
py::array_t<int> cpp_create_numpy_array() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    
    // 创建一个NumPy数组。pybind11 会处理内存分配。
    // 当从 std::vector 创建时，数据会被复制。
    py::array_t<int> arr(data.size());
    py::buffer_info buf = arr.request();
    int *ptr = static_cast<int *>(buf.ptr);
    std::copy(data.begin(), data.end(), ptr);

    std::cout << "C++ (lib): create_numpy_array_in_lib 已创建数组，包含 " << data.size() << " 个元素。" << std::endl;
    return arr;
}
