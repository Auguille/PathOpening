# PathOpening

Implémentation en C++ de l'algorithme d'ouverture par chemin utilisable en python

## Installation

```sh
git clone git@git.unistra.fr:hiernard/pathopening.git
git submodule update --init
```

On utilisera CMake afin de compiler le code de manière simple et efficace

```sh
mkdir build
cd build
cmake ../
make -j4
```

Le makefile va générer un fichier .so représentant le module python de l'ouverture par chemin

## Usage

La libraire permet l'utilisation de quatres fonctions :
```py
pathOpening(Image, PathLength, GapNumber, Direction)
completePathOpening(Image, PathLength, GapNumber)
pathClosing(Image, PathLength, GapNumber, Direction)
completePathClosing(Image, PathLength, GapNumber)
```
Image représente l'image à traiter<br>
PathLength représente la longueur d'un chemin,<br>
GapNumber représente le nombre de trou présent au maximum dans un chemin,<br>
Direction représente le graphe de voisinage utilisé (1 = N-S, 2=NE-SW, 3=E-W, 4=SE-NW)

Les fonctions completePathOpening et completePathClosing renvoie l'ouverture par chemin (respectivement la fermeture) calculé dans les quatres directions

**Exemple d'utilisation**

```py
import PathOpening as po    # Notre module
import cv2                  # Pour la lecture d'image

# Lecture d'une image
img = cv2.imread("../Images/DNAGI.tif", cv2.IMREAD_GRAYSCALE)

result = po.completePathOpening(img, 70, 3)

# Ecriture du résultat
cv2.imwrite("../Results/DNAGI-out-70-3.tif", result)
```
