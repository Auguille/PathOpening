#ifndef __PIXEL_H__
#define __PIXEL_H__

class Pixel
{
    public:
        Pixel();
        virtual ~Pixel();

        int getValue();
        int getUpwardPath();
        int getDownwardPath();
        int getPositionX();
        int getPositionY();
        bool isValid();
        bool isInsideQueue();

        void setValue(int value);
        void setUpwardPath(int upwardPath);
        void setDownwardPath(int downwardPath);
        void setPositionX(int positionX);
        void setPositionY(int positionY);
        void setValid(bool isValid);
        void setInsideQueue(bool isInside);

    private:
        int value;                      // intensité du pixel
        int upwardPath;                 // valeur du chemin lambda-
        int downwardPath;               // valeur du chemin lambda+
        bool valid;                     // Le pixel respecte encore le seuil ?

        bool insideQueue;               // Le pixel est présent dans la pile

        int positionX;                  // Position x du pixel dans le tableau
        int positionY;                  // Position y du pixel dans le tableau
};

#endif