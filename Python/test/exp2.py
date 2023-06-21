import cv2
import numpy as np
import sqlite3
import os
from PIL import Image

def insertOrUpdate(id, name):

    conn = sqlite3.connect('C:/Users/hoang/OneDrive/Desktop/DOAN1/data.db')

    query = "SELECT * FROM people WHERE ID=" + str(id)
    cusror = conn.execute(query)

    isRecordExist = 0
    for row in cusror:
        isRecordExist = 1

    if(isRecordExist == 0):
        query = "INSERT INTO people (ID, Name) VALUES(" +str(id) + ",'" + str(name) + "')"
    else:
        query = "UPDATE people SET Name='" +str(name) + "' WHERE ID="+ str(id)

    conn.execute(query)
    conn.commit()
    conn.close()

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
cap = cv2.VideoCapture(0)

id = input("Enter your ID: ")
name = input("Enter your Name: ")
insertOrUpdate(id, name)

sampleNum = 0

while(True):
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for(x, y, w, h) in faces:
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0,255,0), 2)

        if not os.path.exists('dataSet'):
            os.mkdir('dataSet')
        sampleNum +=1

        cv2.imwrite('dataSet/User.' +str(id)+'.' +str(sampleNum) +'.jpg', gray[y: y+ h, x: x+ w])

    cv2.imshow('frame', frame)
    cv2.waitKey(100)

    if sampleNum > 99 :
        break;

cap.release()
cv2.destroyAllWindows()

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



