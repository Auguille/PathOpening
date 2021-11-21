#include "function.h"

py::array pathOpening(std::vector<std::vector<int>> &image, int L, int K, int Direction)
{
    PO poModule(image, true);

    return py::cast(poModule.computePO(L, K, Direction, true));
}

py::array completePathOpening(std::vector<std::vector<int>> &image, int L, int K)
{
    PO poModule(image, true);

    std::vector<std::vector<int>> output;
    for(int i=1; i<5; ++i)
        output = poModule.computePO(L, K, i, true);

    return py::cast(output);
}

py::array pathClosing(std::vector<std::vector<int>> &image, int L, int K, int Direction)
{
    PO poModule(image, false);

    return py::cast(poModule.computePO(L, K, Direction, false));
}

py::array completePathClosing(std::vector<std::vector<int>> &image, int L, int K)
{
    PO poModule(image, false);

    std::vector<std::vector<int>> output;
    for(int i=1; i<5; ++i)
        output = poModule.computePO(L, K, i, false);

    return py::cast(output);
}

PYBIND11_MODULE(PathOpening, m)
{
    m.def("pathOpening", &pathOpening, "Compute path opening in one direction");
    m.def("completePathOpening", &completePathOpening, "Compute complete path opening");
    m.def("pathClosing", &pathClosing, "Compute path closing in one direction");
    m.def("completePathClosing", &completePathClosing, "Compute complete path closing");
}