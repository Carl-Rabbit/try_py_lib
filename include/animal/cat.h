#pragma once

#include <iostream>
#include <string>

#include "animal.h"

class Cat: public Animal {
public:
    Cat() = default;
    ~Cat() override = default;

    std::string make_sound() const override;
};