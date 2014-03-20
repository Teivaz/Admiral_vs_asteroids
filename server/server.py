import select, socket, threading, time
from Client import Client

PORT = 1234


lock = threading.RLock()

def MonitorNewConnections(sock, clients):
	timeout = 1 # seconds in float
	while True:
		inputready, outputready, exceptready = select.select([sock], [], [], timeout)
		if inputready:
			(conn, addr) = sock.accept()
			lock.acquire()
			print("connection detected: {0}".format(addr))
			clients.append(Client(conn, addr))
			lock.release()
			print("connected!")
		continue		
	print("thread exit!")

sock = socket.socket()

sock.bind(('', PORT))

sock.listen(5)
clients = []

listenerThread = threading.Thread(target=MonitorNewConnections, args=(sock,clients))
listenerThread.start()
#listen(sock,clients, run)

monitor = True
while monitor:
	lock.acquire()
	for client in clients:
		if client.IsActive():
			print(client.GetLastPackage())
		else:
			clients.remove(client)

	lock.release()
	time.sleep(10)


