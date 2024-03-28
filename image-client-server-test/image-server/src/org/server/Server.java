package org.server;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.BindException;
import java.net.ServerSocket;
import java.net.Socket;
import org.ocp.OCP;
import org.ocp.action.Action;

public class Server implements Runnable {
    
    private final Thread thread;
    private static boolean IS_RUNNING;
    private static short PORT;
    
    {
        thread = new Thread(this, "ServerThread");
        Server.IS_RUNNING = false;
    }
    
    public static Server getInstance(int PORT) {
        Server.PORT = (short) PORT;
        return ServerHolder.INSTANCE;
    }
    
    public void start () {
        Server.IS_RUNNING = true;
        thread.start();
    }
    
    public void stop () {
        Server.IS_RUNNING = false;
    }
    
    @Override
    public void run () {
        System.out.println("Server started");
        while (Server.IS_RUNNING) {
            try (
                ServerSocket serverSocket = new ServerSocket(PORT);
                Socket socket = serverSocket.accept();        
                ObjectInputStream objIn = new ObjectInputStream(socket.getInputStream());
            ) {
                    OCP ocp = (OCP) objIn.readObject();
                    Action action = ocp.getAction();
                    switch (action) {
                        case GET_IMG:
                            ocp.setObject(new Object());
                            break;
                        case STOP_SERVER:
                            Server.IS_RUNNING = false;
                            break;
                    }
                if (!Server.IS_RUNNING) {
                    break;
                }
            } catch (ClassNotFoundException | IOException e) {
                if (e instanceof BindException) {
                    Server.IS_RUNNING = false;
                    System.out.println("Address alredy in use");
                }
            }
        }
        
    }
    
    private static class ServerHolder {
        private static final Server INSTANCE = new Server();
    }
    
}