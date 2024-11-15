#include <bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
#define ll long long int

using namespace std;

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cout << "Failed to initialize Winsock" << endl;
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Socket creation error" << endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Use inet_addr instead of InetPton for Windows compatibility
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        cout << "Invalid address/ Address not supported" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection Failed" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    srand(static_cast<unsigned>(time(NULL)));

    ll tf, N;
    cout << "Enter total number of frames: ";
    cin >> tf;
    cout << "Enter window size: ";
    cin >> N;

    string msg = to_string(tf) + " " + to_string(N);
    send(sock, msg.c_str(), msg.size(), 0);

    // Buffer to keep track of which frames have been acknowledged
    vector<bool> ack_received(tf, false);
    int i = 0; // Initial frame to send

    while (i < tf) {
        // Send frames in the current window
        for (int k = i; k < i + N && k < tf; k++) {
            string msg = "Sending Frame " + to_string(k + 1);
            send(sock, msg.c_str(), msg.size(), 0);
            cout << "Sent Frame " << k + 1 << endl;
            Sleep(500);  // slight delay
        }

        // Check for acknowledgments for the sent frames
        for (int k = i; k < i + N && k < tf; k++) {
            memset(buffer, 0, sizeof(buffer));
            int valread = recv(sock, buffer, 1024, 0);

            if (valread > 0) {
                if (strcmp(buffer, ("ACK" + to_string(k + 1)).c_str()) == 0) {
                    ack_received[k] = true;
                    cout << "Acknowledgment received for Frame " << k + 1 << endl;
                }
            }
        }

        // Move the window forward by the number of acknowledged frames
        while (i < tf && ack_received[i]) {
            i++;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
