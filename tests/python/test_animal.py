from my_package import animal

def test_cat():
    cat = animal.Cat()
    assert cat.make_sound() == "Meow!"

def test_dog():
    dog = animal.Dog()
    assert dog.make_sound() == "Woof!"