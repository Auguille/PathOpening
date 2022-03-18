# PathOpening

C++ implementation of morphological paths operators (opening and closing), which are non-linear filters useful in image analysis and image processing, usable in python 

This repository is based on Hugues Talbot works : https://link.springer.com/chapter/10.1007/1-4020-3443-1_4


## Installation

```sh
git clone git@git.unistra.fr:hiernard/pathopening.git
git submodule update --init
```

```sh
mkdir build
cd build
cmake ../
make -j4
pip install ../
```

Le makefile va générer un fichier PathOpening.so représentant le module python de l'ouverture par chemin. <br>
La commande pip install ../ permet d'installer la librairie à partir du fichier setup.py dans l'environnement python pour pouvoir l'utiliser simplement à l'aide de l'import 

```py
import PathOpening
```

## Usage

The library allows the use of four functions:
```py
pathOpening(Image, PathLength, GapNumber, Direction)
completePathOpening(Image, PathLength, GapNumber)
pathClosing(Image, PathLength, GapNumber, Direction)
completePathClosing(Image, PathLength, GapNumber)
```
Image represents the image to be processed<br>
PathLength represents the minimum length of a path<br>
GapNumber represents the maximum gap in a path<br>
Direction represents the adjacency graph used (1 = N-S, 2=NE-SW, 3=E-W, 4=SE-NW)

completePathOpening and completePathClosing functions return the new image calculated using the opening (respectively closing) path operator in the four directions

**Example**

```py
# File test.py
import PathOpening as po  
import cv2

img = cv2.imread("Images/DNAGI.tif", cv2.IMREAD_GRAYSCALE)

result = po.completePathOpening(img, 70, 3)

cv2.imwrite("Results/DNAGI-out-70-3.tif", result)
```
