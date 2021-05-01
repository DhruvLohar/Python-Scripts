import json, sys
import socket
import threading

class Server:
    def __init__(self, backlog=10, buffer_size=4096):
        self.host = str(sys.argv[1])
        self.port = int(sys.argv[2])
        self.backlog = backlog
        self.buff_size = buffer_size
        self.user_data = {}
        try:
            self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server.bind((self.host, self.port))
        except socket.error as err:
            self.display_alert(err, 'ERROR')

    @staticmethod
    def display_alert(msg, type):
        print(f'[CHAT-X | {type}] --> {msg}')

    def init_server(self):
        self.server.listen(self.backlog)
        self.display_alert('Listening For Connections...', 'SOCKET')
        while True:
            conn, addr = self.server.accept()
            self.display_alert(f'Connection request from {addr[0]}:{addr[1]}', 'SOCKET')
            user_thread = threading.Thread(target=self.handle_client, args=(conn,), daemon=True)
            user_thread.start()

    def handle_client(self, conn):
        username = conn.recv(self.buff_size).decode()
        self.user_data[username] = conn
        self.display_alert(f'User Connected : {username}', 'SOCKET')
        self.init_messenger(conn)

    def broadcast(self, data, type):
        for user, conn in self.user_data.items():
            if type[0] == "json":
                if user != data['from_user']:
                    conn.send(json.dumps(data).encode())
            else:
                if conn != type[1]:
                    conn.sendall(data)

    def init_messenger(self, conn):
        while True:
            raw_data = conn.recv(self.buff_size)
            try: 
                data = json.loads(raw_data.decode())
                if data['type'] == 'text' or data['type'] == '_media_request':
                    self.broadcast(data, ['json'])
            except (KeyError, UnicodeDecodeError):
                self.broadcast(raw_data, ['base64', conn])
                

server = Server()
server.init_server()
