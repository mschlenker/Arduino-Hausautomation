
import cgi
outlets = [ "licht-flur", "licht-wohnen", "licht-schlafen" ]

print "Content-Type: text/html"
print
print "<html><body>"
for o in outlets:
   print "<a href='index.py?outlet=" + o + "&action=1'>" + o + " an</a>"
   print "<a href='index.py?outlet=" + o + "&action=0'>" + o + " aus</a>"
   print "</body></html>"


