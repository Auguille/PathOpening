import numpy as np
import PathOpening as po

img = np.array([[0,0,0,4],[0,2,3,5],[0,2,0,0],[1,2,0,0]])

print(img)

test = po.PO(img)
for i in range(1,5):
    imgres = test.computePO(4, i)
    test.reset()

print(imgres)