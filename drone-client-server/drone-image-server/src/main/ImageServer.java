package main;

import java.awt.image.BufferedImage;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

public class ImageServer implements Runnable {
    
    private final Thread thread;
    private boolean listening;
    private final int PORT;
    
    {
        listening = false;
        thread = new Thread(this, "DroneImageServer");    
    }
    
    public ImageServer(int PORT) {
        this.PORT = PORT;
    }
    
    public void start() {
        listening = true;
        thread.start();
    }
    
    public void stop() {
        listening = false;
    }
    
    @Override
    public void run() {
        System.out.println("Server is listening on port " + PORT);
        while (listening) {
            try (
                ServerSocket serverSocket = new ServerSocket(PORT);
                Socket socket = serverSocket.accept();
                DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
                DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
            ) {
                int n = dataInputStream.readInt();
                if (n == 1) {
                    dataOutputStream.writeInt(640);
                    dataOutputStream.writeInt(420);
                    dataOutputStream.writeInt(BufferedImage.TYPE_3BYTE_BGR);
                }
                while (listening) {
                    dataOutputStream.write(Camera.byteCameraBufferedImage, 0, n);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    
}





