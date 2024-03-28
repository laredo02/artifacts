package ftpclient;

import java.net.Socket;
import java.io.IOException;
import java.net.UnknownHostException;
import java.io.DataOutputStream;
import java.io.BufferedOutputStream;

public class FTPClient {

    public static void main(String[] args) {
        
        MyClient myClient = new MyClient("localhost", 9999);
        myClient.writeToServer("Hola Mundo");
        
    }
    
}

class MyClient {
    
    private final String ip;
    private final int port;
    
    public MyClient (String ip, int port) {
    
        this.ip = ip;
        this.port = port;
        
    }
    
    public void writeToServer (String s) {
    
        try (Socket socket = new Socket(ip, port)) {
        
            DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
            BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(dataOutputStream);
            bufferedOutputStream.write(new byte [] {(byte)100, (byte)100, (byte)140, (byte)140});
        
        } catch (UnknownHostException e) {
        
            System.out.println(e);
            
        } catch (IOException e) {
        
            System.out.println(e);
        
        }
        
    }
    
}