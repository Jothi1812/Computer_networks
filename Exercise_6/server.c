#include<stdio.h>
#include<winsock2.h>    // For Winsock API
#include<ws2tcpip.h>    // For inet_pton and other functions

// Link with ws2_32.lib for Windows
#pragma comment(lib,"ws2_32.lib")

void func(SOCKET confd);

int main() {
    WSADATA wsa;
    SOCKET sockfd, confd;
    struct sockaddr_in servaddr, cliaddr;
    int len;

   
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Winsock initialization failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock initialized.\n");

   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("\nSocket is created\n");

   
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

   
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("\nBind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("\nBind successfully\n");

    // Listen for incoming connections
    if (listen(sockfd, 5) == SOCKET_ERROR) {
        printf("\nListen failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("\nListen successfully\n");

    // Accept an incoming connection
    len = sizeof(cliaddr);
    confd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (confd == INVALID_SOCKET) {
        printf("\nAccept failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("\nServer accepted successfully\n");

   
    func(confd);

    // Cleanup
    closesocket(confd);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

void func(SOCKET confd) {
    int n, fib[100];

    // Receive value for number of terms (N)
    printf("\nThe value for number of terms N:\n");
    recv(confd, (char*)&n, sizeof(n), 0);
    printf("%d", n);

    // Calculate Fibonacci series
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    printf("\nThe Fibonacci series is:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }

   
    send(confd, (char*)fib, n * sizeof(int), 0);
}
