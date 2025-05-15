# my_package/wrapper.py
import sys

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

import numpy as np

def numpy_array_plus(arr: np.ndarray, value: int) -> np.ndarray:
    """
    使用 C++ 扩展模块处理 NumPy 数组的函数
    这个函数将 NumPy 数组中的每个元素加上一个整数值。
    Args:
        arr: 输入的 NumPy 数组
        value: 要加上的整数值
    Returns:
        处理后的 NumPy 数组
    """
    # 调用 C++ 扩展模块中的函数
    return _core.cpp_numpy_array_plus(arr, value)

def create_numpy_array() -> np.ndarray:
    """
    创建一个 NumPy 数组的函数
    """
    # 调用 C++ 扩展模块中的函数
    return _core.cpp_create_numpy_array()