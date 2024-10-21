import socket

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

socket.connect(("127.0.0.1", 8000))

data = socket.recv(4096)
print(data)

socket.close()