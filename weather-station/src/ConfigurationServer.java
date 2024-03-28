package main;

import java.io.IOException;
import java.io.BufferedInputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class ConfigurationServer implements Runnable {

	private Thread thread;
	private final int port;

	public ConfigurationServer (int port) {
		thread = new Thread(this, "ServerSocketThread");
		this.port = port;
	}

	public void start () {
		thread.start();
	}

	@Override
	public void run () {
		while (true) {
			try (
				ServerSocket serverSocket = new ServerSocket(port);
				Socket socket = serverSocket.accept();
				BufferedInputStream bufferedInputStream = new BufferedInputStream(socket.getInputStream());
			) {
				int n;
				while ((n = bufferedInputStream.read()) != -1) {

				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}
