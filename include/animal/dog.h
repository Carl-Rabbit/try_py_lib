#pragma once

#include <iostream>
#include <string>

#include "animal.h"

class Dog: public Animal {
public:
    Dog() = default;
    ~Dog() override = default;

    void make_sound() const override;
};
