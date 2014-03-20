import select, socket, threading, time
from Client import Client
from State import *

MAX_PING = 900



class Server:
	def __init__(self, port):
		self.sock = socket.socket()
		self.port = port
		self.lock = threading.RLock()

	def Run(self):
		# Connect socket to the port
		while self.connected == False:
			try:
				self.sock.bind(('', self.port))
				self.sock.listen(5)
			except:
				print("Error connecting to port {0}".format(self.port))
			else:
				self.connected = True

		# Launch connection monitor
		monitor = threading.Thread(target=Server.ConnectionMonitor, args=(self,))
		monitor.start()

		# main loop
		while self.connected == True:
			self.lock.acquire()
			# remove idle clients
			for client in self.clients:
				clientAlive = client.IsActive() and client.GetLastActivity() < (time.time() - MAX_PING)
				if clientAlive == False:
					self.clients.remove(client)
			if self.state:
				self.state.Update(self.clients)
			self.lock.release()

			if self.state and self.state.IsFinished():
				self.state = self.state.GetNextState()



	def ConnectionMonitor(self):
		while self.connected:
			if self.state and self.state.AllowConnections():
				inputready, outputready, exceptready = select.select([self.sock], [], [], 1.0)
				if inputready and self.connected:
					(conn, addr) = self.sock.accept()
					self.lock.acquire()
					print("connection detected: {0}".format(addr))
					self.clients.append(Client(conn, addr))
					self.lock.release()
			else:
				time.sleep(1)

	def Disconnect(self):
		if self.connected:
			self.lock.acquire()
			for client in self.clients:
				client.Disconnect()
			self.sock.close()
			self.lock.release()

	def __del__(self):
		self.Disconnect()

	sock = socket.socket()
	port = 0
	lock = threading.RLock()
	connected = False
	clients = []
	state = BaseServerState()

def main():
	server = Server(1234)
	server.Run()

main()
