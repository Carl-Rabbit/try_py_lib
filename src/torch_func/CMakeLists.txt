file(GLOB_RECURSE CPP_SOURCES *.cpp)

message(STATUS "C++ sources for _torch_func: ${CPP_SOURCES}")
add_library(_torch_func SHARED ${CPP_SOURCES})
target_link_libraries(_torch_func PUBLIC torch pybind11::pybind11)
