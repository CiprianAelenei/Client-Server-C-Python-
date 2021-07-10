#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];

    // Stergere buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Creare socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("Nu s-a putut crea socketul\n");
        return -1;
    }

    printf("Socket creat cu succes\n");

    // Setare port si IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7602);
    server_addr.sin_addr.s_addr = inet_addr("37.120.249.45");

    // Interogare server pentru conexiune:
    if (connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Nu se poate conecta\n");
        return -1;
    }
    printf("S-a realizat conexiunea cu serverul\n");

    // Input de la utilizator:
    printf("Introduceti mesajul: ");
    gets(client_message);

    // Expediere mesaj catre server:
    if (send(socket_desc, client_message, strlen(client_message), 0) < 0) {
        printf("Nu se poate expedia mesajul\n");
        return -1;
    }

    // Receptionare raspuns server:
    if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0) {
        printf("Eroare la receptionarea mesajului de la server\n");
        return -1;
    }

    printf("Raspuns server: %s\n", server_message);

    // Inchidere socket:
    close(socket_desc);

    return 0;
}
