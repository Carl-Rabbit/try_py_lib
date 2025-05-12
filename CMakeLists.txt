# CMakeLists.txt
cmake_minimum_required(VERSION 3.16) # 与 pyproject.toml 中要求一致或更高
project(my_package_cpp_core LANGUAGES CXX) # 项目名可以任意，但清晰为好

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)