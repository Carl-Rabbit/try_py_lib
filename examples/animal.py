# examples/hello.py (或在 Python 解释器中)
import my_package
from my_package import animal

print(f"Using my_package version: {my_package.__version__}")

# 调用 Python 封装函数
try:
    cat = animal.Cat()
    cat.make_sound()
    
    dog = animal.Dog()
    dog.make_sound()

except ValueError as e:
    print(f"Caught expected ValueError: {e}")
except Exception as e:
    print(f"Caught unexpected error: {e}")