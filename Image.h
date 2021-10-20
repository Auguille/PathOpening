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

        void resizeImage();

        Pixel* getPixelAdress(int x, int y);

        int getPixelIntensity(int x, int y);
        int getPixelUpwardPath(int x, int y);
        int getPixelDownwardPath(int x, int y);
        bool isPixelValid(int x, int y);
        bool isPixelInQueue(int x, int y);

        void setPixelIntensity(int x, int y, int value);
        void setPixelUpwardPath(int x, int y, int value);
        void setPixelDownwardPath(int x, int y, int value);
        void setPixelValid(int x, int y, bool isValid);
        void setPixelInQueue(int x, int y, bool isInQueue);

        void readImage(std::string filename);
        void writeImage(std::string filename);


    private:
        int height;
        int width;
        int grayLevel;

        std::vector<std::vector<Pixel>> image;
};

#endif