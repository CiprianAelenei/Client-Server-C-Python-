#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];

    // Stergere buffere:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Creare socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("Eroare in timp ce s-a creat socketul\n");
        return -1;
    }
    printf("Socket creat cu succes\n");

    // Setare port si IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7602);
    server_addr.sin_addr.s_addr = inet_addr("37.120.249.45");

    // Bind cu portul si IP-ul setat:
    if (bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Nu se poate face legatura(bind) cu portul\n");
        return -1;
    }
    printf("S-a realizat legatura(bind)\n");

    // Ascultare clienti:
    if (listen(socket_desc, 1) < 0) {
        printf("Eroare la ascultare\n");
        return -1;
    }
    printf("\nAscultare pentru viitoarele conexiuni.....\n");

    // Acceptare conexiuni viitoare:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);

    if (client_sock < 0) {
        printf("Nu se poate accepta\n");
        return -1;
    }
    printf("Client conectat cu IP: %s si port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Receptionare mesaj client:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0) {
        printf("Nu s-a putut receptiona mesajul!\n");
        return -1;
    }
    printf("Mesajul clientului: %s\n", client_message);

    // Respuns catre client:
    strcpy(server_message, "Acesta este mesajul serverului.");

    if (send(client_sock, server_message, strlen(server_message), 0) < 0) {
        printf("Nu s-a trimis\n");
        return -1;
    }

    // Inchide soketul:
    close(client_sock);
    close(socket_desc);

    return 0;
}