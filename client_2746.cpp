#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        scerr << "Invalid address/ Address not supported" << endl;
        return -1;
    }
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection Failed" << endl;
        return -1;
    }
    vector<int> numbers = {5, 3, 8, 6, 2, 7, 4, 1};

    int arr_size = numbers.size();
    send(sock, &arr_size, sizeof(arr_size), 0);
    send(sock, numbers.data(), arr_size * sizeof(int), 0);

    cout << "Array sent to server." << endl;

    vector<int> sorted_numbers(arr_size);
    read(sock, sorted_numbers.data(), arr_size * sizeof(int));

    cout << "Sorted array received from server: ";
    for (int num : sorted_numbers) cout << num << " ";
    cout << endl;

    close(sock);
    return 0;
}