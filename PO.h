#ifndef __PO_H__
#define __PO_H__

#include "Image.h"

class PO
{
    public:
        PO(std::string inputFilename);
        ~PO();

        void computePO(int L, int neighborType);
        void writeResult(std::string filename);
        void reset();

    private:
        void printPath(std::vector<int> &lp, std::vector<int> &lm);
        void initOutput();
        void sortImage();
        void initValidArray(std::vector<bool> &valid);
        bool initInput(int L, 
                       int neighborType, 
                       std::vector<int> &lp, 
                       std::vector<int> &lm);
        void propagate(Pixel *p,
                       std::vector<int> &path,
                       std::vector<int> &nf, 
                       std::vector<int> &nb,
                       std::vector<Pixel*> &Qc);
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