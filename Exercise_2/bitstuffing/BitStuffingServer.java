package bitstuffing;

import java.io.*;
import java.net.*;

public class BitStuffingServer {
    public static void main(String[] args) throws IOException {
        // Create a server socket to listen on port 6789
        ServerSocket serverSocket = new ServerSocket(6789);

        // Accept a connection from the client
        Socket socket = serverSocket.accept();
        System.out.println("Client connected!");

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        // Receiving the stuffed data from the client
        String stuffedData = dis.readUTF();
        System.out.println("Stuffed data from client: " + stuffedData);

        // Unstuff the data by removing stuffed '0' bits
        StringBuilder unstuffedData = new StringBuilder();
        int cnt = 0;

        for (int i = 0; i < stuffedData.length(); i++) {
            char ch = stuffedData.charAt(i);
            unstuffedData.append(ch);
            if (ch == '1') {
                cnt++;
                if (cnt == 5) {
                    // Skip the stuffed '0'
                    i++;
                    cnt = 0;
                }
            } else {
                cnt = 0;
            }
        }

        System.out.println("Unstuffed data: " + unstuffedData.toString());

        // Close the connections
        dos.close();
        dis.close();
        socket.close();
        serverSocket.close();
    }
}
