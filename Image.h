#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <vector>
#include "Pixel.h"

class Image
{
    public:
        Image();
        virtual ~Image();

        // Getter Setter
        int getHeight();
        int getWidth();
        int getGrayLevel();

        void setHeight(int height);
        void setWidth(int width);
        void setGrayLevel(int grayLevel);

        Pixel* getPixelAdress(int i);

        int getPixelIntensity(int i);
        int getPositionX(int i);
        int getPositionY(int i);
        bool isPixelValid(int i);
        bool isPixelInQueue(int i);

        void setPixelIntensity(int i, int value);
        void setPixelValid(int i, bool isValid);
        void setPixelInQueue(int i, bool isInQueue);

        void readImage(std::string filename);
        void writeImage(std::string filename);
        void invert();


    private:
        int height;
        int width;
        int grayLevel;

        std::vector<Pixel> image;
};

#endif