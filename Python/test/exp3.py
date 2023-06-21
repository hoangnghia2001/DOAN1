import cv2
import numpy as np
import os
from PIL import Image

recognizer = cv2.face.LBPHFaceRecognizer_create()

path = 'dataSet'

def getImageWithId(path):
    imagePaths = [os.path.join(path, f) for f in os.listdir(path)]

    faces = []
    IDs = []

    for imagePath in imagePaths:

        faceImg = Image.open(imagePath).convert('L')
        faceNp = np.array(faceImg, 'uint8')

        print(faceNp)

        Id = int(imagePath.split('.')[1])

        faces.append(faceNp)
        IDs.append(Id)

        cv2.imshow('trainning', faceNp)
        cv2.waitKey(100)

    return faces, IDs

faces, Ids = getImageWithId(path)

recognizer.train(faces, np.array(Ids))

if not os.path.exists('recoginzer'):
    os.makedirs('recoginzer')

recognizer.save('recoginzer/trainningData.yml')

cv2.destroyAllWindows()