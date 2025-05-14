# 查找 pybind11 包
# scikit-build-core 会确保 pybind11 在 CMake 搜索路径中
find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(animal)
add_subdirectory(numpy_func)

# 添加 C++ 扩展模块
# 目标名 _core (与 PYBIND11_MODULE 中的第一个参数一致)
pybind11_add_module(_core
    SHARED # 指定构建共享库 (.so/.pyd)
    _core.cpp # C++ 源文件路径 (相对于 CMakeLists.txt)
)
target_link_libraries(_core PRIVATE _animal)
target_link_libraries(_core PRIVATE _numpy_func)

set_target_properties(_core PROPERTIES
    INSTALL_RPATH "$ORIGIN" # 当安装时
    BUILD_WITH_INSTALL_RPATH TRUE # 也让构建树中的 RPATH 生效
)

# (推荐) 设置 C++ 标准
# 使用 PRIVATE 意味着这个要求只应用于 _core 目标本身
target_compile_features(_core PRIVATE cxx_std_17)

# (可选) 添加编译优化标志 (例如，只在 Release 构建时)
# scikit-build-core 通常处理构建类型，但你可以明确指定
# target_compile_options(_core PRIVATE $<$<CONFIG:Release>:$<$<NOT:$<PLATFORM_ID:Windows>>:-O2>> $<$<CONFIG:Release>:$<$<PLATFORM_ID:Windows>:/O2>>)

# (可选) 如果你的 C++ 代码需要包含其他目录
# target_include_directories(_core PRIVATE path/to/other/includes)

# (可选) 如果你的 C++ 代码需要链接其他库
# find_package(OtherLib REQUIRED)
# target_link_libraries(_core PRIVATE OtherLib::OtherLib)

# --- 安装规则 ---
# scikit-build-core 会自动处理将构建好的 _core 模块
# 安装到 Python 包的正确位置 (my_package)
# 通常不需要在这里添加额外的 install() 命令用于 _core 模块本身
install(TARGETS 
            _core 
            _animal
            _numpy_func
        DESTINATION 
            my_package
        )