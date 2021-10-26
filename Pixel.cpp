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

int Pixel::getPosition()
{
    return this->position;
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

void Pixel::setPosition(int position)
{
    this->position = position;
}

void Pixel::setPositionX(int positionX)
{
    this->positionX = positionX;
}

void Pixel::setPositionY(int positionY)
{
    this->positionY = positionY;
}

void Pixel::setValid(bool isValid)
{
    this->valid = isValid;
}

void Pixel::setInsideQueue(bool isInside)
{
    this->insideQueue = isInside;
}