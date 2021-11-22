import PathOpening as po    # Notre module
import cv2                  # Pour la lecture d'image

# Lecture d'une image
img = cv2.imread("Images/Test.pgm", cv2.IMREAD_GRAYSCALE)

imgres = po.completePathOpening(img, 4, 0)

# Ecriture du résultat
cv2.imwrite("Results/Test-opening-4-0.pgm", imgres)
