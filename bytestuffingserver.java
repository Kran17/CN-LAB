import java.net.*;
import java.io.*;

public class ByteStuffingServer {
    public static void main(String[] args) throws IOException {
        // Opening the socket for the connection
        ServerSocket servsock = new ServerSocket(45678);
        System.out.println("Server started, waiting for a client to connect...");

        // Block until a client creates a connection with the server
        Socket socket = servsock.accept();
        System.out.println("Client connected.");

        // Declaring Input Streams for taking input
        DataInputStream dis = new DataInputStream(socket.getInputStream());

        // Declaring output streams for output
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        while (true) {
            String out = new String();

            // Reading the data sent by the client
            String res = dis.readUTF();
            System.out.println("Message Successfully Received!!!");
            System.out.println("The Stuffed Message is: " + res);

            // De-stuffing the received message
            for (int i = 1; i < res.length() - 1; i++) {
                // If there is 'E' followed by 'F' in the data or 'F' is the last in the data, de-stuff the former 'E'
                if (res.charAt(i) == 'E' && res.charAt(i + 1) == 'F' || (res.charAt(i) == 'F' && i == res.length() - 2)) {
                    out = out + 'F';
                    i++;
                }
                // If there is an 'E' followed by 'E' in the data then de-stuff the former 'E' from the data
                else if (res.charAt(i) == 'E' && res.charAt(i + 1) == 'E') {
                    out = out + 'E';
                    i++;
                } else {
                    out = out + res.charAt(i);
                }
            }

            System.out.println("Destuffed Message: " + out);

            // Sending acknowledgment back to the client
            dos.writeUTF("success");

            // Reading the next message from the client
            String ch = dis.readUTF();
            if (ch.equals("bye")) {
                System.out.println("EXITING... Messaging is over.");
                break;
            }
        }

        // Closing all the connections
        socket.close();
        dis.close();
        dos.close();
        servsock.close();
    }
}
