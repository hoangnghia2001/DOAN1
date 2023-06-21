import serial
import time


ser = serial.Serial("COM6", 115200)

time.sleep(1)


counter = 0
data = "test"

while True:
    data = "test %d" %(counter)
    ser.write(str(data).encode())
    i = 0
    # while ser.inWaiting() == 0:
    #
    #     pass
    print( ser.inWaiting())
    while ser.inWaiting() != 0:
        x = ser.read(6)
        x = str(x, 'UTF-8').strip("\x00")
        print(x)
        if ser.inWaiting() == 0:
            break
    time.sleep(10)
    counter = counter + 1
    time.sleep(1)

