#pragma once

#include <iostream>
#include <string>

#include "animal.h"

class Cat: public Animal {
public:
    Cat() = default;
    ~Cat() override = default;

    void make_sound() const override;
};