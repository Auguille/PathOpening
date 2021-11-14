#include "Image.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Image::Image()
{
}

Image::~Image()
{
}

int Image::getHeight()
{
    return this->height;
}

int Image::getWidth()
{
    return this->width;
}

int Image::getGrayLevel()
{
    return this->grayLevel;
}

void Image::setHeight(int height)
{
    this->height = height;
}

void Image::setWidth(int width)
{
    this->width = width;
}

void Image::setGrayLevel(int grayLevel)
{
    this->grayLevel = grayLevel;
}

int Image::getPixelIntensity(int i)
{
    return this->image[i].getValue();
}

int Image::getPositionX(int i)
{
    return this->image[i].getPositionX();
}

int Image::getPositionY(int i)
{
    return this->image[i].getPositionY();
}

bool Image::isPixelValid(int i)
{
    return this->image[i].isValid();
}

bool Image::isPixelInQueue(int i)
{
    return this->image[i].isInsideQueue();
}

bool Image::isPixelBorder(int i)
{
    return this->image[i].isBorder();
}

Pixel* Image::getPixelAdress(int i)
{
    return &this->image[i];
}

void Image::setPixelIntensity(int i, int value)
{
    this->image[i].setValue(value);
}

void Image::setPixelValid(int i, bool isValid)
{
    this->image[i].setValid(isValid);
}

void Image::setPixelInQueue(int i, bool isInQueue)
{
    this->image[i].setInsideQueue(isInQueue);
}

void Image::setPixelBorder(int i, bool isBorder)
{
    this->image[i].setBorder(isBorder);
}

void Image::initImage(std::vector<std::vector<int>> &img)
{
    this->height = img.size()+2;
    this->width = img[0].size()+2;

    this->image.resize(this->height*this->width);

    for(int i=0, a=0, b=0; i<this->height*this->width; ++i)
    {
        int x = i%width;
        int y = i/width;
        if(x == 0 || y == 0 || x == this->width-1 || y == this->height-1)
        {
            this->image[i].setValue(0);
            this->image[i].setValid(false);
            this->image[i].setBorder(true);
        }
        else
        {
            this->image[i].setValue(img[a][b]);
            this->image[i].setValid(true);
            this->image[i].setBorder(false);
            b++;

            if(b == this->width-2)
            {
                b=0;
                a++;
            }
        }
        this->image[i].setInsideQueue(false);
        this->image[i].setPosition(i);
        this->image[i].setPositionX(x);
        this->image[i].setPositionY(y);
    }
}

std::vector<std::vector<int>> Image::returnImage()
{
    std::vector<std::vector<int>> imageRet;

    imageRet.resize(this->height-2);
    for(int i=0; i<imageRet.size(); ++i)
        imageRet[i].resize(this->width-2);

    for(int i=0, a=0, b=0; i<this->height*this->width; ++i)
    {
        int x = image[i].getPositionX();
        int y = image[i].getPositionY();

        if(x != 0 && y != 0 && x != this->width-1 && y != this->height-1)
        {
            imageRet[a][b] = image[i].getValue();
            b++;
            if(b == this->width-2)
            {
                b=0;
                a++;
            }
        }
    }

    return imageRet;
}