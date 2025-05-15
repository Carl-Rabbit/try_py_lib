#include <stdexcept>

#include "torch_func/torch_func.h"


torch::Tensor cpp_add_tensors(const torch::Tensor &a, const torch::Tensor &b) {
    // 检查输入张量的维度是否相同
    if (a.dim() != b.dim()) {
        throw std::invalid_argument("Input tensors must have the same number of dimensions.");
    }

    // 检查输入张量的形状是否相同
    for (int i = 0; i < a.dim(); ++i) {
        if (a.size(i) != b.size(i)) {
            throw std::invalid_argument("Input tensors must have the same shape.");
        }
    }

    // 执行张量加法
    return a + b;
}

torch::Tensor cpp_get_range_tensor(const int start, const int end) {
    // 检查输入范围是否合法
    if (start >= end) {
        throw std::invalid_argument("Start must be less than end.");
    }

    // 创建一个范围张量
    return torch::arange(start, end);
}