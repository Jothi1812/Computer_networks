#include<stdio.h>
#include<winsock2.h>  // For Winsock functions

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

void main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr;
    int num, factorial, len;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return;
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }
    printf("Socket created successfully.\n");

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8060);  // Using port 8080 for example
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Input number to send to server
    printf("Enter a number to calculate factorial: ");
    scanf("%d", &num);

    // Send number to server
    sendto(sockfd, (char*)&num, sizeof(num), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Receive the factorial from the server
    len = sizeof(servaddr);
    recvfrom(sockfd, (char*)&factorial, sizeof(factorial), 0, (struct sockaddr*)&servaddr, &len);

    // Print the received factorial
    printf("Factorial of %d is: %d\n", num, factorial);

    // Cleanup
    closesocket(sockfd);
    WSACleanup();
}
