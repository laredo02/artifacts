
import java.io.DataInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {

	public static void main (String [] args) {
		System.out.println("Server:");
		Server server = new Server(9090);
		server.start();
	}

}

class Server implements Runnable {

	private Thread thread;
	private int port;

	public Server (int port) {
		thread = new Thread(this, "ServerThread");
		this.port = port;
	}

	public void start () {
		thread.start();
	}

	public void run () {	
		while (true) {
			try (
				ServerSocket serverSocket = new ServerSocket(port);
			) {
				Socket socket = serverSocket.accept();
				DataInputStream dataInputStream =
						new DataInputStream(socket.getInputStream());
				System.out.println(dataInputStream.readUTF());
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}








