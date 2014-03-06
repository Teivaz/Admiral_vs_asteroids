import socket, threading

PORT = 1234


lock = threading.RLock()

def listen(sock, clients):
	while True:
		try:
			lock.release()
		except:
			None
		try:
			(conn, addr) = sock.accept()
		except:
			break;
		lock.acquire()
		print("connection detected: {0}".format(addr))
		clients[addr] = conn
		print("connected!")
		#run = False
	print("thread exit!")

sock = socket.socket()

sock.bind(('', PORT))

sock.listen(100)
clients = dict()

listenerThread = threading.Thread(target=listen, args=(sock,clients))
listenerThread.start()
#listen(sock,clients, run)

monitor = True
while monitor:
	lock.acquire()
	for addr, conn in clients.iteritems():
		try:
			data = conn.recv(25)
			if not data:
				break
			print("{0} : \n\t{1}".format(addr, data))
		except:
			monitor = False
			sock.close()
			sock = None
			print("close")
	lock.release()

