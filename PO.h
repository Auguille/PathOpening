#ifndef __PO_H__
#define __PO_H__

#include "Image.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <queue>

namespace py = pybind11;

class PO
{
    public:
        PO(std::vector<std::vector<int>> &image);
        ~PO();

        py::array computePO(int L, int K, int neighborType);
        void reset();

    private:
        void printPath(std::vector<std::vector<int>> &lp, std::vector<std::vector<int>> &lm, int K);
        void printCount(std::vector<int> &count, std::vector<std::vector<bool>> &isChanged, int K);
        void initOutput();
        void sortImage();
        void initValidArray(std::vector<bool> &valid);
        bool initInput(int L, 
                       int neighborType, 
                       std::vector<std::vector<int>> &lp, 
                       std::vector<std::vector<int>> &lm,
                       int K);
        void propagate( std::queue<Pixel*> &queue, 
                        std::queue<Pixel*> &next, 
                        std::vector<std::vector<int>> &path, 
                        std::vector<int> &succ, 
                        std::vector<int> &pred, 
                        std::vector<std::vector<int>> &lm, 
                        std::vector<std::vector<int>> &lp, 
                        int L, 
                        int K, 
                        int threshold,
                        std::vector<int> &count,
                        std::vector<std::vector<bool>> &isChanged,
                        bool isDownward);
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