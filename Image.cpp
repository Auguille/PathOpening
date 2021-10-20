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

void Image::resizeImage()
{
    this->image.resize(this->height);
    for(int i=0; i<this->height; ++i)
        this->image[i].resize(this->width);   
}

int Image::getPixelIntensity(int x, int y)
{
    return this->image[y][x].getValue();
}

int Image::getPixelUpwardPath(int x, int y)
{
    return this->image[y][x].getUpwardPath();
}

int Image::getPixelDownwardPath(int x, int y)
{
    return this->image[y][x].getDownwardPath();
}

bool Image::isPixelValid(int x, int y)
{
    return this->image[y][x].isValid();
}

bool Image::isPixelInQueue(int x, int y)
{
    return this->image[y][x].isInsideQueue();
}


Pixel* Image::getPixelAdress(int x, int y)
{
    return &this->image[y][x];
}

void Image::setPixelIntensity(int x, int y, int value)
{
    this->image[y][x].setValue(value);
}

void Image::setPixelUpwardPath(int x, int y, int value)
{
    this->image[y][x].setUpwardPath(value);
}

void Image::setPixelDownwardPath(int x, int y, int value)
{
    this->image[y][x].setDownwardPath(value);
}

void Image::setPixelValid(int x, int y, bool isValid)
{
    this->image[y][x].setValid(isValid);
}

void Image::setPixelInQueue(int x, int y, bool isInQueue)
{
    this->image[y][x].setInsideQueue(isInQueue);
}

void Image::readImage(std::string filename)
{
    std::fstream fs(filename, std::fstream::in);

    std::string magicNumber;
    std::getline(fs, magicNumber);
    if(magicNumber.compare("P2") != 0) 
        std::cerr << "Version error" << std::endl;

    fs >> this->width >> this->height >> this->grayLevel;

    this->image.resize(this->height);
    for(int i=0; i<this->height; ++i)
        this->image[i].resize(this->width);

    for(int i=0; i<this->height; ++i)
    {
        for(int j=0; j<this->width; ++j)
        {
            int value;
            fs >> value;
            this->image[i][j].setValue(value);
            this->image[i][j].setValid(true);
            // if(1+i > L-1)
            //     this->image[i][j].setUpwardPath(L-1);
            // else
            this->image[i][j].setUpwardPath(i+1);
            // if(this->height-i > L-1)
            //     this->image[i][j].setDownwardPath(L-1);
            // else
            this->image[i][j].setDownwardPath(this->height-i);
            this->image[i][j].setInsideQueue(false);
            this->image[i][j].setPositionX(j);
            this->image[i][j].setPositionY(i);
        }
    }

    fs.close();
}

void Image::writeImage(std::string filename)
{
    std::fstream fs(filename, std::fstream::out);

    fs << "P2\n" << this->width << " " << this->height << "\n" << this->grayLevel << "\n";

    for(int i=0; i<this->height; ++i)
    {
        for(int j=0; j<this->width; ++j)
            fs << this->image[i][j].getValue() << " ";
        fs << "\n";
    }
            
}