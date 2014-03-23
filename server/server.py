import select, socket, threading, time
from Client import Client
from State import *

MAX_PING = 500 # seconds



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
			# remove idle clients
			for client in self.clients:
				clientAlive = client.IsActive() and client.GetLastActivity() > (time.time() - MAX_PING)
				if clientAlive == False:
					self.clients.remove(client)

			# Process pending connections
			self.lock.acquire()
			if len(self.pendingConnections) > 0:
				client = self.pendingConnections[0]
				self.state.OnConnectionDetected(client, self.clients)
				self.pendingConnections.remove(client)
			self.lock.release()
			
			self.state.Update(self.clients)

			if self.state.IsFinished():
				self.state = self.state.GetNextState()



	def ConnectionMonitor(self):
		while self.connected:
			inputready, outputready, exceptready = select.select([self.sock], [], [], 1.0)
			if inputready and self.connected:
				(conn, addr) = self.sock.accept()
				print("connection detected: {0}".format(addr))
				self.lock.acquire()
				self.pendingConnections.append(Client(conn, addr))
				self.lock.release()

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
	pendingConnections = []
	state = BaseServerState()

def main():
	server = Server(1234)
	server.Run()

main()
