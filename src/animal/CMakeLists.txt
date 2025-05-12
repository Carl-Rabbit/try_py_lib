file(GLOB_RECURSE CPP_SOURCES *.cpp)

message(STATUS "C++ sources for _animal: ${CPP_SOURCES}")
add_library(_animal SHARED ${CPP_SOURCES})
