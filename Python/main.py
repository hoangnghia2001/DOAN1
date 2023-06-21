# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
# from exp4 import checkfaceid
import function
import cv2
import numpy as np
# import os
import serial
import time


ser = serial.Serial("COM7", 115200)

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")

recognizer = cv2.face.LBPHFaceRecognizer_create()

recognizer.read('C:/Users/hoang/OneDrive/Desktop/DOAN1/recoginzer/trainningData.yml')




def readdata(ser) :
    x = ""
    while ser.inWaiting() != 0:
        x = ser.read(6)
        x = str(x, 'UTF-8').strip("\x00")
        if ser.inWaiting() == 0:
            break
    return  x

def checkface100():
    count = 0
    id = 0
    str5 = ""
    while str5 != "Exit  ":
        ret, frame = cap.read()
        str5 = function.checkfaceid(cap, ret, frame, recognizer, face_cascade)
        print(str5)

        if str5[:4] == "True":
            if id == 0 :
                id = int(str5.split('.')[1])
            if int(str5.split('.')[1]) == id :
                if count < 0:
                    count = 0
                count += 1
            else:
                id = int(str5.split('.')[1])
                count = 1
        if str5 == "False":
            count -= 1
        str5 = readdata(ser)
        print(count)
        if count < -100:
            count = 0
            return "False"
        if count > 20:
            count = 0
            return "True." + str(id)
    return "Exit  "

def setupfaceid(cap) :
    str2 = readdata(ser)
    while str2 != "Ready ":
        str2 = readdata(ser)
        if str2[:3] == "Che":
            print(str2)
            if int(str2.split('.')[1]) == 0:
                str4 = ""
                while str4 != "Exit  ":
                    str4 = checkface100()
                    print(str4)
                    ser.write(str(str4).encode())
            else :
                ttt = function.checkface(int(str2.split('.')[1]))
                ser.write(str(ttt).encode())
        elif str2[:3] == "Add" :
            print(str2)
            function.addfaceid(cap, recognizer, face_cascade, int(str2.split('.')[1]))
            ser.write(str("True").encode())
            print("True")
        elif str2[:3]== "Rem" :
            print(str2)
            if int(str2.split('.')[1]) == 99:
                function.removeall(recognizer)
                ser.write(str("True").encode())
                print("True")
            elif int(str2.split('.')[1]) == 0:
                str2 = readdata(ser)
                str3 = ""
                while str3 != "Exit  ":
                    str3 = checkface100()
                    print(str3)
                    if str(str3)[:4] == "True" :
                        function.remofaceid(recognizer,int(str3.split('.')[1]))
                        ser.write(str(str3).encode())
            else:
                function.remofaceid(recognizer,int(str2.split('.')[1]))
                ser.write(str("True").encode())
                print("True")
        else: pass
    print(str2)
    return


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
cap = cv2.VideoCapture(0)
if __name__ == '__main__':
    print_hi('PyCharm')
    count = 0
    id = 0
    while True :
        # cv2.imshow('feame', frame)
        ret, frame = cap.read()
        str1 = function.checkfaceid(cap , ret, frame, recognizer, face_cascade)
        print(str1)

        if str1[:4] == "True" :
            if id == 0:
                id = int(str1.split('.')[1])
            if int(str1.split('.')[1]) == id:
                if count < 0:
                    count = 0
                count += 1
            else:
                id = int(str1.split('.')[1])
                count = 1
        if str1 == "False" :
            count -=1

        print(count)
        if count < -100 :
            rxbuffer = "False"
            ser.write(str(rxbuffer).encode())
            count =0
            id = 0
            time.sleep(5)
        if count > 20 :
            ser.write(str(str1).encode())
            count =0
            id = 0
            time.sleep(5)

        str1 = readdata(ser)
        if str1 != "" :
            print(str1)
            if str1 == "Stop  " :
                print(str1)
                setupfaceid(cap)





cap.release()
cv2.destroyAllWindows()
# See PyCharm help at https://www.jetbrains.com/help/pycharm/
