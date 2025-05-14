file(GLOB_RECURSE CPP_SOURCES *.cpp)

message(STATUS "C++ sources for _numpy_func: ${CPP_SOURCES}")
add_library(_numpy_func STATIC ${CPP_SOURCES})
target_link_libraries(_numpy_func PUBLIC pybind11::pybind11)
set_target_properties(_numpy_func PROPERTIES POSITION_INDEPENDENT_CODE ON)
