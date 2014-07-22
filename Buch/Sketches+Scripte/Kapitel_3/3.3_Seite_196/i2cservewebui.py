from flask import Flask
import time
import smbus
app = Flask(__name__, static_url_path='/static', static_folder='/usr/local/hausautomation/static')

bus = smbus.SMBus(1) # 0 bei Revision 1
address = 0x03       # Adresse des Arduino
outlets = [ "licht-flur", "licht-wohnen", "licht-schlafen" ]

def convertStrToListHex(charArr):
   return map(lambda x: ord(x), charArr)
   lstHex = []
   for c in charArr:
      lstHex.append(ord(c))
   return lstHex

def writeToArduino(val, tgt):
    try:
        bus.write_i2c_block_data( address, val, convertStrToListHex(tgt))
	return 1
    except:
        # print "Ooops, sending failed!"
    	return -1

def outputHtml(msg):
    html = """<html><head><title>Haussteuerung</title>
      <meta name='viewport' content='width=500px' /> 
      <link type='text/css' rel='stylesheet' media='screen' href='/static/style.css' />
      </head><body><div class='col'><p>"""
    html += msg
    html += "</p>"
    for o in outlets:
        html += " <a href='/webui/" + o + "/1'>" + o + " AN</a>"
        html += " <a href='/webui/" + o + "/0'>" + o + " AUS</a>"
    html += "</div></body></html>"
    return html
    
@app.route('/')
def default_route():
    return outputHtml("")

@app.route('/webui/<target>/<value>')
def webui_put(value, target):
    while writeToArduino(int(value), target) < 1:
        time.sleep(1)
        writeToArduino(int(value), target)
    if int(value) > 0:
        return outputHtml("Schalte an")
    else:
        return outputHtml("Schalte aus")

@app.route('/data/put/<target>/<value>')
def simple_put(value, target):
    while writeToArduino(int(value), target) < 1:
    	time.sleep(1)
    	writeToArduino(int(value), target)
    return "<html><body>done</body></html>\n"

if __name__ == "__main__":
    app.run(host='0.0.0.0',port='80')


