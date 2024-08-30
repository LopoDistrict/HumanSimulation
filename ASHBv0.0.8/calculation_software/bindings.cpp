// bindings.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "calculation.cpp"

namespace py = pybind11;

PYBIND11_MODULE(my_module, m) {
    m.def("add", &add, "A function which adds two numbers");
    m.def("greet", &greet, "A function which greets someone");
    m.def("get_numbers", &get_numbers, "A function which returns a list of numbers");
}