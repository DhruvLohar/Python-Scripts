import socket

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

socket.bind(("127.0.0.1", 8000))

socket.listen(5)

while True:
    conn, addr = socket.accept()
    
    conn.send(b"aadish madarchod")
    
    conn.close()
    break

socket.close()