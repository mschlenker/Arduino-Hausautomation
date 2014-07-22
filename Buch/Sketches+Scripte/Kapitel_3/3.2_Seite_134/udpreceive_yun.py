import sys    
import socket
sys.path.insert(0, '/usr/lib/python2.7/bridge/') 
from bridgeclient import BridgeClient as bridgeclient

UDP_IP = "10.76.23.232"
UDP_PORT = 5678

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
mbval = bridgeclient()

while True:
	data, addr = sock.recvfrom(1024)
	toks = data.split(':')
	if (len(toks) > 1) and (toks[0] == 'uptime'):
		print toks[1] 
		# Translate key-val pair directly to localstore
		mbval.put(toks[0], str(int(toks[1])) )	
