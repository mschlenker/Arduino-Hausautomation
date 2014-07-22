#!/usr/bin/python

import cgi
import sys
import socket
sys.path.insert(0, '/usr/lib/python2.7/bridge/') 
from bridgeclient import BridgeClient as bridgeclient

sys.stderr = sys.stdout


form = cgi.FieldStorage()
mbval = bridgeclient()
outlets = [ "licht-flur", "licht-wohnen", "licht-schlafen" ]

print "Content-Type: text/html"
print

print "<html>"
print "<head>"
print "<title>Haussteuerung</title><meta name='viewport' content='width=500px' /><link type='text/css' rel='stylesheet' media='screen' href='style.css' />"
print "</head>"
print "<body><div class='col'>"
if "outlet" not in form:
  print "<p>Keine Aktion angefragt</p>"
elif form.getvalue("outlet") in outlets and int(form.getvalue("action")) > 0:
  print "<p>Schalte an</p>"
  mbval.put(form.getvalue("outlet"), "1")   
elif form.getvalue("outlet") in outlets:
  print "<p>Schalte aus</p>"
  mbval.put(form.getvalue("outlet"), "0")
else:
  print "<p>Ung&uuml;ltige Steckdose!</p>"
for o in outlets:
  print "<a href='index.py?outlet=" + o + "&action=1'>" + o + " AN</a>"
  print "<a href='index.py?outlet=" + o + "&action=0'>" + o + " AUS</a>"
print "</div></body></html>"



