package main;

import camera.Camera;
import java.awt.Dimension;

public class Main {
    
    public static void main (String [] args) {
    
        Camera camera = new Camera(new Dimension(1280, 720));
        camera.start();
        
    }
    
}
