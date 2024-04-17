import serial
import time

import random
# import time
# import threading
# # rms ( A: requested motor speed ) = num
# # rsa ( A: request steering angle ) = num
# # gms ( J: get motor speed ) = num
# # gbl ( J: get battery level ) = num
# BATTERYLEVEL = 0
# MOTORSPEED = 0

# # def update_values():
# #     global BATTERYLEVEL, MOTORSPEED
# #     for i in range(50):
# #         BATTERYLEVEL = max(0, BATTERYLEVEL - i)  # Ensure BATTERYLEVEL does not go below 0
# #         MOTORSPEED = (MOTORSPEED + 10) % 201  # Example update logic for MOTORSPEED
# #         time.sleep(1.5)

# # def start_updating():
# #     thread = threading.Thread(target=update_values)
# #     thread.daemon = True  # Daemon threads are killed when the main program exits
# #     thread.start()
# def getInformationArduino(data: bytes) -> tuple[str, int]:
#     return  data.decode("utf-8").split('=')[0] + \
#             str(int.from_bytes(data.decode("utf-8").split('=')[1].encode("utf-8"), "big")), \
#             int.from_bytes(data.decode("utf-8").split('=')[1].encode("utf-8"), "big")

# def sendInformationArduino(data: str, value: int, ser) -> bytes:
#     sendData = f"{data}{value}"
#     print(sendData.encode())
#     return ser.write(sendData.encode("utf-8"))

# def getMotorSpeed(data: bytes) -> tuple[str, int]:
#     return getInformationArduino(data)

# def getBatteryLevel(data: bytes) -> tuple[str, int]:
#     return getInformationArduino(data)

# def sendMotorSpeed(value: int, ser) -> bytes:
#     return sendInformationArduino("RMS=", value, ser)

# def sendSteeringAngle(value: int, ser) -> bytes:
#     return sendInformationArduino("RSA=", value, ser)
    
# def start_reading(ser):
#     def read_loop():
#         global MOTORSPEED, BATTERYLEVEL
#         while True:
#             print("rms=1000".encode())
#             # sendMotorSpeed(100, ser)
#             ser.write("rms=200".encode())
#             time.sleep(0.5) 
#             data = ser.readline().decode("ascii")
#             print(ser)
#             # print(f"Data: {data}")
#             numberStr = data[data.index("=")+1:]
#             MOTORSPEED = int(numberStr)
#             print(numberStr)
#             print(int(numberStr))
#             time.sleep(5)
#         ######
#         # incomingData = ser.read_until(b'\n')
#         # if incomingData[0:3] == b'GMS':
#         #     global MOTORSPEED
#         #     MOTORSPEED = getMotorSpeed(incomingData)[1]
#         # elif incomingData[0:3] == b'GBL':
#         #     global BATTERYLEVEL
#         #     BATTERYLEVEL = getBatteryLevel(incomingData)[1]
#         # sendMotorSpeed(50, ser)
#         # sendSteeringAngle(20, ser)
#         # time.sleep(0.1)

#     thread = threading.Thread(target=read_loop)
#     thread.daemon = True  # This will make the thread exit when the main program exits
#     thread.start()

ser = serial.Serial(port="COM8", baudrate=115200, timeout = 0.01)
time.sleep(3)


while True:
    num = random.randint(-1, 1)
    ser.write(f"dd={num}".encode())
    data = ser.readline().decode("ascii")
    print(data)
    