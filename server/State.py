import select, socket, threading, time
from Client import Client
from ServerMessage import *

# Base state class
class BaseServerState:
	def __init__(self):
		None

	def Update(self, clients):
		None

	def IsFinished(self):
		return True

	def GetNextState(self):
		state = Lobby()
		return state

	def AllowConnections(self):
		return False

class Lobby:
	def __init__(self):
		None

	def Update(self, clients):
		for client in clients:
			print(client.GetLastPackage()[2])

	def IsFinished(self):
		return self.isFinished

	def GetNextState(self):
		state = Loading()
		return state

	def AllowConnections(self):
		return True

	isFinished = False


class Loading:
	def __init__(self):
		None

	def Update(self, clients):
		None

	def IsFinished(self):
		return self.isFinished

	def GetNextState(self):
		state = GamePlay()
		return state
	
	def AllowConnections(self):
		return False

	isFinished = False


class GamePlay:
	def __init__(self):
		None

	def Update(self, clients):
		None

	def IsFinished(self):
		return True

	def GetNextState(self):
		state = Lobby()
		return state
	
	def AllowConnections(self):
		return False
