#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const* argv[]) 
{
    // Create server socket
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    if (servSockD < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // String to store data to send to client
    char serMsg[255] = "Message from the server to the client 'Hello Client'";

    // Define server address
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9001);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the specified IP and port
    if (bind(servSockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Bind failed");
        close(servSockD);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(servSockD, 1) < 0) {
        perror("Listen failed");
        close(servSockD);
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    int clientSocket = accept(servSockD, NULL, NULL);
    if (clientSocket < 0) {
        perror("Accept failed");
        close(servSockD);
        exit(EXIT_FAILURE);
    }

    // Send message to client
    send(clientSocket, serMsg, sizeof(serMsg), 0);

    // Close sockets
    close(clientSocket);
    close(servSockD);

    return 0;
}
