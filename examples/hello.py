# examples/hello.py (或在 Python 解释器中)
import my_package

print(f"Using my_package version: {my_package.__version__}")

# 调用 Python 封装函数
try:
    result = my_package.process_data("Data from Python", verbose=True)
    print(f"Success: {result}")

    # 测试默认参数
    sum_result = my_package.add(10) # num2 默认为 5
    print(f"Sum (10 + default 5): {sum_result}")

    sum_result2 = my_package.add(10, 20)
    print(f"Sum (10 + 20): {sum_result2}")

    # 使用 Python 类
    calc = my_package.Calculator(offset=100)
    class_sum = calc.add(3, 4)
    print(f"Calculator sum (3 + 4 + offset 100): {class_sum}")
    class_process = calc.process("Class Input")
    print(f"Calculator process: {class_process}")


    # 测试错误处理
    print("\nTesting error handling:")
    my_package.process_data("") # 应该会引发 ValueError

except ValueError as e:
    print(f"Caught expected ValueError: {e}")
except Exception as e:
    print(f"Caught unexpected error: {e}")