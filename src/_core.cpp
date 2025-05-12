#include <pybind11/pybind11.h>
#include <string>
#include <stdexcept> // 用于 C++ 异常

#include "func/bindings_func.hpp"
#include "animal/bindings_animal.hpp"

namespace py = pybind11;

// --- Pybind11 绑定 ---
// 模块名 _core 需要与 CMakeLists.txt 中定义的扩展名匹配
PYBIND11_MODULE(_core, m) {
    m.doc() = "Internal C++ core module for my_package (don't use directly)"; // 模块文档字符串

    init_bindings_func(m); // 绑定 func 模块
    init_bindings_animal(m); // 绑定 Animal 类及其子类
}
