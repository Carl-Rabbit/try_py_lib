# CMakeLists.txt
cmake_minimum_required(VERSION 3.16) # 与 pyproject.toml 中要求一致或更高
project(my_package_cpp_core LANGUAGES CXX) # 项目名可以任意，但清晰为好

include_directories(${PROJECT_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests/cpp)