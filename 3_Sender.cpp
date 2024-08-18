#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <Receiver IP> <Receiver Port>" << endl;
        return EXIT_FAILURE;
    }

    const char *receiver_ip = argv[1];
    int receiver_port = stoi(argv[2]);

    int sockfd;
    sockaddr_in receiver_addr;
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(receiver_port);
    receiver_addr.sin_addr.s_addr = inet_addr(receiver_ip);

    while (true)
    {
        cout << "Sender: ";
        cin.getline(buffer, BUFFER_SIZE);

        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const sockaddr *)&receiver_addr, sizeof(receiver_addr));

        if (strcmp(buffer, "exit") == 0)
            break;

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, nullptr, nullptr);
        buffer[n] = '\0';
        cout << "Receiver: " << buffer << endl;

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sockfd);
    return 0;
}
