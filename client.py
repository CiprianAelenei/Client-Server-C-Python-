import socket
import threading

# Setare Nickname
nickname = input("Introduceti nickname: ")

# Conectarea la Server
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('37.120.249.45',7602))

# Ascultare Server si experdiere nickname
def receive():
    while True:
        try:
            # Receptionare mesaj de la server
            # Daca 'NICK' expediaza Nickname
            message = client.recv(1024).decode('ascii')
            if message == 'NICK':
                client.send(nickname.encode('ascii'))
            else:
                print(message)
        except:
            # Inchide conexiunea daca este eroare
            print("A aparut o eroare!")
            client.close()
            break

# Expediere mesaj catre server
def write():
    while True:
        message = '{}: {}'.format(nickname, input(''))
        client.send(message.encode('ascii'))

# Deschidere firuri de executie pentru ascultare si executare
receive_thread = threading.Thread(target=receive)
receive_thread.start()

write_thread = threading.Thread(target=write)
write_thread.start()

