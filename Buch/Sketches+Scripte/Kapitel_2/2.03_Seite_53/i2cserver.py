from flask import Flask
import time
import smbus
app = Flask(__name__)

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03       # Adresse des Arduino

def writeToArduino(value):
    bus.write_byte(address, value)
    return -1

def readFromArduino():
    number = bus.read_byte(address)
    return number

@app.route("/1")
def led_on():
    writeToArduino(1)
    reply = "Status der LED ist %d."  % (readFromArduino())
    return reply
    
@app.route("/0")
def led_off():
    writeToArduino(0)
    reply = "Status der LED ist %d."  % (readFromArduino())
    return reply

@app.route("/")
def no_action():
    reply = "Status der LED ist %d."  % (readFromArduino())
    return reply

if __name__ == "__main__":
    app.run(host='0.0.0.0',port='8080')

