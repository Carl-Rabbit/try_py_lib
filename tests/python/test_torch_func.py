from my_package import torch_func
import torch

def test_add_tensors():
    # 创建两个张量
    a = torch.tensor([1, 2, 3])
    b = torch.tensor([4, 5, 6])

    # 调用 C++ 函数
    result = torch_func.add_tensors(a, b)

    # 检查结果
    assert result.size(0) == 3, "Result tensor size mismatch."
    assert result[0].item() == 5, "First element mismatch."
    assert result[1].item() == 7, "Second element mismatch."
    assert result[2].item() == 9, "Third element mismatch."

def test_get_range_tensor():
    # 创建范围张量
    result = torch_func.get_range_tensor(0, 5)

    # 检查结果
    assert result.size(0) == 5, "Result tensor size mismatch."
    assert result[0].item() == 0, "First element mismatch."
    assert result[1].item() == 1, "Second element mismatch."
    assert result[2].item() == 2, "Third element mismatch."
    assert result[3].item() == 3, "Fourth element mismatch."
    assert result[4].item() == 4, "Fifth element mismatch."
