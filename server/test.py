import socket, time

sock = socket.socket()
sock.connect(("127.0.0.1", 1234))

while True:
	time.sleep(1)
	sock.send("test!\n")
