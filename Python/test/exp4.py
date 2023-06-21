import cv2
import numpy as np
import os
import sqlite3
from PIL import Image
# import serial
# import time
#
#
# ser = serial.Serial("COM6", 115200)

#trainning
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
recognizer = cv2.face.LBPHFaceRecognizer_create()

recognizer.read('C:/Users/hoang/OneDrive/Desktop/DOAN1/recoginzer/trainningData.yml')

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

def checkfaceid(cap , ret , frame):
    # cap = cv2.VideoCapture(0)
    rxbuffer = "None"
    # ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray)
    for(x, y, w, h) in faces:
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0,255,0), 2)

        roi_gray = gray[y: y+h , x: x+ w]

        id, confidence = recognizer.predict(roi_gray)

        if confidence < 40:
            profile = getProfile(id)
            if(profile != None):
                cv2.putText(frame, " "+str(profile[1]), (x+ 10, y +h +30), fontface, 1 , (0,255,0),2  )
                rxbuffer = "True." + str(id)
        else:
            cv2.putText(frame, "Unknow ", (x + 10, y + h + 30), fontface, 1, (0,0, 255), 2)
            rxbuffer = "False"
    return  str(rxbuffer)


# cap = cv2.VideoCapture(0)
# ret, frame = cap.read()
# count = 0
# while True :
#     # cv2.imshow('feame', frame)
#     ret, frame = cap.read()
#     str1 = checkfaceid(cap , ret, frame)
#     cv2.imshow('feame', frame)
#     print(str1)
#     if str1 == "True" :
#         count += 1
#     if str1 == "False" :
#         count -=1
#
#     print(count)
#     if count < -100 :
#         rxbuffer = "False"
#         ser.write(str(rxbuffer).encode())
#         count =0
#         time.sleep(10)
#     if count > 100 :
#         rxbuffer = "True"
#         ser.write(str(rxbuffer).encode())
#         count =0
#         time.sleep(10)


cap = cv2.VideoCapture(0)


count = 0

while(True):
    rxbuffer = "None"
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray)
    for(x, y, w, h) in faces:
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0,255,0), 2)

        roi_gray = gray[y: y+h , x: x+ w]

        id, confidence = recognizer.predict(roi_gray)

        if confidence < 40:
            profile = getProfile(id)
            if(profile != None):
                cv2.putText(frame, " "+str(profile[1]), (x+ 10, y +h +30), fontface, 1 , (0,255,0),2  )
                # rxbuffer = "True"
                count += 1
        else:
            cv2.putText(frame, "Unknow ", (x + 10, y + h + 30), fontface, 1, (0,0, 255), 2)
            # rxbuffer = "False"
            count -= 1

    cv2.imshow('feame',frame)
    print(count)
    if count < -100 :
        rxbuffer = "False"
        ser.write(str(rxbuffer).encode())
        count =0
        time.sleep(10)
    if count > 100 :
        rxbuffer = "True"
        ser.write(str(rxbuffer).encode())
        count =0
        time.sleep(10)

    # ser.write(str(rxbuffer).encode())
    if(cv2.waitKey(1) == ord('q')):
        break;



cap.release()
cv2.destroyAllWindows()



