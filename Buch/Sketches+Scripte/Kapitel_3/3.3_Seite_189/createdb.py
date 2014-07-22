import sys
import socket
import sqlite3
sys.path.insert(0, '/usr/lib/python2.7/bridge/')
from bridgeclient import BridgeClient as bridgeclient
from datetime import datetime, date, time

# Mailbox- und Datenbankverbindung
mailbox = bridgeclient()
dbconn = sqlite3.connect('/usr/local/hausautomation/sensors.sqlite')
cursor = dbconn.cursor()

# Datum zerlegen
t = datetime.now()
this_hour = t.hour
this_min = t.minute
this_day = t.day
this_mon = t.month
this_year = t.year

# Tabelle anlegen:
try:
   cursor.execute("CREATE TABLE sensors (year int, month int, day int, hour int, min int, node int, value int)")
except:
   print "Creating table failed!"

# Sensoren auslesen und in die Datenbank schreiben:
sensors = [ 5, 23 ]
for s in sensors:
   sval = mailbox.get("sensor-" + str(s))
   if sval is None:
      print "Empty value!"
   else:
      cursor.execute("INSERT INTO sensors VALUES (?,?,?,?,?,?,?)", (this_year, this_mon, this_day, this_hour, this_min, s, int(sval)))

dbconn.commit()
dbconn.close()

