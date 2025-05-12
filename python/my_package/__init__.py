# my_package/__init__.py

# 从封装模块 (wrapper.py) 导入你希望公开的 API
from .wrapper import process_data, add, Calculator
# 如果有其他 Python 模块，也可以从这里导入
# from .other_module import some_utility

# 定义包的版本号，这是一个好习惯
# 注意：版本号最好只在一个地方定义（例如 pyproject.toml），然后其他地方引用它
# 这里我们假设版本在 pyproject.toml 中定义，可以通过 importlib.metadata 读取
try:
    import importlib.metadata
    # __name__ 在这里就是包名 "my_package"
    __version__ = importlib.metadata.version(__name__)
except importlib.metadata.PackageNotFoundError:
    # 如果包尚未安装（例如在开发过程中直接运行脚本），则设置默认值
    __version__ = "0.0.0-unknown"

# (可选但推荐) 定义 __all__ 列表
# 这控制了当用户执行 'from my_package import *' 时导入哪些名称
# 它也是一个明确的信号，表明哪些是公共 API
__all__ = [
    'process_data',
    'add',
    'Calculator',
    # 'some_utility',
    '__version__',
]

# 可以在这里添加包级别的初始化代码（如果需要）
# print(f"my_package version {__version__} initialized.")
