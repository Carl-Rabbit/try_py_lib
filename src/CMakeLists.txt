# 查找 pybind11 包
# scikit-build-core 会确保 pybind11 在 CMake 搜索路径中
find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(animal)
add_subdirectory(numpy_func)
add_subdirectory(torch_func)

# 添加 C++ 扩展模块
# 目标名 _core (与 PYBIND11_MODULE 中的第一个参数一致)
pybind11_add_module(_core
    SHARED # 指定构建共享库 (.so/.pyd)
    _core.cpp # C++ 源文件路径 (相对于 CMakeLists.txt)
)
target_link_libraries(_core PUBLIC _animal)
target_link_libraries(_core PUBLIC _numpy_func)
target_link_libraries(_core PUBLIC _torch_func)

set(libtorch_SOURCE_DIR ${PYTHON_SITE_PACKAGES}/torch)
message(STATUS "include libtorch_SOURCE_DIR: ${libtorch_SOURCE_DIR}")
target_include_directories(_core PUBLIC ${libtorch_SOURCE_DIR}/include ${libtorch_SOURCE_DIR}/include/torch/csrc/api/include)
# link all torch libraries in ${libtorch_SOURCE_DIR}/lib
file(GLOB TORCH_LIBRARIES "${libtorch_SOURCE_DIR}/lib/*")
message(STATUS "link TORCH_LIBRARIES: ${TORCH_LIBRARIES}")
target_link_libraries(_core PRIVATE ${TORCH_LIBRARIES})

if(UNIX AND NOT APPLE) # Linux 系统
    # TORCH_INSTALL_PREFIX 通常由 find_package(Torch) 设置，指向 libtorch 安装的根目录
    # 例如，在 Conda 环境中可能是 .../lib/pythonX.Y/site-packages/torch
    if(DEFINED TORCH_INSTALL_PREFIX)
        set(TORCH_LIBRARY_DIR "${TORCH_INSTALL_PREFIX}/lib")
        message(STATUS "为 _core 设置 RPATH，使其指向 Torch 库目录: ${TORCH_LIBRARY_DIR}")

        # 为安装后的目标 _core 设置 RPATH
        # $ORIGIN 表示 _core.so 文件所在的目录
        set_target_properties(_core PROPERTIES
            INSTALL_RPATH "$ORIGIN:${TORCH_LIBRARY_DIR}"
        )
        # 同时为构建树中的目标 _core 设置 RPATH，这样在构建目录中也能直接运行/测试
        set_target_properties(_core PROPERTIES
            BUILD_RPATH "${TORCH_LIBRARY_DIR}"
        )
        # 此设置确保为安装设置的 RPATH 也在构建树中使用
        set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    else()
        message(WARNING "TORCH_INSTALL_PREFIX 未被 find_package(Torch) 定义。 \
                         libtorch 的 RPATH 可能未正确设置。 \
                         请确保 libtorch 在标准系统路径中，或已配置 LD_LIBRARY_PATH。")
    endif()
endif()

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
            _torch_func
        DESTINATION 
            my_package
        )