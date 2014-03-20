import socket, time, array

sock = socket.socket()
sock.connect(("127.0.0.1", 1234))

status = False

while True:
	data = array.array('l')
	status = not status
	data.append(1)
	data.append(1)
	data.append(2)
	data.append(1)
	data.append(status)
	#buf = buffer(data, 0)
	sock.send(data)
	print(data)
	time.sleep(1)
