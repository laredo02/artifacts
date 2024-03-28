package org.imageserver;

import org.camera.ServerCamera;
import java.awt.Dimension;
import org.server.Server;

public class ImageServer {
    
    public static void main(String[] args) throws InterruptedException {
        
        ServerCamera camera = new ServerCamera(new Dimension(640, 480));
        camera.start();
//        Server server = Server.getInstance(9090);
//        server.start();
    
    }
    
}
