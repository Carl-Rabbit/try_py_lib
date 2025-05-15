#pragma once

#include <pybind11/pybind11.h>

#include "torch_func/torch_func.h"

namespace py = pybind11;

void init_bindings_torch_func(py::module_& m) {
      m.def("cpp_add_tensors", &cpp_add_tensors,
            "Adds two tensors using C++",
            py::arg("a"), py::arg("b"));
      m.def("cpp_get_range_tensor", &cpp_get_range_tensor,
            "Get a range tensor from start to end using C++",
            py::arg("start"), py::arg("end"));
}