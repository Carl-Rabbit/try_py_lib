#include "gtest/gtest.h"
#include <pybind11/embed.h> // 用于嵌入Python解释器和GIL管理
#include <torch/torch.h> // 用于 torch::Tensor

#include "torch_func/torch_func.h" 

#include <vector>
#include <iostream>
#include <string>      // 确保包含 <string>
#include <stdexcept> // For std::runtime_error

namespace py = pybind11;

// 定义一个测试固件 (Test Fixture)
class TorchFuncTest : public ::testing::Test {
protected:
    // Python解释器守护程序，确保只初始化和终止一次
    // 对于整个测试套件 (所有使用此固件的测试)
    static py::scoped_interpreter guard;
    
    // GIL 获取器，每个测试用例执行时都会创建一个实例
    // 从而为该测试用例获取GIL
    py::gil_scoped_acquire gil_acq;

    // 可选：在每个测试用例开始前导入numpy
    // py::module_ np;

public:
    // SetUpTestSuite 在此固件的第一个测试开始前调用
    static void SetUpTestSuite() {
        // guard 已经在静态成员声明时构造，这里不需要额外操作
        // 如果需要更复杂的初始化，可以在这里进行
        std::cout << "GTest: Python interpreter initialized for TorchFuncTest suite." << std::endl;
    }

    // TearDownTestSuite 在此固件的最后一个测试结束后调用
    static void TearDownTestSuite() {
        // guard 会在程序结束时自动析构，终止解释器
        std::cout << "GTest: Python interpreter will be finalized by scoped_interpreter." << std::endl;
    }

    // 构造函数：每个测试用例对象创建时调用
    TorchFuncTest() {
        // gil_acq 在成员初始化列表中构造，自动获取GIL
        // try {
        //     np = py::module_::import("numpy");
        //     if (!np) {
        //         FAIL() << "GTest: Failed to import NumPy module in test constructor.";
        //     }
        //     std::cout << "GTest: NumPy module imported for a test case." << std::endl;
        // } catch (const py::error_already_set& e) {
        //     FAIL() << "GTest: Failed to import NumPy in test constructor: " << e.what() << "\nPython error: " << getPythonError();
        // }
        std::cout << "GTest: GIL acquired for a test case." << std::endl;
    }

    // 析构函数：每个测试用例对象销毁时调用
    ~TorchFuncTest() override {
        // gil_acq 会自动析构，释放GIL
        std::cout << "GTest: GIL released for a test case." << std::endl;
    }

    // 辅助函数来获取Python错误信息 (可选, 但推荐)
    std::string getPythonError() {
        if (PyErr_Occurred()) {
            PyObject *ptype_obj, *pvalue_obj, *ptraceback_obj;
            PyErr_Fetch(&ptype_obj, &pvalue_obj, &ptraceback_obj); // 获取错误信息，并清除当前错误状态
            PyErr_NormalizeException(&ptype_obj, &pvalue_obj, &ptraceback_obj);

            py::handle ptype(ptype_obj); 
            py::handle pvalue(pvalue_obj); 
            py::handle ptraceback(ptraceback_obj);

            std::string err_msg = "Python Exception: ";
            if (ptype && ptype.ptr() != Py_None) { 
                err_msg += std::string(py::str(ptype.attr("__name__"))); // 显式转换为 std::string
            } else {
                err_msg += "Unknown type";
            }

            if (pvalue && pvalue.ptr() != Py_None) {
                // *** 修改点在这里 ***
                err_msg += ": " + std::string(py::str(pvalue)); // 显式转换为 std::string
            }
            
            // 恢复错误状态，以便pybind11或其他调用者可以再次看到它（如果需要）
            // 或者清除它，如果你不希望它传播
            // PyErr_Restore(ptype.release().ptr(), pvalue.release().ptr(), ptraceback.release().ptr());
            // 对于测试报告，通常获取信息后就可以清除了，避免干扰后续。
            // PyErr_Clear(); // 如果PyErr_Fetch后不调用Restore，错误状态已清除。
            // 如果调用了Restore，则需要Clear。由于Fetch已经清除了，这里不需要额外操作。
            // py::error_already_set::discard_as_unraisable(); // 另一种处理方式
            return err_msg;
        }
        return "No Python error occurred or error already handled.";
    }
};

// 初始化静态成员 guard
py::scoped_interpreter TorchFuncTest::guard{};


// 使用 TEST_F 宏来使用我们的固件
TEST_F(TorchFuncTest, TestCppAddTensors) {
  try {
    // 创建两个张量
    torch::Tensor a = torch::tensor({1, 2, 3});
    torch::Tensor b = torch::tensor({4, 5, 6});

    // 调用 C++ 函数
    torch::Tensor result = cpp_add_tensors(a, b);

    // 检查结果
    ASSERT_EQ(result.size(0), 3) << "Result tensor size mismatch.";
    ASSERT_EQ(result[0].item<int>(), 5) << "First element mismatch.";
    ASSERT_EQ(result[1].item<int>(), 7) << "Second element mismatch.";
    ASSERT_EQ(result[2].item<int>(), 9) << "Third element mismatch.";

  } catch (const py::error_already_set& e) {
    FAIL() << "Python exception caught in test: " << e.what() << "\nDetails: " << getPythonError();
  } catch (const std::exception& e) {
    FAIL() << "C++ exception caught in test: " << e.what();
  }
  // 在测试结束前再次检查Python错误状态，以捕获未被py::error_already_set包装的错误
  if (PyErr_Occurred()) {
      FAIL() << "Uncaught Python error at end of test: " << getPythonError();
  }
}

//cpp_get_range_tensor
TEST_F(TorchFuncTest, TestCppGetRangeTensor) {
  try {
    // 创建范围张量
    torch::Tensor result = cpp_get_range_tensor(0, 5);

    // 检查结果
    ASSERT_EQ(result.size(0), 5) << "Result tensor size mismatch.";
    ASSERT_EQ(result[0].item<int>(), 0) << "First element mismatch.";
    ASSERT_EQ(result[1].item<int>(), 1) << "Second element mismatch.";
    ASSERT_EQ(result[2].item<int>(), 2) << "Third element mismatch.";
    ASSERT_EQ(result[3].item<int>(), 3) << "Fourth element mismatch.";
    ASSERT_EQ(result[4].item<int>(), 4) << "Fifth element mismatch.";

  } catch (const py::error_already_set& e) {
    FAIL() << "Python exception caught in test: " << e.what() << "\nDetails: " << getPythonError();
  } catch (const std::exception& e) {
    FAIL() << "C++ exception caught in test: " << e.what();
  }
  // 在测试结束前再次检查Python错误状态，以捕获未被py::error_already_set包装的错误
  if (PyErr_Occurred()) {
      FAIL() << "Uncaught Python error at end of test: " << getPythonError();
  }
}

