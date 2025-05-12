# Try Py Cpp Lib

```shell
conda install cmake ninja pybind11
```

```shell
# 0. (推荐) 创建并激活虚拟环境
# python -m venv venv
# source venv/bin/activate  # Linux/macOS
# .\venv\Scripts\activate    # Windows

# 1. (可选) 使用 build 工具构建 wheel 包 (不安装)
#    这会读取 pyproject.toml 并调用指定的构建后端
python -m build

# 2. 安装包 (会触发构建过程)
#    pip 会自动读取 pyproject.toml 并执行构建
pip install .

# 3. (可选) 开发模式安装
#    这对于需要修改 Python 代码的情况很有用
#    注意：修改 C++ 代码或 CMakeLists.txt 后仍需重新运行此命令
pip install -e .
```