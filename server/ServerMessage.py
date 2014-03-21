
class MessageType:
	PING = 0
	GET_CLIENT_INFO = 1 # name, w response
	GET_STATUS = 2		# ready / not ready, w response
	LOBBY_USERS = 3		# number of users, their names and stauses
	

class ServerMessage:
	def __init__(self, type, payload):
		rawHeader = self.CreateHeader(header)
		self.message = self.CreateMessage(rawHeader, payload)
		self.size = self.Size(message)

	def CreateHeader(self, header):
		raw = []
		raw.append(1)		# always 1 to determine little endian / big endian
		raw.append(1)		# size of header
		raw.append(header)	# header
		return raw

	def Size(self, data):
		return len(data)

	# 1, header size, [header], payload size, [payload]
	def CreateMessage(self, rawHeader, payload):
		message = rawHeader.append(Size(payload))
		message = message.append(payload)
		return buffer(message)

	size = 0
	message = []

