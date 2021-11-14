#include "PO.h"

#include <algorithm>
#include <queue>
#include <iostream>

PO::PO(std::vector<std::vector<int>> &image)
{
    input.initImage(image);
    initOutput();
    sortImage();
}

PO::~PO()
{
}

void PO::createNeighborhood(int neighborType, 
                             std::vector<int> &np, 
                             std::vector<int> &nm)
{
    // S-N
    if(neighborType == 1)
    {
        np.push_back(-input.getWidth()-1);
        np.push_back(-input.getWidth());
        np.push_back(-input.getWidth()+1);

        nm.push_back(input.getWidth()-1);
        nm.push_back(input.getWidth());
        nm.push_back(input.getWidth()+1);
    }

    //SW-NE
    else if(neighborType == 2)
    {
        np.push_back(-input.getWidth());
        np.push_back(1);
        np.push_back(-input.getWidth()+1);

        nm.push_back(input.getWidth());
        nm.push_back(-1);
        nm.push_back(input.getWidth()-1);
    }

    // W-E
    else if(neighborType == 3)
    {
        np.push_back(-input.getWidth()+1);
        np.push_back(1);
        np.push_back(input.getWidth()+1);
        
        nm.push_back(-input.getWidth()-1);
        nm.push_back(-1);
        nm.push_back(input.getWidth()-1);
    }

    // NW-SE
    else if(neighborType == 4)
    {
        np.push_back(-1);
        np.push_back(-input.getWidth());
        np.push_back(-input.getWidth()-1);
        
        nm.push_back(1);
        nm.push_back(input.getWidth());
        nm.push_back(input.getWidth()+1);
    }
}

bool PO::initInput(int L, int neighborType, std::vector<std::vector<int>> &lp, std::vector<std::vector<int>> &lm, int K)
{
    bool pathLongEnough = false;
    lp.resize(K+1);
    lm.resize(K+1);
    for(int i=0; i<input.getHeight()*input.getWidth(); ++i)
    {
        int x = input.getPositionX(i);
        int y = input.getPositionY(i);
        for(int k=0; k<=K; ++k)
        {
            if(x == 0 || y == 0 || x == input.getWidth()-1 || y == input.getHeight()-1)
            {
                lm[k].push_back(0);
                lp[k].push_back(0);
            }
            else
            {
                switch (neighborType)
                {
                case 1:
                    if(y >= L)
                    {
                        lm[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lm[k].push_back(y);
                    
                    if(input.getHeight()-1-y >= L)
                    {
                        lp[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lp[k].push_back(input.getHeight()-1-y);
                    break;

                case 2:
                    if((input.getWidth()-2)-(x-1)+(y-1) >= L)
                    {
                        lm[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lm[k].push_back((input.getWidth()-2)-(x-1)+(y-1));

                    if((input.getWidth()-2)+(x-1)-(y-1) >= L)
                    {
                        lp[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lp[k].push_back((input.getWidth()-2)+(x-1)-(y-1));
                    break;
                
                case 3:
                    if(x >= L)
                    {
                        lp[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lp[k].push_back(x);
                    
                    if(input.getWidth()-1-x >= L)
                    {
                        lm[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lm[k].push_back(input.getWidth()-1-x);
                    break;

                case 4:
                    if(input.getWidth()-2+input.getHeight()-2-1-(x-1)-(y-1) >= L)
                    {
                        lp[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lp[k].push_back((input.getWidth()-2)+(input.getHeight()-2)-1-(x-1)-(y-1));   

                    if((x-1)+(y-1)+1 >= L)
                    {
                        lm[k].push_back(L);
                        pathLongEnough = true;
                    }
                    else
                        lm[k].push_back((x-1)+(y-1)+1);
                    break;

                default:
                    break;
                }
            }
        }
    }

    return pathLongEnough;
}

py::array PO::computePO(int L, int K, int neighborType)
{
    std::vector<int> np, nm;
    createNeighborhood(neighborType, np, nm);

    std::vector<std::vector<int>> lp, lm;
    if(initInput(L, neighborType, lp, lm, K))
    {
        std::vector<Pixel*> Qc;
        for(int i=0; i<sortedImage.size(); ++i)
        {
            int pos = sortedImage[i]->getPosition();
            if(input.isPixelValid(pos))
            {
                propagate(sortedImage[i], lm, np, nm, Qc, K);
                propagate(sortedImage[i], lp, nm, np, Qc, K);

                for(int i=0; i<Qc.size(); ++i)
                {
                    int p = Qc[i]->getPosition();
                    if(input.isPixelValid(p) || p == pos)
                    {
                        int length = 0;
                        for(int k=0; k<=K; ++k)
                            if(K-k-!input.isPixelValid(p) >= 0)
                                length = std::max(lm[k][p]+lp[K-k-!input.isPixelValid(p)][p], length);

                        if(length-1 < L)
                        {
                            if(input.getPixelIntensity(pos) > output.getPixelIntensity(p))
                                output.setPixelIntensity(p, input.getPixelIntensity(pos));
                            input.setPixelValid(p,false);
                        }
                    }
                    input.setPixelInQueue(p, false);
                }
                Qc.clear();
            }
        }
    }

    return py::cast(output.returnImage());
}

// Active = Qc
// Enqueue = Qq 
void PO::propagate(Pixel *p, 
                    std::vector<std::vector<int>> &path,
                    std::vector<int> &pred, 
                    std::vector<int> &succ,
                    std::vector<Pixel*> &Qc,
                    int K)
{
    static int cpt = 0;

    int pos = p->getPosition();
    if(!input.isPixelInQueue(pos))
    {
        Qc.push_back(p);
        input.setPixelInQueue(pos, true);
    }
    
    p->setValid(false);

    std::queue<Pixel*> Qq;
    Qq.push(p);

    while(!Qq.empty())
    {
        int position = Qq.front()->getPosition();
        Qq.pop();

        for(int k=0; k<=K; ++k)
        {
            int length = -1;
            if(input.isPixelValid(position))
            {
                for(int i=0; i<pred.size(); ++i)
                    if(!input.isPixelBorder(position+pred[i]))
                        length = std::max(path[k][position+pred[i]], length);
            }

            else if(k>0)
            {
                for(int i=0; i<pred.size(); ++i)
                    if(!input.isPixelBorder(position+pred[i]))
                        length = std::max(path[k-1][position+pred[i]], length);
            }

            if(length+1 < path[k][position])
            {
                path[k][position] = length+1;
                for(int i=0; i<succ.size(); ++i)
                    if(!input.isPixelBorder(position+succ[i]))
                        Qq.push(input.getPixelAdress(position+succ[i]));

                if(!input.isPixelInQueue(position))
                {
                    Qc.push_back(input.getPixelAdress(position));
                    input.setPixelInQueue(position, true);
                }
            }
        }
    }

    cpt++;
}

void PO::sortImage()
{
    for(int i=0; i<input.getWidth()*input.getHeight(); ++i)
    {
        if(input.isPixelValid(i))
            sortedImage.push_back(input.getPixelAdress(i));
    }

    std::stable_sort(sortedImage.begin(), sortedImage.end(), [](Pixel *p1, Pixel *p2)
    {
        return p1->getValue() < p2->getValue();
    });
}

void PO::reset()
{
    for(int i=0; i<input.getHeight()*input.getWidth(); ++i)
    {
        int x = input.getPositionX(i);
        int y = input.getPositionY(i);
        if(x == 0 || y == 0 || x == input.getWidth()-1 || y == input.getHeight()-1)
            input.setPixelValid(i,false);
        else
            input.setPixelValid(i,true);
    }
}

void PO::initOutput()
{
    output = input;
    for(int i=0; i<input.getHeight()*input.getWidth(); ++i)
        output.setPixelIntensity(i, 0);
}


PYBIND11_MODULE(PathOpening, m)
{
    py::class_<PO>(m, "PO")
        .def(py::init<std::vector<std::vector<int>> &>())
        .def("reset", &PO::reset)
        .def("computePO", &PO::computePO);
}