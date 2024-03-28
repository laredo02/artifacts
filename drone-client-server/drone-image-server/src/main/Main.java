package main;

public class Main {

    public static void main(String[] args) {
        Camera camera = new Camera(1280, 720);
        camera.start();
        ImageServer imageServer = new ImageServer(9090);
        imageServer.start();
    }
    
}
