import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;

public class Main {

	public static void main (String [] args) {
		boolean repeat = true;
		Client client = new Client();
		String string;
		while (true) {
			string = new ConsoleReader().readLine();
			if (!string.equals("exit")) {
				if (string.equals("")) {
					continue;
				}
				client.writeString(string);
			} else {
				System.exit(0);
			}
		}
	}

}

class ConsoleReader {

	private BufferedReader bufferedReader;

	public ConsoleReader () {
		bufferedReader = new BufferedReader(
				new InputStreamReader(System.in));
	}
	
	public String readLine () {
		try {
			System.out.print(":");
			return bufferedReader.readLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}

}

class Client {

	private String ip;
	private int port;

	public Client () {
		this("localhost", 9090);
	}

	public Client (String ip, int port) {
		this.ip = ip;
		this.port = port;
	}

	public void writeString (String string) {
		String clientString = new String("Client: ").concat(string);
		try (
			Socket socket = new Socket(ip, port);
			DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
		) {
			dataOutputStream.writeUTF(clientString);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public String getIP () {
		return ip;
	}

	public int getPORT () {
		return port;
	}

}
