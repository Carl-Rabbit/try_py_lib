#pragma once

#include <torch/extension.h>
// pybind11/pybind11.h 通常会被 torch/extension.h 包含

torch::Tensor cpp_add_tensors(const torch::Tensor &a, const torch::Tensor &b);

torch::Tensor cpp_get_range_tensor(const int start, const int end);