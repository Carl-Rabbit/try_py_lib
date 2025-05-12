# my_package/wrapper.py
import sys
from typing import Optional # 用于类型提示

try:
    # 关键: 使用相对导入来引入同一包内的 C++ 扩展模块
    # '.' 代表当前目录 (my_package)
    from . import _core
except ImportError as e:
    # 提供一个友好的错误信息，以防 C++ 模块未编译或找不到
    # 这在开发过程中很有用
    print(
        "Error: Could not import the C++ core module (_core).\n"
        "Ensure the package is built and installed correctly.\n"
        "Try running 'pip install .' or 'pip install -e .' in the project root.",
        file=sys.stderr # 打印到标准错误
    )
    # 可以选择重新抛出异常，或者让后续代码在访问 _core 时失败
    raise ImportError(
        "C++ core module (_core) not found. Build the package first."
    ) from e

# --- Python 公共 API ---

def process_data(data: str, *, verbose: bool = False) -> Optional[str]:
    """
    Processes the input data using the C++ core.

    This is the user-facing Python function.

    Args:
        data: The string data to process.
        verbose: If True, print verbose messages (pure Python logic).

    Returns:
        The processed string, or None if input is invalid.

    Raises:
        ValueError: If the input data is empty (converted from C++ exception).
    """
    if verbose:
        print(f"Python wrapper: Preparing to process data: '{data}'")

    if not isinstance(data, str):
        # 可以在 Python 层添加额外的类型检查
        raise TypeError("Input 'data' must be a string.")

    try:
        # 调用底层的 C++ 函数
        result = _core.cpp_internal_logic(data)
        if verbose:
            print("Python wrapper: C++ core processing successful.")
        return f"Python Wrapper Result: {result}"
    except RuntimeError as cpp_error:
        # 捕获 C++ 抛出的 std::runtime_error (pybind11 会将其转换为 RuntimeError)
        # 并将其转换为更 Pythonic 的 ValueError
        if verbose:
            print(f"Python wrapper: Caught error from C++ core: {cpp_error}")
        raise ValueError(f"Invalid input provided to C++ core: {cpp_error}") from cpp_error
    except Exception as e:
        # 捕获其他可能的意外错误
        print(f"Python wrapper: An unexpected error occurred: {e}", file=sys.stderr)
        raise # 重新抛出未知错误

def add(num1: int, num2: int = 5) -> int:
    """
    Adds two numbers using the C++ core, with a Python default value.

    Args:
        num1: The first number.
        num2: The second number (defaults to 5).

    Returns:
        The sum of num1 and num2.
    """
    # 直接调用 C++ 函数，利用 Python 添加默认参数
    return _core.cpp_add_numbers(num1, num2)

# 也可以定义一个 Python 类来封装 C++ 功能
class Calculator:
    """A simple calculator using the C++ core."""
    def __init__(self, offset: int = 0):
        self._offset = offset # 纯 Python 状态

    def add(self, a: int, b: int) -> int:
        """Adds two numbers plus an offset."""
        core_sum = _core.cpp_add_numbers(a, b)
        return core_sum + self._offset

    def process(self, text: str) -> str:
        """Processes text using the core logic."""
        # 可以在类方法中调用 C++ 函数
        return _core.cpp_internal_logic(text)
