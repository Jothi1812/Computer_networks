package bytestuffing;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ByteStuffingClient {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 6789);

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        Scanner sc = new Scanner(System.in);

        // Input data from the user
        System.out.println("Enter data to be stuffed:");
        String data = sc.nextLine();

        // Perform byte stuffing
        String stuffedData = data.replace("ESC", "ESCESC").replace("FLAG", "ESCFLAG");
        System.out.println("Stuffed data: " + stuffedData);

        // Send stuffed data to the server
        dos.writeUTF(stuffedData);

        // Receive unstuffed data from the server
        String unstuffedData = dis.readUTF();
        System.out.println("Received unstuffed data from server: " + unstuffedData);

        dis.close();
        dos.close();
        socket.close();
    }
}