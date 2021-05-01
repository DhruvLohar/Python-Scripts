import os, sys, time
import socket
import threading
import json

class Client:
	def __init__(self, host="localhost", port=int(sys.argv[1]), buffer_size=40960000):
		self.host = host
		self.port = port
		self.buff_size = buffer_size
		self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.server.connect((self.host, self.port))
		self.display_alert('Connected to Server', 'SOCKET')

	@staticmethod
	def display_alert(msg, type):
		print(f'[CHAT-X | {type}] --> {msg}')

	def recv_message(self):
		while True:
			raw_data = self.server.recv(self.buff_size)
			try: 
				data = json.loads(raw_data)
				if data['type'] == 'text':
					print(f'{data["from_user"]} --> {data["message"]}')
				elif data['type'] == '_media_request':
					print(f"Receving {data['name']} from {data['from_user']} ...")
					file_name = data['file_name']
			except (KeyError, UnicodeDecodeError):
				with open(f"received/{data['from_user']}.jpeg", "wb+") as img:
					img.write(raw_data)
					print("File Recevied!")

	def send_media(self, path, username):
		file_size = os.path.getsize(path)
		file_name = os.path.basename(path)
		data = {'type': '_media_request', 'name': file_name, 'size': file_size, 'from_user': username}
		self.server.send(json.dumps(data).encode())
		with open(path, 'rb') as file_data:
			print('Sending File...')
			data = file_data.read()
			self.server.sendall(data)
		print('File Sent Successfully!')

	def init_client(self):
		username = str(input('Enter your name --> '))
		self.server.send(username.encode())
		recv_thread = threading.Thread(target=self.recv_message, args=(), daemon=True)
		recv_thread.start()
		while True:
			message = str(input(''))
			if message[:2] != '#!':
				data = {
					'type': 'text',
					'from_user': username,
					'message': message
				}
				self.server.send(json.dumps(data).encode())
			elif message == '#!media':
				path = str(input('Enter file path --> '))
				self.send_media(path, username)

client = Client()
client.init_client()
