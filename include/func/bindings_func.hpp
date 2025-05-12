#pragma once

#include <pybind11/pybind11.h>

#include "func/func.hpp"

namespace py = pybind11;

void init_bindings_func(py::module_& m) {
    m.def("cpp_internal_logic", &cpp_internal_logic,
          "Internal C++ processing function",
          py::arg("input")); // 使用 py::arg 指定参数名

    m.def("cpp_add_numbers", &cpp_add_numbers,
          "Adds two integers using C++",
          py::arg("a"), py::arg("b"));
}