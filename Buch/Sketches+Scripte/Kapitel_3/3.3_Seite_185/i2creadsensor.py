import smbus
import time
# import math
# import random
import array

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03       # Adresse des Arduino
startSensor = 0 
doTheLoop = True

def readFromArduino():
    global startSensor    
    try:
    	sensorData = bus.read_i2c_block_data(address, 0x01)
    except:
	print "Ooops!"
	return True
    if startSensor == 0:
        startSensor = sensorData[0]
    elif startSensor == sensorData[0]:
        return False
    print "Sensor ID ", sensorData[0]
    sensorVal = sensorData[1]<<8 | sensorData[2]
    print "Value ", sensorVal
    return True

while doTheLoop:
    doTheLoop = readFromArduino()
    time.sleep(1)

