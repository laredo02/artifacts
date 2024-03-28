package main;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;

public class Camera implements Runnable {

    public static BufferedImage cameraBufferedImage;
    public static byte [] byteCameraBufferedImage;
    private final int width, height;
    private final Thread thread;
    private boolean running;
    
    static {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }
    
    {
        thread = new Thread(this, "CameraServer");
        running = false;
    }
    
    public Camera (int width, int height) {
        this.width = width;
        this.height = height;
    }
    
    @Override
    public void run () {
        Mat mat = new Mat();
        VideoCapture videoCapture = new VideoCapture(1);
        videoCapture.set(Videoio.CAP_PROP_FRAME_WIDTH, width);
        videoCapture.set(Videoio.CAP_PROP_FRAME_HEIGHT, height);
        if (videoCapture.isOpened()) {
            while (running) {
                videoCapture.read(mat);
                if (!mat.empty()) {
                    cameraBufferedImage = Camera.bufferImage(mat);
                    byteCameraBufferedImage = ((DataBufferByte) cameraBufferedImage.getRaster()
                                                                                   .getDataBuffer())
                                                                                   .getData();
                } else {
                    System.err.println("Image not captured");
                }
            }
        } else {
            System.err.println("Could not open capture, \n"
                    + "camera capture is not supported on this device.");
            System.exit(1);
        }
    }
    
    public void start () {
        running = true;
        thread.start();
    }
    
    public static BufferedImage bufferImage (Mat mat) {
        int type = BufferedImage.TYPE_BYTE_GRAY;
        if (mat.channels() > 1) {
            type = BufferedImage.TYPE_3BYTE_BGR;
        }
        byte buffer [] = new byte[mat.channels()*mat.cols()*mat.rows()];
        mat.get(0, 0, buffer);
        cameraBufferedImage = new BufferedImage(mat.cols(), mat.rows(), type);
        final byte [] targetPixels = ((DataBufferByte) cameraBufferedImage.getRaster().getDataBuffer()).getData();
        System.arraycopy(buffer, 0, targetPixels, 0, buffer.length);
        return cameraBufferedImage;
    }
    
    public static synchronized byte [] getByteBufferedImage () {
        return byteCameraBufferedImage;
    }
    
    public static synchronized BufferedImage getCameraBufferedImage () {
        return cameraBufferedImage;
    }
    
}
