import time, threading, select, array
from ServerMessage import *


class Client:
	def __init__(self, connection, address):
		self.conn = connection
		self.address = address
		self.alive = True
		self.lastActivity = time.time()
		task = threading.Thread(target=Client.Task, args=(self,))
		task.start()

	def IsReady(self):
		return False

	def GetLastActivity(self):
		self.lock.acquire()
		lastActivity = self.lastActivity
		self.lock.release()
		return lastActivity

	def GetLastPackage(self):
		self.lock.acquire()
		ret = self.package
		self.lock.release()
		return ret

	def IsActive(self):
		return self.alive

	def Task(self):
		while self.alive:
			inputready, outputready, exceptready = select.select([self.conn], [], [], 1.0)
			if inputready:
				self.lock.acquire()
				try:
					endiansMatch = array.array('l', self.conn.recv(4))[0] == 1
					headerSize = array.array('l', self.conn.recv(4))[0]
					type = array.array('l', self.conn.recv(headerSize*4))[0]
					payloadSize = array.array('l', self.conn.recv(4))[0]
					if payloadSize == 0:
						self.package[type] = True
					else:
						self.package[type] = array.array('l', self.conn.recv(payloadSize*4))
				except:
					pass
					#self.alive = False
				else:
					self.lastActivity = time.time()
				self.lock.release()

	def Disconnect(self):
		#print("Down")
		if self.alive:
			self.lock.acquire()
			self.conn.close()
			self.alive = False
			self.lock.release()

	def SendMessage(self, message):
		if self.alive:
			self.conn.send(message.message)

	def __del__(self):
		self.Disconnect()

	package = {}
	conn = None
	addr = ()
	lastActivity = 0
	lock = threading.RLock()
	alive = False
