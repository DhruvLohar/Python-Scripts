import socket, sys

host = "192.168.56.1"
port = int(sys.argv[1])

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect((host, port))

img = open("client.py", "w+")
data = server.recv(40960000).decode()
img.write(data)
print("done")

img.close()
server.close()
