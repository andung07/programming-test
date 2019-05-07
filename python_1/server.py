import socket

SERVER_IP = "0.0.0.0"
SERVER_PORT = 3111
REDIRECT_IP = "127.0.0.1"
REDIRECT_PORT = 2999
BUFFER_SIZE = 4096

class tcp_server:
    def __init__(self, port):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind(("0.0.0.0", port))
        self.socket.listen(1)

    def start(self):
        while 1:
            print("Waiting for a connection")
            conn, addr = self.socket.accept()
            print("Accepting a connection from ", addr)
            while 1:
                data = conn.recv(BUFFER_SIZE)
                if not data: break

                print("Redirecting data to the designated server ...")
                redirect = tcp_client(REDIRECT_IP, REDIRECT_PORT)
                redirect.send(data)

                print("Getting a reply from the edge server ...")
                redirect_reply = redirect.read()
                if not redirect_reply: break

                print("Replying back to the original client ...")
                conn.send(redirect_reply)

                print("Closing redirect tcp connection ...")
                redirect.close()


class tcp_client:
    def __init__(self, ip, port):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((ip, port))

    def send(self, message):
        self.socket.send(message)

    def read(self):
        data = self.socket.recv(BUFFER_SIZE)
        return data

    def close(self):
        self.socket.close()


if __name__ == "__main__":
    print("Starting TCP server ...")
    server = tcp_server(SERVER_PORT)
    server.start()
