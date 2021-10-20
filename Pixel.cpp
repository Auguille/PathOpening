#include "Pixel.h"

Pixel::Pixel()
{
}

Pixel::~Pixel()
{
}

int Pixel::getValue()
{
    return this->value;
}

int Pixel::getUpwardPath()
{
    return this->upwardPath;
}

int Pixel::getDownwardPath()
{
    return this->downwardPath;
}

int Pixel::getPositionX()
{
    return this->positionX;
}

int Pixel::getPositionY()
{
    return this->positionY;
}

bool Pixel::isValid()
{
    return this->valid;
}

bool Pixel::isInsideQueue()
{
    return this->insideQueue;
}

void Pixel::setValue(int value)
{
    this->value = value;
}

void Pixel::setUpwardPath(int upwardPath)
{
    this->upwardPath = upwardPath;
}

void Pixel::setDownwardPath(int downwardPath)
{
    this->downwardPath = downwardPath;
}

void Pixel::setPositionX(int position)
{
    this->positionX = position;
}

void Pixel::setPositionY(int position)
{
    this->positionY = position;
}

void Pixel::setValid(bool isValid)
{
    this->valid = isValid;
}

void Pixel::setInsideQueue(bool isInside)
{
    this->insideQueue = isInside;
}