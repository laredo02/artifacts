package ftpserver;

import java.io.IOException;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.BufferedInputStream;
import java.io.DataOutputStream;
import java.io.BufferedOutputStream;

import java.net.ServerSocket;
import java.net.Socket;
import java.net.BindException;

import java.util.ArrayList;

public class FTPServer {

    public static void main(String[] args) {
        MyFileReader myFileReader = new MyFileReader();
        myFileReader.readFile(new File("/home/miguel/Documents/HolaMundo")); 
        myFileReader.readFile(new File(args[0]));
        
        MyServer myServer = new MyServer();
        myServer.start();
        
    }
    
}

class MyServer implements Runnable {

    private boolean repeat = true;
    
    public void MyServer () {
    
    }
    
    @Override
    public void run () {
        while (repeat) {
            try (ServerSocket serverSocket = new ServerSocket(9999)) {
                Socket socket = serverSocket.accept();
                DataInputStream dataInputStream = new DataInputStream(
                    socket.getInputStream());
                BufferedInputStream bufferedInputStream = new BufferedInputStream(
                    dataInputStream);
                DataOutputStream dataOutputStream = new DataOutputStream(
                    socket.getOutputStream());
                BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(
                    dataOutputStream);
                bufferedOutputStream.write(new byte [] {100, 100, 100, 78});
                
            } catch (BindException e) {
            } catch (IOException e) {
            }
        } 
    }
    
    public void start () {
        
    }
    
    public void stop () {
        repeat = false;
        try {
            Thread.currentThread().join();
        } catch (InterruptedException e) {
            System.out.println("Hola Mundo");
        }
    }

}

class MyFileReader {

    private final ArrayList<String> fileArrayByLines; 
    private final String line = "";
    private File file;

    MyFileReader() {
        this.fileArrayByLines = new ArrayList<>();
    }
    
    public String readFile (File file) {
        try {
            if (file.exists()) {
                FileReader fileReader = new FileReader(file);
                BufferedReader bufferedReader = new BufferedReader(fileReader);
                int n = bufferedReader.read();
                while (n != -1) { 
                    if (n != (int) '\n') {
                        fileArrayByLines.add(Character.toString((char) n));
                        line.concat(Character.toString((char) n));
                        System.out.println(line);
                        
                    }
                    n = bufferedReader.read();
                }
            } else {
                System.out.println("File " + file.getCanonicalPath() + " does "
                        + "not exisist.");
            }
        } catch (IOException e) {
            System.out.println(e.getCause());
        }
        System.out.println(fileArrayByLines);
        return "Hola Mundo";
    }
    
}



















