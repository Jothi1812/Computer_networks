package bitstuffing;
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class BitStuffingClient {
    public static void main(String[] args) throws IOException {
        // Open a socket for connection
        Socket socket = new Socket("localhost", 6789);

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        // Scanner class object to take input
        Scanner sc = new Scanner(System.in);

        // Take input of unstuffed data from user
        System.out.println("Enter data (in bits): ");
        String data = sc.nextLine();

        int cnt = 0;
        StringBuilder stuffedData = new StringBuilder();

        for (int i = 0; i < data.length(); i++) {
            char ch = data.charAt(i);
            stuffedData.append(ch);
            if (ch == '1') {
                cnt++;
                if (cnt == 5) {
                    // Stuff a '0' after five consecutive '1's
                    stuffedData.append('0');
                    cnt = 0;
                }
            } else {
                cnt = 0;
            }
        }

        System.out.println("Data stuffed in client: " + stuffedData.toString());
        System.out.println("Sending to server for unstuffing");

        // Send stuffed data to the server
        dos.writeUTF(stuffedData.toString());

        // Close the connections
        dos.close();
        dis.close();
        socket.close();
    }
}
