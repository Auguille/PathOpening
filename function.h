#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "PO.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

py::array pathOpening(std::vector<std::vector<int>> &image, int L, int K, int Direction);
py::array completePathOpening(std::vector<std::vector<int>> &image, int L, int K);

py::array pathClosing(std::vector<std::vector<int>> &image, int L, int K, int Direction);
py::array completePathClosing(std::vector<std::vector<int>> &image, int L, int K);

#endif