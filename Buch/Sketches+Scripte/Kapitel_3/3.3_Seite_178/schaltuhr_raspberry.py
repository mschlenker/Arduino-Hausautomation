import smbus
import time
import math
import random
import array
from datetime import datetime, date, 
def writeToArduino(val, tgt):
    try:
        bus.write_i2c_block_data( address, val, convertStrToListHex(tgt))
        return 1
    except:
        print "Ooops, sending failed!"
        return -1

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03       # Adresse des Arduino

t = datetime.now()
this_hour = t.hour
this_min  = t.minute

switchtimes = [
  # hr, min,         name,       state
  [ 17,  57, "licht-flur",         "1" ],
  [ 23,   0, "licht-flur",         "0" ],
  [ 18,   0, "licht-wohnen",       "1" ],
  [ 23,  30, "licht-wohnen",       "0" ],
  [  6,  30, "heizung-schlafen", "200" ],
  [  8,  30, "heizung-schlafen", "180" ],
  [  6,  30, "heizung-bad",      "220" ],
  [  8,  30, "heizung-bad",      "190" ],
  [ 18,  30, "heizung-bad",      "220" ],
  [ 20,  30, "heizung-bad",      "180" ],
  [  6,  30, "heizung-kinder",   "205" ],
  [ 18,  30, "heizung-kinder",   "190" ]
]

for s in switchtimes:
  if s[0] == this_hour and s[1] == this_min:
    print "Switching: ", s[2]
    while writeToArduino(int(s[3]), s[2]) < 1:
        time.sleep(1)
        print "Trying again"
        writeToArduino(int(s[3]), s[2])    

