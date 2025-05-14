from my_package import numpy_func
import numpy as np

def test_numpy_array_from_lib():
    # 测试 C++ 扩展模块中的 NumPy 数组处理函数
    arr = np.array([1, 2, 3])
    arr = numpy_func.numpy_array_plus(arr, 1)
    assert np.array_equal(arr, np.array([2, 3, 4])), "C++ extension did not process the array correctly"
    
def test_create_numpy_array_from_lib():
    # 测试 C++ 扩展模块中的 NumPy 数组创建函数
    arr = numpy_func.create_numpy_array()
    assert isinstance(arr, np.ndarray), "C++ extension did not return a NumPy array"
    assert arr.shape == (5,), "C++ extension returned an array with incorrect shape"
    assert np.array_equal(arr, np.array([1, 2, 3, 4, 5])), "C++ extension returned an array with incorrect values"