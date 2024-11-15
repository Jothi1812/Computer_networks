#include<stdio.h>
#include<winsock2.h>  // For Winsock functions

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

void calculate_factorial(SOCKET sockfd, struct sockaddr_in *client, int len);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr, client;
    int len, recv_num;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket created successfully.\n");

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);  // Using port 8080 for example
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("Bind successful, waiting for client...\n");

    // Receive data from client and calculate factorial
    len = sizeof(client);
    calculate_factorial(sockfd, &client, len);

    // Cleanup
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void calculate_factorial(SOCKET sockfd, struct sockaddr_in *client, int len) {
    int num, factorial = 1;

    // Receive number from client
    recvfrom(sockfd, (char*)&num, sizeof(num), 0, (struct sockaddr*)client, &len);
    printf("Received number from client: %d\n", num);

    // Calculate factorial using a loop
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }

    // Send the result back to the client
    sendto(sockfd, (char*)&factorial, sizeof(factorial), 0, (struct sockaddr*)client, len);
    printf("Factorial sent to client: %d\n", factorial);
}
