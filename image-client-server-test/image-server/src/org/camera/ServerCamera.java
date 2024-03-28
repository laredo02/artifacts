package org.camera;

import java.awt.Dimension;
import java.awt.image.BufferedImage;
import javax.swing.ImageIcon;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;

public class ServerCamera implements Runnable {
    
    private final Thread thread;
    public static boolean IS_RUNNING;
    private VideoCapture capture;
    private ImageIcon imageIcon;
    ImageDisplay imgDis = new ImageDisplay();
    
    {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        thread = new Thread(this, "CameraThread");
        ServerCamera.IS_RUNNING = false;
        capture = new VideoCapture(0);
    }
    
    public ServerCamera (Dimension dimension) {
        capture.set(Videoio.CAP_PROP_FRAME_WIDTH, dimension.width);
        capture.set(Videoio.CAP_PROP_FRAME_HEIGHT, dimension.height);
        
    }

    public void start () {  
        ServerCamera.IS_RUNNING = true;
        thread.start();
    }
    
    public void stop () {
        ServerCamera.IS_RUNNING = false;
    }
    
    @Override
    public void run () {
        Mat mat = new Mat();
        if (capture.isOpened()) {
            while (true) {
                capture.read(mat);
                if (!mat.empty()) {
                    BufferedImage image = ImageProcessor.bufferImage(mat);
                    imageIcon = new ImageIcon(image);
                }
            }
        }
    }

}