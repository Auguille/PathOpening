cmake_minimum_required(VERSION 3.12)
project(PathOpening LANGUAGES CXX)

# add_executable(PathOpening Pixel.h Pixel.cpp Image.h Image.cpp PO.h PO.cpp main.cpp)

find_package(PythonLibs 3.8 EXACT REQUIRED)

add_subdirectory(extern/pybind11)
pybind11_add_module(PathOpening Pixel.h Pixel.cpp Image.h Image.cpp PO.h PO.cpp function.h function.cpp)

set_target_properties(PathOpening PROPERTIES OUTPUT_NAME "PathOpening")
set_target_properties(PathOpening PROPERTIES SUFFIX ".so")