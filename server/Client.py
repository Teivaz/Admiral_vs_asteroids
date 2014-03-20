import time, threading, select

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
					self.package = self.conn.recv(25)
				except:
					self.alive = False
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

	def __del__(self):
		self.Disconnect()

	package = []
	conn = 0
	addr = ()
	lastActivity = 0
	lock = threading.RLock()
	alive = False
