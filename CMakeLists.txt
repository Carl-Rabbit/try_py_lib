# CMakeLists.txt
cmake_minimum_required(VERSION 3.16) # 与 pyproject.toml 中要求一致或更高
project(my_package_cpp_core LANGUAGES CXX) # 项目名可以任意，但清晰为好

set(CONDA_PREFIX $ENV{CONDA_PREFIX})
message(STATUS "CONDA_PREFIX: ${CONDA_PREFIX}")

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

include_directories(${PROJECT_SOURCE_DIR}/include)

include(FetchContent)

# used for pybind::embed
find_package(pybind11 REQUIRED)
find_package(Python COMPONENTS Interpreter Development.Embed REQUIRED)
message(STATUS "PYTHON_SITE_PACKAGES : ${PYTHON_SITE_PACKAGES}")

# torch
find_package(Torch REQUIRED)
if (NOT TARGET torch)
    message(FATAL_ERROR "Torch not found.")
endif()
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS})

# googletest
# MUST be placed after setting CMAKE_CXX_FLAGS
# because googletest will use the CMAKE_CXX_FLAGS to compile
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests/cpp)