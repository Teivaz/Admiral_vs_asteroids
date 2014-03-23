import socket, time, array

sock = socket.socket()
sock.connect(("127.0.0.1", 1234))

status = False

while True:
	data = array.array('l')
	status = not status
	data.append(socket.htonl(0)) # msg total len
	data.append(socket.htonl(1)) # header len
	data.append(socket.htonl(2)) # type
	data.append(socket.htonl(1)) # len
	data.append(socket.htonl(status)) # body
	data[0] = socket.htonl(len(data))
	sock.send(data)
	print(data)
	time.sleep(1)
