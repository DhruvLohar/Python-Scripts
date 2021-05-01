import socket, json
import os, sys

host = "192.168.56.1"
port = int(sys.argv[1])

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()

def send_img(conn):
	with open("server.py", "r") as img_file:
		print(f"sending file of size {os.path.getsize('linux.jpeg')}")
		img_data = img_file.read()

	conn.send(img_data)
	print("sent!")


while True:
	conn, addr = server.accept()
	print("client connected")
	send_img(conn)
