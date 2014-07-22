import os
import time
import smbus

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03

# Adresse des Arduino
btaddr = 'BC:F5:AC:53:28:4A'

def convertStrToListHex(charArr):
   return map(lambda x: ord(x), charArr)

def writeToArduino(val, tgt):
   try:
      bus.write_i2c_block_data( address, val, convertStrToListHex(tgt))
      return 1
   except:
      # print "Ooops, sending failed!"
      return -1

for i in range(0, 4):
   exitcode = os.system("hcitool info " + btaddr)
   if exitcode < 1:
      print "Geraet gefunden!"
      writeToArduino(1, "licht-arbeiten")
      exit(0)
   time.sleep(30)

print "Geraet nicht gefunden!"
writeToArduino(0, "licht-arbeiten")
exit(1)

