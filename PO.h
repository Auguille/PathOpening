#ifndef __OP_H__
#define __OP_H__

#include "Image.h"

class PO
{
    public:
        PO(std::string inputFilename, int L);
        ~PO();

        void compute();
        void writeResult(std::string filename);

    private:
        void computeVPO();
        void computeHPO();
        void computeSENWPO();
        void sortImage();
        void initVPaths();
        void initHPaths();
        void computeVUpward(std::vector<std::vector<Pixel*>> &upwardPath);
        void computeHUpward(std::vector<std::vector<Pixel*>> &upwardPath);
        void computeVDownward(std::vector<std::vector<Pixel*>> &downwardPath);
        void computeHDownward(std::vector<std::vector<Pixel*>> &downwardPath);

        void applyThreshold(int threshold);

        void initOutputImage();

        // Debug
        void printPath();


    private:
        Image input;
        Image output;
        int L;

        std::vector<Pixel*> activePixel;
        std::vector<Pixel*> sortedImage;
        std::vector<int> threshold;

};

#endif