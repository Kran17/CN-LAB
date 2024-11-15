package byte_stuffing;

import java.io.*;
import java.net.*;

public class Byte_Stuffing_Server {
    public static void main(String[] args) throws IOException {
        int port = 45678;
        ServerSocket ss = new ServerSocket(port);

        System.out.println("Server started...waiting for client.");
        Socket s = ss.accept();
        System.out.println("Client connected.");

        // Declaring I/O Streams
        DataInputStream dis = new DataInputStream(s.getInputStream());
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());

        while (true) {
            String receivedData = dis.readUTF();
            System.out.println("Received Stuffed Message: " + receivedData);

            // Destuffing logic
            String destuffedData = new String();
            for (int i = 1; i < receivedData.length() - 1; i++) {  // skip first and last 'F'
                if (receivedData.charAt(i) == 'E' && (receivedData.charAt(i + 1) == 'F' || receivedData.charAt(i + 1) == 'E')) {
                    // Skip the 'E' and take the next character
                    continue;
                }
                destuffedData += receivedData.charAt(i);
            }

            System.out.println("Destuffed Message: " + destuffedData);

            // Acknowledge reception to client
            dos.writeUTF("success");

            if (destuffedData.equals("bye")) {
                System.out.println("Ending session.");
                break;
            }
        }
        ss.close();
        s.close();
        dis.close();
        dos.close();
    }
}
