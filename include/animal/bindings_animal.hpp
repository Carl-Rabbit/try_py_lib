#pragma once

#include <pybind11/pybind11.h>

#include "animal/animal.h"
#include "animal/cat.h"
#include "animal/dog.h"

namespace py = pybind11;

void init_bindings_animal(py::module_& m) {
    py::class_<Animal>(m, "Animal")
        .def("make_sound", &Animal::make_sound, "Make sound");
    py::class_<Cat, Animal>(m, "Cat")
        .def(py::init<>())
        .def("make_sound", &Cat::make_sound, "Make sound");
    py::class_<Dog, Animal>(m, "Dog")
        .def(py::init<>())
        .def("make_sound", &Dog::make_sound, "Make sound");
}