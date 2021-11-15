cmake_minimum_required(VERSION 3.4)
project(PathOpening LANGUAGES CXX)

# add_executable(PathOpening Pixel.h Pixel.cpp Image.h Image.cpp PO.h PO.cpp main.cpp)

add_subdirectory(extern/pybind11)
pybind11_add_module(PathOpening Pixel.h Pixel.cpp Image.h Image.cpp PO.h PO.cpp)