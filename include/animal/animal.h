#pragma once

class Animal {
public:
    virtual ~Animal() = default;
    virtual void make_sound() const = 0;
};
