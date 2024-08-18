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
        cerr << "Usage: " << argv[0] << " <Sender IP> <Sender Port>" << endl;
        return EXIT_FAILURE;
    }

    const char *sender_ip = argv[1];
    int sender_port = stoi(argv[2]);

    int sockfd;
    sockaddr_in sender_addr, my_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(sender_port);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        perror("bind failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    addr_len = sizeof(sender_addr);

    while (true)
    {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (sockaddr *)&sender_addr, &addr_len);
        buffer[n] = '\0';
        cout << "Sender: " << buffer << endl;

        if (strcmp(buffer, "exit") == 0)
            break;

        cout << "Receiver: ";
        cin.getline(buffer, BUFFER_SIZE);

        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const sockaddr *)&sender_addr, addr_len);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sockfd);
    return 0;
}
