// fibonacci_client_windows.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Include Winsock library
#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    int number, result;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 1;
    }

    // Prepare the server sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_port = htons(8070);
    server.sin_addr.s_addr = inet_addr("152.58.252.139"); // Public IP of the server
    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed with error code : %d", WSAGetLastError());
        return 1;
    }

    // Get user input
    printf("Enter a number for Fibonacci calculation: ");
    scanf("%d", &number);

    // Send the number to the server
    send(sock, (char*)&number, sizeof(number), 0);

    // Receive the Fibonacci result from the server
    recv(sock, (char*)&result, sizeof(result), 0);
    printf("Fibonacci result received: %d\n", result);

    // Close the socket
    closesocket(sock);

    // Cleanup Winsock
    WSACleanup();

    return 0;
}