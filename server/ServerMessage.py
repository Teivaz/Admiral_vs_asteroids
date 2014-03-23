import socket, array

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
		raw.append(socket.htonl(0))
		raw.append(socket.htonl(1))		# size of header
		raw.append(socket.htonl(header))	# header
		return raw

	def Size(self, data):
		return len(data)

	# 1, header size, [header], payload size, [payload]
	def CreateMessage(self, rawHeader, payload):
		message = rawHeader.append(Size(payload))
		for long in payload:
			message = message.append(socket.htonl(long))
		message[0] = socket.htonl(len(message));
		return buffer(message)

	size = 0
	message = []
						
def ReadMessage(connection):
	lenRaw = array.array('l', connection.recv(4))
	packLen = socket.ntohl(lenRaw[0])
	msgRaw = connection.recv(packLen * 4)
	return DecodeMessage(msgRaw)

def DecodeMessage(msg):
	msgAlligned = array.array('l', msg)
	msgDecoded = array.array('l')
	for long in msgAlligned:
		msgDecoded.append(socket.ntohl(long))

	headerSize = msgDecoded[0]
	payloadOffset = headerSize + 2
	payloadSize = msgDecoded[payloadOffset - 1]
	header = msgDecoded[1 : 1 + headerSize]
	payload = msgDecoded[payloadOffset : payloadOffset + payloadSize]
	return header, payload