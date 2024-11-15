package bytestuffing;

import java.io.*;
import java.net.*;

public class ByteStuffingServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(6789);
        System.out.println("Server started and waiting for connection...");

        Socket socket = serverSocket.accept();
        System.out.println("Client connected.");

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        // Read stuffed data from client
        String stuffedData = dis.readUTF();
        System.out.println("Received stuffed data from client: " + stuffedData);

        // Unstuff the data by removing the stuffed ESC bytes
        String unstuffedData = stuffedData.replace("ESCESC", "ESC").replace("ESCFLAG", "FLAG");
        System.out.println("Unstuffed data: " + unstuffedData);

        // Send unstuffed data back to client
        dos.writeUTF(unstuffedData);

        dis.close();
        dos.close();
        socket.close();
        serverSocket.close();
    }
}
