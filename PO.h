#ifndef __PO_H__
#define __PO_H__

#include "Image.h"
#include <queue>

class PO
{
    public:
        PO(std::vector<std::vector<int>> &image, bool opening);
        ~PO();

        std::vector<std::vector<int>> computePO(int L, int K, int neighborType, bool opening);
        void reset();

    private:
        void printPath(std::vector<std::vector<int>> &lp, std::vector<std::vector<int>> &lm, int K);
        void printCount(std::vector<int> &count, std::vector<std::vector<bool>> &isChanged, int K);
        void initOutput(bool opening);
        void sortImage(bool opening);
        void initValidArray(std::vector<bool> &valid);
        bool initInput(int L, 
                       int neighborType, 
                       std::vector<std::vector<int>> &lp, 
                       std::vector<std::vector<int>> &lm,
                       int K);
        void propagate( std::queue<Pixel*> &queue, 
                        std::queue<Pixel*> &next1,
                        std::queue<Pixel*> &next2, 
                        std::vector<std::vector<int>> &path, 
                        std::vector<int> &succ, 
                        std::vector<int> &pred, 
                        std::vector<std::vector<int>> &lm, 
                        std::vector<std::vector<int>> &lp, 
                        int K, 
                        std::queue<int> &active);
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