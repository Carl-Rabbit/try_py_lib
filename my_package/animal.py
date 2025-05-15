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
Animal = _core.Animal
Dog = _core.Dog
Cat = _core.Cat