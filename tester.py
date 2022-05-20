import socket
import time

class IRC:
	irc = socket.socket()

	def __init__(self) -> None:
		self.irc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	def	send(self, user, msg) -> None:
		# print("PRIVMSG " + user + " " + msg + "\n")
		self.irc.send(bytes("PRIVMSG " + user + " :" + msg + "\n", "UTF-8"))
		# print("MSG SENDED")

	def connect(self, server, port, user, channel) -> None:
		print("Connecting to " + server)
		self.irc.connect((server, port))
		time.sleep(1)
		self.irc.send(bytes("PASS " + user + "\n", "UTF-8"))
		time.sleep(1)
		self.irc.send(bytes("NICK " + user + "\n", "UTF-8"))
		time.sleep(1)
		self.irc.send(bytes("USER " + user + " " + user + " " + user + " :" + user + " ", "UTF-8"))
		time.sleep(3)
		self.irc.send(bytes("JOIN " + channel + "\n", "UTF-8"))
		time.sleep(2)

	def get_response(self) -> str:
		resp = self.irc.recv(2040).decode("UTF-8")

		if resp.find('PING') != -1:                      
			self.irc.send(bytes('PONG ' + resp.split() [1] + '\r\n', "UTF-8")) 
			# print("send : " + 'PONG ' + resp.split() [1] + '\r\n')

		return (resp)

bot = IRC()

bot.connect("localhost", 6667, "arthur", "#test")
while (True):
	bot.send("#test", "Ceci est un test")
	time.sleep(0.1)