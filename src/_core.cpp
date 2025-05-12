#include <pybind11/pybind11.h>
#include <string>
#include <stdexcept> // 用于 C++ 异常

namespace py = pybind11;

// --- 你的 C++ 核心功能 ---
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
// --- End of C++ core logic ---


// --- Pybind11 绑定 ---
// 模块名 _core 需要与 CMakeLists.txt 中定义的扩展名匹配
PYBIND11_MODULE(_core, m) {
    m.doc() = "Internal C++ core module for my_package (don't use directly)"; // 模块文档字符串

    // 绑定 C++ 函数
    m.def("cpp_internal_logic", &cpp_internal_logic,
          "Internal C++ processing function",
          py::arg("input")); // 使用 py::arg 指定参数名

    m.def("cpp_add_numbers", &cpp_add_numbers,
          "Adds two integers using C++",
          py::arg("a"), py::arg("b"));

    // 如果需要，在这里绑定 C++ 类等
    // py::class_<MyCppClass>(m, "MyCppClass")
    //     .def(py::init<>())
    //     .def("some_method", &MyCppClass::some_method);
}
