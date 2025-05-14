#pragma once

#include <pybind11/pybind11.h>

#include "numpy_func/numpy_func.h"

namespace py = pybind11;

void init_bindings_numpy_func(py::module_& m) {
    m.def("cpp_numpy_array_plus", &cpp_numpy_array_plus,
          "Add a NumPy array from C++",
          py::arg("arr"), py::arg("value")); // 使用 py::arg 指定参数名
    m.def("cpp_create_numpy_array", &cpp_create_numpy_array,
          "Create a NumPy array in C++");
}