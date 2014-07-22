from flask import Flask
import time
import smbus
app = Flask(__name__)

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03       # Adresse des Arduino

def convertStrToListHex(charArr):
   return map(lambda x: ord(x), charArr)

def writeToArduino(val, tgt):
    try:
        bus.write_i2c_block_data( address, val, convertStrToListHex(tgt))
	return 1
    except:
        # print "Ooops, sending failed!"
    	return -1

@app.route('/data/put/<target>/<value>')
def simple_put(value, target):
    while writeToArduino(int(value), target) < 1:
    	time.sleep(1)
    	writeToArduino(int(value), target)
    return "<html><body>done</body></html>\n"

if __name__ == "__main__":
    app.run(host='0.0.0.0',port='80')


