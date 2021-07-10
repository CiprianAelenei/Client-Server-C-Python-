import socket
import threading

# Date Conectare
host = '37.120.249.45'
port = 7602

# Porinre Server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()

# Lista cu clienti si lista cu nicknames
clients = []
nicknames = []

# Expedierea mesajelor cate toti clientii care sunt conectati
def broadcast(message):
    for client in clients:
        client.send(message)

# Manipulator mesaje de la clienti
def handle(client):
    while True:
        try:
            # Trimiterea de mesaje
            message = client.recv(1024)
            broadcast(message)
        except:
            # Stergere si inchidere client
            index = clients.index(client)
            clients.remove(client)
            client.close()
            nickname = nicknames[index]
            broadcast('{} left!'.format(nickname).encode('ascii'))
            nicknames.remove(nickname)
            break

# Functia de primire si de ascultare a portului
def receive():
    while True:
        # Acceptarea conexiunii
        client, address = server.accept()
        print("Conectat cu {}".format(str(address)))

        # Cererea si pastrarea nickname-ului cerut
        client.send('NICK'.encode('ascii'))
        nickname = client.recv(1024).decode('ascii')
        nicknames.append(nickname)
        clients.append(client)

        # Afisare si transmiterea nickname
        print("Nickname is {}".format(nickname))
        broadcast("{} joined!".format(nickname).encode('ascii'))
        client.send('Conectat la server!'.encode('ascii'))

        # Inceperea manipularii firului de executie al cleintului
        thread = threading.Thread(target=handle, args=(client,))
        thread.start()

receive()
