#pragma once

#include <iostream>
#include <string>

#include "animal.h"

class Dog: public Animal {
public:
    Dog() = default;
    ~Dog() override = default;

    std::string make_sound() const override;
};
