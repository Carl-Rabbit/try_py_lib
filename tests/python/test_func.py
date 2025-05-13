from my_package import func

def test_add():
    assert func.add(1, 2) == 3
    assert func.add(-1, 1) == 0
    assert func.add(-1, -1) == -2
    assert func.add(0, 0) == 0
