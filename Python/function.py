import cv2
import numpy as np
import os
import sqlite3
import shutil
from PIL import Image




def addfaceid(cap, recognizer, face_cascade, id) :
    def insertOrUpdate(id, name):

        conn = sqlite3.connect('C:/Users/hoang/OneDrive/Desktop/DOAN1/data.db')

        query = "SELECT * FROM people WHERE ID=" + str(id)
        cusror = conn.execute(query)

        isRecordExist = 0
        for row in cusror:
            isRecordExist = 1

        if (isRecordExist == 0):
            query = "INSERT INTO people (ID, Name) VALUES(" + str(id) + ",'" + str(name) + "')"
        else:
            query = "UPDATE people SET Name='" + str(name) + "' WHERE ID=" + str(id)

        conn.execute(query)
        conn.commit()
        conn.close()

    if(id < 32):
        name = "Parent"
    else:
        name = "Children"
    insertOrUpdate(id, name)

    sampleNum = 0

    while (True):
        ret, frame = cap.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)
        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            if not os.path.exists('dataSet'):
                os.mkdir('dataSet')
            sampleNum += 1

            cv2.imwrite('dataSet/User.' + str(id) + '.' + str(sampleNum) + '.jpg', gray[y: y + h, x: x + w])

        # cv2.imshow('frame', frame)
        cv2.waitKey(2)

        if sampleNum > 99:
            break;


    path = 'dataSet'


    faces, Ids = getImageWithId(path)

    recognizer.train(faces, np.array(Ids))

    if not os.path.exists('recoginzer'):
        os.makedirs('recoginzer')

    recognizer.save('recoginzer/trainningData.yml')
    # cv2.destroyAllWindows()

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

def remofaceid(recognizer, id) :
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
    sampleNum = 0

    while True:

        path = 'dataSet/User.' + str(id) + '.' + str(sampleNum) + '.jpg'
        if os.path.isfile(path):
            os.remove(path)

        if sampleNum > 99:
            break;
        sampleNum += 1

    path = 'dataSet'

    if is_directory_empty(path):

        faces, Ids = getImageWithId(path)

        recognizer.train(faces, np.array(Ids))

        if not os.path.exists('recoginzer'):
            os.makedirs('recoginzer')

        recognizer.save('recoginzer/trainningData.yml')
    else :
        path = 'None'
        faces, Ids = getImageWithId(path)

        recognizer.train(faces, np.array(Ids))

        if not os.path.exists('recoginzer'):
            os.makedirs('recoginzer')

        recognizer.save('recoginzer/trainningData.yml')
def is_directory_empty(directory):
    if not os.path.isdir(directory):
        return False  # Không phải là thư mục

    if not os.listdir(directory):
        return False  # Thư mục rỗng

    return True  # Thư mục không rỗng

def removeall(recognizer):
    conn = sqlite3.connect('C:/Users/hoang/OneDrive/Desktop/DOAN1/data.db')
    cursor = conn.cursor()
    cursor.execute(f"DELETE FROM people;")
    conn.commit()
    conn.close()
    path = 'dataSet'
    shutil.rmtree(path)

    if not os.path.exists('dataSet'):
        os.mkdir('dataSet')
    path = 'None'
    faces, Ids = getImageWithId(path)

    recognizer.train(faces, np.array(Ids))

    if not os.path.exists('recoginzer'):
        os.makedirs('recoginzer')
    recognizer.save('recoginzer/trainningData.yml')

# get profile
def getProfile(id):

    conn = sqlite3.connect('C:/Users/hoang/OneDrive/Desktop/DOAN1/data.db')
    query = "SELECT * FROM people WHERE ID=" + str(id)
    cusror = conn.execute(query)

    profile = None

    for row in cusror:
        profile = row

    conn.close()
    return profile

fontface = cv2.FONT_HERSHEY_SIMPLEX

def checkfaceid(cap , ret , frame, recognizer, face_cascade  ):
    # cap = cv2.VideoCapture(0)
    rxbuffer = "None"
    # ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray)
    for(x, y, w, h) in faces:
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0,255,0), 2)

        roi_gray = gray[y: y+h , x: x+ w]

        ids, confidence = recognizer.predict(roi_gray)

        if confidence < 40:
            profile = getProfile(ids)
            if(profile != None):
                rxbuffer = "True." + str(ids)
        else:
            rxbuffer = "False"
    return  str(rxbuffer)

def checkface(id):
    conn = sqlite3.connect('C:/Users/hoang/OneDrive/Desktop/DOAN1/data.db')

    query = "SELECT * FROM people WHERE ID=" + str(id)
    cursor = conn.execute(query)
    result = cursor.fetchall()
    if len(result) > 0:
        return int(id)
    else :
        return 0












