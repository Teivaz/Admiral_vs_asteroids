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

	def OnConnectionDetected(self, client, clients):
		client.close()

class Lobby:
	def __init__(self):
		None

	def Update(self, clients):
		for client in clients:
			try:
				print(client.GetLastPackage()[2])
			except:
				None

	def IsFinished(self):
		return self.isFinished

	def GetNextState(self):
		state = Loading()
		return state

	def OnConnectionDetected(self, client, clients):
		clients.append(client)

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

	def OnConnectionDetected(self, client, clients):
		client.close()

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

	def OnConnectionDetected(self, client, clients):
		client.close()

