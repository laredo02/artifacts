import java.io.DataOutputStream;

import java.net.ServerSocket;
import java.net.Socket;

public class Server {

	private static final int serverPort = 5400;

	public static void main (String [] args) {

		try (ServerSocket serverSocket = new ServerSocket(serverPort)) {

			Socket socket = serverSocket.accept();
			DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
			System.out.println(dataInputStream.readUTF());

		} catch (Exception exception) {

			System.out.println(exception);

		}

	}

}