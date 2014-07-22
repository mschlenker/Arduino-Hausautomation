import smbus
import time
import math
import random

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03       # Adresse des Arduino

def writeToArduino(value):
    bus.write_byte(address, value)
    return -1

def readFromArduino():
    number = bus.read_byte(address)
    return number

while True:
    val = int(random.random() * 5.0) 
    writeToArduino(val)
    print "RPI: Hi Arduino, ich schick Dir ", val
    time.sleep(1)
    number = readFromArduino()
    print "Arduino: Hi RPI, ich hab empfangen ", number
    print

