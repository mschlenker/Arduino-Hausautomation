import socket

UDP_IP = "10.76.23.56"
UDP_PORT = 5678

sock = socket.socket(socket.AF_INET, # Internet
	socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	print "raw message: ",data
	toks = data.split(':')
	if len(toks) > 1:
		print toks[0]," : ",toks[1]
