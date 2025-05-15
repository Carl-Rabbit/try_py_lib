if(NOT TARGET GTest::gtest)
    message(FATAL_ERROR "GTest not found.")
endif()

add_subdirectory(func)
add_subdirectory(animal)
add_subdirectory(numpy_func)
add_subdirectory(torch_func)