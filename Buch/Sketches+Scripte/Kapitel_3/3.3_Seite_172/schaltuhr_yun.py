import sys    
import socket
sys.path.insert(0, '/usr/lib/python2.7/bridge/') 
from bridgeclient import BridgeClient as bridgeclient
from datetime import datetime, date, time

mbval = bridgeclient()

t = datetime.now()
this_hour = t.hour
this_min  = t.minute

switchtimes = [
  # hr, min,         name,       state 
  [ 15,  10, "licht-flur",         "1" ],
  [ 17,  45, "licht-flur",         "0" ],
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
    mbval.put(s[2], s[3])

