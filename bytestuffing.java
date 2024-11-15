
package byte_stuffing; 
import java.io.*; 
import java.net.*; 

public class Byte_Stuffing { 
	public static void main(String[] args) throws IOException 
	{ 
		
		ServerSocket servsock = new ServerSocket(45678); 

		
		Socket socket = servsock.accept(); 

		
		DataInputStream dis = new DataInputStream(socket.getInputStream()); 
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream()); 

		while (true) { 
			String out = new String(); 
			
			String res = dis.readUTF(); 
			System.out.println("Message Received...Successfully!!!"); 
			System.out.println("The Stuffed Message is : " + res); 

			for (int i = 1; i < res.length() - 1; i++) { 

			
				if (res.charAt(i) == 'D' || res.charAt(i) == 'F') 
					out = out + res.charAt(i); 

				
				else if (res.charAt(i) == 'E' && res.charAt(i + 1) == 'E') { 
					out = out + 'E'; 
					i++; 
				} 
			} 
			System.out.println("The Destuffed Message is : " + out); 
			dos.writeUTF("success"); 
			String ch = dis.readUTF(); 
			if (ch.equals("bye")) { 
				System.out.println("Messaging is over.....EXITING"); 
				break; 
			} 
		} 

		
		socket.close(); 
		dis.close(); 
		dos.close(); 
	} 
} 
