import cv2
import numpy as np
import sqlite3
import os
from PIL import Image

id = input("Enter your ID: ")


def deleteOrUpdate(id):
    conn = sqlite3.connect('C:/Users/hoang/OneDrive/Desktop/DOAN1/data.db')

    query = "SELECT * FROM people WHERE ID=" + str(id)
    cusror = conn.execute(query)

    isRecordExist = 0
    for row in cusror:
        isRecordExist = 1

    if (isRecordExist == 1):
        query = "DELETE FROM people WHERE ID=" + str(id)

    conn.execute(query)
    conn.commit()
    conn.close()


deleteOrUpdate(id)
sampleNum =0

while True:

    path = 'dataSet/User.' +str(id)+'.' +str(sampleNum) +'.jpg'
    if os.path.isfile(path):
        os.remove(path)


    if sampleNum >199 :
        break;
    sampleNum += 1

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


    return faces, IDs


def is_directory_empty(directory):
    if not os.path.isdir(directory):
        return False  # Không phải là thư mục

    if not os.listdir(directory):
        return False  # Thư mục rỗng

    return True  # Thư mục không rỗng


if is_directory_empty(path):

    faces, Ids = getImageWithId(path)

    recognizer.train(faces, np.array(Ids))

    if not os.path.exists('recoginzer'):
        os.makedirs('recoginzer')

    recognizer.save('recoginzer/trainningData.yml')

    cv2.destroyAllWindows()



