#include "PO.h"

#include "algorithm"
#include <iostream>

PO::PO(std::string inputFilename, int L):
    L(L)
{
    input.readImage(inputFilename);
    initOutputImage();

    sortedImage.resize(input.getHeight()*input.getWidth());
}

PO::~PO()
{
}

void PO::initVPaths()
{
    for(int i=0; i<input.getHeight(); ++i)
    {
        for(int j=0; j<input.getWidth(); ++j)
        {
            if(1+i > L)
                input.setPixelUpwardPath(j,i,L);
            else
                input.setPixelUpwardPath(j,i,i+1);

            if(input.getHeight()-i > L)
                input.setPixelDownwardPath(j,i,L);
            else
                input.setPixelDownwardPath(j,i,input.getHeight()-i);
        }
    }
}

void PO::initHPaths()
{
    for(int i=0; i<input.getHeight(); ++i)
    {
        for(int j=0; j<input.getWidth(); ++j)
        {
            if(input.getWidth()-j > L)
                input.setPixelUpwardPath(j,i,L);
            else
                input.setPixelUpwardPath(j,i,input.getWidth()-j);

            if(j+1 > L)
                input.setPixelDownwardPath(j,i,L);
            else
                input.setPixelDownwardPath(j,i,j+1);
        }
    }
}

void PO::computeVUpward(std::vector<std::vector<Pixel*>> &upwardPath)
{
    for(int i=0; i<upwardPath.size(); ++i)
    {
        for(int j=0; j<upwardPath[i].size(); ++j)
        {
            int x = upwardPath[i][j]->getPositionX();
            int y = upwardPath[i][j]->getPositionY();

            bool hasChanged = false;
            int newValue = 0;
            if(input.isPixelValid(x,y))
            {
                if(x == 0)
                    newValue = 1+std::max(input.getPixelUpwardPath(x,y-1), input.getPixelUpwardPath(x+1,y-1));
                else if(x == input.getWidth()-1)
                    newValue = 1+std::max(input.getPixelUpwardPath(x-1,y-1), input.getPixelUpwardPath(x,y-1));
                else
                    newValue = 1+std::max(input.getPixelUpwardPath(x-1,y-1), std::max(input.getPixelUpwardPath(x,y-1), input.getPixelUpwardPath(x+1,y-1)));
                int olderUpwardPath = input.getPixelUpwardPath(x,y);

                if(olderUpwardPath > newValue)
                    hasChanged=true;
            }

            if(!input.isPixelValid(x,y) || hasChanged)
            {
                input.setPixelUpwardPath(x,y,newValue);

                // Si le point a des successeurs on les ajoute
                if(i < upwardPath.size()-1)
                {
                    if(x > 0 && input.isPixelValid(x-1,y+1))
                        upwardPath[i+1].push_back(input.getPixelAdress(x-1, y+1));

                    if(x < input.getWidth()-1 && input.isPixelValid(x+1,y+1))
                        upwardPath[i+1].push_back(input.getPixelAdress(x+1, y+1));

                    if(input.isPixelValid(x,y+1))
                        upwardPath[i+1].push_back(input.getPixelAdress(x, y+1));
                }

                // Si le point n'est pas encore dans la file on l'ajoute
                if(!input.isPixelInQueue(x,y))
                {
                    activePixel.push_back(input.getPixelAdress(x,y));
                    input.setPixelInQueue(x,y,true);
                }
            }
        }
        upwardPath[i].clear();
    }
}

void PO::computeHUpward(std::vector<std::vector<Pixel*>> &upwardPath)
{
    for(int i=upwardPath.size()-1; i>=0; --i)
    {
        for(int j=0; j<upwardPath[i].size(); ++j)
        {
            int x = upwardPath[i][j]->getPositionX();
            int y = upwardPath[i][j]->getPositionY();

            bool hasChanged = false;
            int newValue = 0;
            if(input.isPixelValid(x,y))
            {
                if(y == 0)
                    newValue = 1+std::max(input.getPixelUpwardPath(x+1,y), input.getPixelUpwardPath(x+1,y+1));
                else if(y == input.getHeight()-1)
                    newValue = 1+std::max(input.getPixelUpwardPath(x+1,y-1), input.getPixelUpwardPath(x+1,y));
                else
                    newValue = 1+std::max(input.getPixelUpwardPath(x+1,y-1), std::max(input.getPixelUpwardPath(x+1,y), input.getPixelUpwardPath(x+1,y+1)));
                int olderUpwardPath = input.getPixelUpwardPath(x,y);

                if(olderUpwardPath > newValue)
                    hasChanged=true;
            }

            if(!input.isPixelValid(x,y) || hasChanged)
            {
                input.setPixelUpwardPath(x,y,newValue);

                // Si le point a des successeurs on les ajoute
                if(i > 0)
                {
                    if(y > 0 && input.isPixelValid(x-1,y-1))
                        upwardPath[i-1].push_back(input.getPixelAdress(x-1, y-1));

                    if(y < input.getHeight()-1 && input.isPixelValid(x-1,y+1))
                        upwardPath[i-1].push_back(input.getPixelAdress(x-1, y+1));

                    if(input.isPixelValid(x-1,y))
                        upwardPath[i-1].push_back(input.getPixelAdress(x-1, y));
                }

                // Si le point n'est pas encore dans la file on l'ajoute
                if(!input.isPixelInQueue(x,y))
                {
                    activePixel.push_back(input.getPixelAdress(x,y));
                    input.setPixelInQueue(x,y,true);
                }
            }
        }
        upwardPath[i].clear();
    }
}

void PO::computeVDownward(std::vector<std::vector<Pixel*>> &downwardPath)
{
    for(int i=downwardPath.size()-1; i>=0; --i)
    {
        for(int j=0; j<downwardPath[i].size(); ++j)
        {
            int x = downwardPath[i][j]->getPositionX();
            int y = downwardPath[i][j]->getPositionY();

            bool hasChanged = false;
            int newValue = 0;
            if(input.isPixelValid(x,y))
            {
                if(x == 0)
                    newValue = 1+std::max(input.getPixelDownwardPath(x,y+1), input.getPixelDownwardPath(x+1,y+1));
                else if(x == input.getWidth()-1)
                    newValue = 1+std::max(input.getPixelDownwardPath(x-1,y+1), input.getPixelDownwardPath(x,y+1));
                else
                    newValue = 1+std::max(input.getPixelDownwardPath(x-1,y+1), std::max(input.getPixelDownwardPath(x,y+1), input.getPixelDownwardPath(x+1,y+1)));
                int olderDownwardPath = input.getPixelDownwardPath(x,y);

                if(olderDownwardPath > newValue)
                    hasChanged=true;
            }

            if(!input.isPixelValid(x,y) || hasChanged)
            {
                input.setPixelDownwardPath(x,y,newValue);

                // Si le point a des successeurs on les ajoute
                if(i > 0)
                {
                    if(x > 0 && input.isPixelValid(x-1,y-1))
                        downwardPath[i-1].push_back(input.getPixelAdress(x-1, y-1));

                    if(x < input.getWidth()-1 && input.isPixelValid(x+1,y-1))
                        downwardPath[i-1].push_back(input.getPixelAdress(x+1, y-1));

                    if(input.isPixelValid(x,y-1))
                        downwardPath[i-1].push_back(input.getPixelAdress(x, y-1));
                }

                // Si le point n'est pas encore dans la file on l'ajoute
                if(!input.isPixelInQueue(x,y))
                {
                    activePixel.push_back(input.getPixelAdress(x,y));
                    input.setPixelInQueue(x,y,true);
                }
            }
        }
        downwardPath[i].clear();
    }
}

void PO::computeHDownward(std::vector<std::vector<Pixel*>> &downwardPath)
{
    for(int i=0; i<downwardPath.size(); ++i)
    {
        for(int j=0; j<downwardPath[i].size(); ++j)
        {
            int x = downwardPath[i][j]->getPositionX();
            int y = downwardPath[i][j]->getPositionY();

            bool hasChanged = false;
            int newValue = 0;
            if(input.isPixelValid(x,y))
            {
                if(y == 0)
                    newValue = 1+std::max(input.getPixelDownwardPath(x-1,y), input.getPixelDownwardPath(x-1,y+1));
                else if(y == input.getHeight()-1)
                    newValue = 1+std::max(input.getPixelDownwardPath(x-1,y-1), input.getPixelDownwardPath(x-1,y));
                else
                    newValue = 1+std::max(input.getPixelDownwardPath(x-1,y-1), std::max(input.getPixelDownwardPath(x-1,y), input.getPixelDownwardPath(x-1,y+1)));
                int olderDownwardPath = input.getPixelDownwardPath(x,y);

                if(olderDownwardPath > newValue)
                    hasChanged=true;
            }

            if(!input.isPixelValid(x,y) || hasChanged)
            {
                input.setPixelDownwardPath(x,y,newValue);

                // Si le point a des successeurs on les ajoute
                if(i < downwardPath.size()-1)
                {
                    if(y > 0 && input.isPixelValid(x+1,y-1))
                        downwardPath[i+1].push_back(input.getPixelAdress(x+1, y-1));

                    if(y < input.getHeight()-1 && input.isPixelValid(x+1,y+1))
                        downwardPath[i+1].push_back(input.getPixelAdress(x+1, y+1));

                    if(input.isPixelValid(x+1,y))
                        downwardPath[i+1].push_back(input.getPixelAdress(x+1, y));
                }

                // Si le point n'est pas encore dans la file on l'ajoute
                if(!input.isPixelInQueue(x,y))
                {
                    activePixel.push_back(input.getPixelAdress(x,y));
                    input.setPixelInQueue(x,y,true);
                }
            }
        }
        downwardPath[i].clear();
    }
}

void PO::applyThreshold(int threshold)
{
    for(int i=0; i<activePixel.size(); ++i)
    {
        int x = activePixel[i]->getPositionX();
        int y = activePixel[i]->getPositionY();
        int pathLength = input.getPixelUpwardPath(x,y) + input.getPixelDownwardPath(x,y) - 1;
        if(pathLength < L)
        {
            if(output.getPixelIntensity(x,y) == -1 || output.getPixelIntensity(x,y) < threshold)
                output.setPixelIntensity(x, y, threshold);

            input.setPixelDownwardPath(x,y,0);
            input.setPixelUpwardPath(x,y,0);
            input.setPixelValid(x,y,false);
        }
        input.setPixelInQueue(x,y,false);
    }
    activePixel.clear();
}

void PO::computeVPO()
{
    initVPaths();

    int index = 0;
    std::vector<std::vector<Pixel*>> upwardPath;
    std::vector<std::vector<Pixel*>> downwardPath;
    upwardPath.resize(input.getHeight());
    downwardPath.resize(input.getHeight());

    for(int it=0; it<threshold.size(); it++)
    {
        int t = threshold[it];

        while(index < sortedImage.size() && sortedImage[index]->getValue() == t)
        {
            int x = sortedImage[index]->getPositionX();
            int y = sortedImage[index]->getPositionY();
            if(input.isPixelValid(x,y))
            {
                upwardPath[y].push_back(sortedImage[index]);
                downwardPath[y].push_back(sortedImage[index]);
                input.setPixelValid(x,y,false);
            }
            index++;
        }

        // Compute lamda- and lambda+
        computeVUpward(upwardPath);
        computeVDownward(downwardPath);

        applyThreshold(t);

    }
}

void PO::computeHPO()
{
    initHPaths();
    std::vector<std::vector<Pixel*>> upwardPath;
    std::vector<std::vector<Pixel*>> downwardPath;
    upwardPath.resize(input.getWidth());
    downwardPath.resize(input.getWidth());

    int index = 0;
    for(int it=0; it<threshold.size(); it++)
    {
        int t = threshold[it];

        while(index < sortedImage.size() && sortedImage[index]->getValue() == t)
        {
            int x = sortedImage[index]->getPositionX();
            int y = sortedImage[index]->getPositionY();
            if(input.isPixelValid(x,y))
            {
                upwardPath[x].push_back(sortedImage[index]);
                downwardPath[x].push_back(sortedImage[index]);
                input.setPixelValid(x,y,false);
            }
            index++;
        }

        // Compute lamda- and lambda+
        computeHUpward(upwardPath);
        computeHDownward(downwardPath);

        applyThreshold(t);
    }
}

void PO::sortImage()
{
    for(int i=0; i<input.getHeight(); ++i)
    {
        for(int j=0; j<input.getWidth(); ++j)
        {
            sortedImage[i*input.getWidth()+j] = input.getPixelAdress(j,i);
        }
    }

    std::sort(sortedImage.begin(), sortedImage.end(), [](Pixel *p1, Pixel *p2)
    {
        return p1->getValue() < p2->getValue();
    });

    threshold.resize(sortedImage.size());
    for(int i=0; i<sortedImage.size(); ++i)
        threshold[i] = sortedImage[i]->getValue();

    auto last = std::unique(threshold.begin(), threshold.end());
    threshold.erase(last, threshold.end());
}


void PO::compute()
{
    sortImage();
    
    computeVPO();

    for(int i=0; i<input.getHeight(); ++i)
    {
        for(int j=0; j<input.getWidth(); ++j)
        {
            input.setPixelValid(j,i,true);
        }
    }

    computeHPO();

}

void PO::printPath()
{
    std::cout << "Lambda-\n";
    for(int i=0; i<input.getHeight(); ++i)
    {
        for(int j=0; j<input.getWidth(); ++j)
        {
            std::cout << input.getPixelUpwardPath(j,i) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Lambda+\n";
    for(int i=0; i<input.getHeight(); ++i)
    {
        for(int j=0; j<input.getWidth(); ++j)
        {
            std::cout << input.getPixelDownwardPath(j,i) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PO::writeResult(std::string filename)
{
    output.writeImage(filename);
}

void PO::initOutputImage()
{
    output.setHeight(input.getHeight());
    output.setWidth(input.getWidth());
    output.setGrayLevel(input.getGrayLevel());
    output.resizeImage();

    for(int i=0; i<output.getHeight(); ++i)
    {
        for(int j=0; j<output.getWidth(); ++j)
        {
            output.setPixelIntensity(j,i,-1);
        }
    }
}