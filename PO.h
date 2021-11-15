#ifndef __PO_H__
#define __PO_H__

#include "Image.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>


namespace py = pybind11;

class PO
{
    public:
        PO(std::vector<std::vector<int>> &image);
        ~PO();

        py::array computePO(int L, int K, int neighborType);
        void reset();

    private:
        void printPath(std::vector<int> &lp, std::vector<int> &lm);
        void initOutput();
        void sortImage();
        void initValidArray(std::vector<bool> &valid);
        bool initInput(int L, 
                       int neighborType, 
                       std::vector<std::vector<int>> &lp, 
                       std::vector<std::vector<int>> &lm,
                       int K);
        void propagate(Pixel *p,
                       std::vector<std::vector<int>> &path,
                       std::vector<int> &nf, 
                       std::vector<int> &nb,
                       std::vector<Pixel*> &Qc,
                       int K);
        void createNeighborhood(int neighborType, 
                                std::vector<int> &np, 
                                std::vector<int> &nm);

    private:
        Image input;
        Image output;

        std::vector<Pixel*> sortedImage;

        std::vector<bool> b;
        std::vector<Pixel*> Qc;
};

#endif