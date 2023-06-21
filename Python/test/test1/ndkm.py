import cv2
import face_recognition

imgA = face_recognition.load_image_file("pic/images2.jpg")
imgA = cv2.cvtColor(imgA,cv2.COLOR_BGR2RGB)

imgB = face_recognition.load_image_file("pic/image_9.jpg")
imgB = cv2.cvtColor(imgA,cv2.COLOR_BGR2RGB)

faceloc = face_recognition.face_locations(imgB)[0]
print(faceloc)

encodeA = face_recognition.face_encodings(imgA)[0]
cv2.rectangle(imgA,(faceloc[3], faceloc[0]),(faceloc[1], faceloc[2]), (255,0,0),2 )

cv2.imshow("a",imgA)
cv2.waitKey()

