#pragma once

#include <pybind11/numpy.h>

// Forward declaration of pybind11 namespace
namespace py = pybind11;

/**
 * @brief 处理一个 int 类型的 NumPy 数组。
 * * 打印数组的维度、形状和元素。
 * 此函数从 C++ 库中调用。
 * * @param arr 要处理的 NumPy 数组。
 */
py::array_t<int> cpp_numpy_array_plus(py::array_t<int> arr, int value);

/**
 * @brief 在 C++ 中创建一个 int 类型的 NumPy 数组。
 * * 此函数从 C++ 库中调用。
 * * @return py::array_t<int> 创建的 NumPy 数组。
 */
py::array_t<int> cpp_create_numpy_array();

