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

La libraire permet l'utilisation d'une fonction :
```py
computePO(PathLength, GapNumber, Direction)
```
PathLength représente la longueur d'un chemin,

GapNumber représente le nombre de trou présent au maximum dans un chemin,

Direction représente le graphe de voisinage utilisé (1 = N-S, 2=NE-SW, 3=E-W, 4=SE-NW)

Cette fonction renvoie l'image calculée à partir du maximum de chaque pixel entre l'image précédemment calculée (Une image nulle si il n'y a pas de précedent) et l'image calculée dans la direction n

**Exemple d'utilisation**

```py
import PathOpening as po    # Notre module
import cv2                  # Pour la lecture d'image

# Lecture d'une image
img = cv2.imread("../Images/DNAGI.tif", cv2.IMREAD_GRAYSCALE)

test = po.PO(img)
for i in range(1,5):
    imgres = test.computePO(70, 3, i)

# Ecriture du résultat
cv2.imwrite("../Results/DNAGI-out-70-3.tif", imgres)
```
