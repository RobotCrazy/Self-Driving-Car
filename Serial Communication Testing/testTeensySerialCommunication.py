# import serial
# import time

# batteryLevelVal = 0

# def batteryLevel(data:bytes) -> tuple[str, int]:
#     #bl=0
#     return data.decode("utf-8").split('=')[0] + str(int.from_bytes(data.decode("utf-8").split('=')[1].encode("utf-8"), "big")), int.from_bytes(data.decode("utf-8").split('=')[1].encode("utf-8"), "big")
    
# def incomingToStr(data: bytes) -> str:
#     return data[0:3].decode("utf-8")+ str(int.from_bytes(data[3:-1], "big"))
   

# ser = serial.Serial(port="COM3", baudrate=115200)

# while(True):
#     incomingData = ser.read_until(b'\n')
#     if incomingData: 
#         print(incomingData)

#     # incomingData = ser.read_until(b'\n')
#     # batteryPrint = batteryLevel(incomingData)[0]
#     # batteryLevelVal = batteryLevel(incomingData)[1]
#     # if incomingData:
#     #     # batteryLevelStr = batteryPrint[batteryPrint.index("="):]
#     #     print(batteryLevelVal)

#     # ser.write(b'ms=50')
#     # incomingData = ser.read_until(b'\n')
#     # if(incomingData):
#     #     print(incomingToStr(incomingData))
    
#     time.sleep(0.05)

# # print("Connected to " + ser.portstr)


import serial
import time

# rms ( A: requested motor speed ) = num
# rsa ( A: request steering angle ) = num
# gms ( J: get motor speed ) = num
# gbl ( J: get battery level ) = num

BATTERYLEVEL = 0
M0TORSPEED = 0

def getInformationArduino(data) -> tuple[str, int]:
    return  data.decode("utf-8").split('=')[0] + \
            str(int.from_bytes(data.decode("utf-8").split('=')[1].encode("utf-8"), "big")), \
            int.from_bytes(data.decode("utf-8").split('=')[1].encode("utf-8"), "big")

def sendInformationArduino(data: str, value: int, ser) -> bytes:
    sendData = f'{data}{value}'
    return ser.write(sendData.encode())

def getMotorSpeed(data: bytes) -> tuple[str, int]:
    return getInformationArduino(data)

def getBatteryLevel(data: bytes) -> tuple[str, int]:
    return getInformationArduino(data)

def sendMotorSpeed(value: int, ser) -> bytes:
    return sendInformationArduino("RMS=", value, ser)

def sendSteeringAngle(value: int, ser) -> bytes:
    return sendInformationArduino("RSA=", value, ser)
    

ser = serial.Serial(port="COM3", baudrate=115200)

ser.baudrate = 115200  # set Baud rate to 9600
ser.bytesize = 8     # Number of data bits = 8
ser.parity   ='N'    # No parity
ser.stopbits = 1     # Number of Stop bits = 1

time.sleep(3)

# numBytesWritten = ser.write(b'AB') #This one works with the Arduino
# echoedValue = ser.read().decode("utf-8")

# print(echoedValue)

ser.write("rms=1000".encode())
time.sleep(0.5) 
data = ser.readline().decode("ascii")
print(data)
numberStr = data[data.index("=")+1:]
print(numberStr)
print(int(numberStr))


ser.close()

# while(True):
#     try:
#         test = "RMS=50\n".encode("utf-8")
#         ser.write(test)
#         print(f'Sent: {test}')
#     except:
#         print("Did not send!")

#         time.sleep(10)
#     incomingData = ser.read_until(b'\n')
#     if(incomingData):
#         print(incomingData)

    
    # incomingData = ser.read_until(b'\n')
    # #getvalues
    # if (incomingData[0:3] == "GMS"):
    #     print(f"Motor Speed: {getMotorSpeed(incomingData)[1]}")
    #     MOTORSPEED = getMotorSpeed(incomingData)[1]
    # elif (incomingData[0:3] == "GBL"):
    #     print(f"Battery Level: {getBatteryLevel(incomingData)[1]}")
    #     BATTERYLEVEL = getBatteryLevel(incomingData)[1]
    # sendMotorSpeed(50, ser)
    # sendSteeringAngle(20, ser)
    # time.sleep(0.1)
