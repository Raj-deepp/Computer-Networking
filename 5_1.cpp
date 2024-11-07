//Design a connection oriented concurrent chat server using fork ()

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <csignal>
using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message from client
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            cout << "Client disconnected." << endl;
            break;
        }

        // Display received message
        cout << "Client: " << buffer << endl;

        // Check for "logout" message
        if (strncmp(buffer, "logout", 6) == 0) {
            cout << "Client requested to logout." << endl;
            break;
        }

        // Echo back the message to the client
        send(clientSocket, buffer, strlen(buffer), 0);
    }
    close(clientSocket);
    exit(0); // Exit child process
}

void signalHandler(int sig) {
    // Wait for all dead processes
    while (waitpid(-1, nullptr, WNOHANG) > 0);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create server socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    cout << "Server is listening on port " << PORT << "..." << endl;

    // Set up signal handling to clean up child processes
    signal(SIGCHLD, signalHandler);

    while (true) {
        // Accept an incoming client connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        cout << "New connection from " << inet_ntoa(clientAddr.sin_addr) <<":"<< ntohs(clientAddr.sin_port) << endl;

        // Create a new process for each client
        if (fork() == 0) {  // Child process
            close(serverSocket); // Child doesn't need the listener
            handleClient(clientSocket); // Handle client communication
            exit(0);
        } else {
            close(clientSocket); // Parent doesn't need this client socket
        }
    }

    close(serverSocket);
    return 0;
}