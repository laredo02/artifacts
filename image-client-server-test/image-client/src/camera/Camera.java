package camera;

import camera.imageprocessor.ImageProcessor;
import java.awt.Dimension;
import java.awt.Point;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;
import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;
import ui.Window;

public class Camera extends JFrame implements Runnable {

    private final Thread thread;
    private boolean running;
    private final Window win;
    private final VideoCapture videoCapture;
    private Mat tmpMat, blur, hsv, hsvMask, hsl, gray;
    
    private static Scalar hsvMin, hsvMax;
    
    {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        running = false;
        win = new Window();
        videoCapture = new VideoCapture(1);
        tmpMat = new Mat();
        blur = new Mat();
        hsv = new Mat();
        hsvMask = new Mat();
        hsl = new Mat();
        gray = new Mat();
    }
    
    public Camera (Dimension dimension) {
        videoCapture.set(Videoio.CAP_PROP_FRAME_WIDTH, dimension.width);
        videoCapture.set(Videoio.CAP_PROP_FRAME_HEIGHT, dimension.height);
        thread = new Thread(this, "CameraThread");
        initWindow(new Dimension(1280, 720), new Point(100, 200));
    }
    
    public void start () {
        running = true;
        thread.start();
    }
    
    public void stop () {
        running = false;
   }
    
    @Override
    public void run () {
        if (videoCapture.isOpened()) {
            try {
                while (running) {
                    videoCapture.read(tmpMat);
                    if (!tmpMat.empty()) {
                       
                        Core.flip(tmpMat, tmpMat, 1);
                        
                        Imgproc.blur(tmpMat, blur, new Size(6, 6));
                        
                        Imgproc.cvtColor(blur, hsv, Imgproc.COLOR_BGR2HSV);
                        Imgproc.cvtColor(blur, hsl, Imgproc.COLOR_BGR2HLS);
                        Imgproc.cvtColor(blur, gray, Imgproc.COLOR_BGR2GRAY);
                            Imgproc.blur(tmpMat, gray, new Size(20, 20));
                            Imgproc.cvtColor(gray, gray, Imgproc.COLOR_BGR2GRAY);
                            Imgproc.threshold(gray, gray, 130, 255, Imgproc.THRESH_BINARY);
                        
                            win.setImageIcon(new ImageIcon(ImageProcessor.bufferImage(blur)),
                                new ImageIcon(ImageProcessor.bufferImage(hsv)),
                                new ImageIcon(ImageProcessor.bufferImage(hsl)),
                                new ImageIcon(ImageProcessor.bufferImage(gray)));
                    } else {
                        throw new FrameNotCapturedException();
                    }   
                }
            } catch (FrameNotCapturedException e) {
                System.out.println(e);
            }
        } else {
            System.out.println("Your webcam is not suppoterd by OpenCV " + Core.VERSION);
        }
    }
    
    public static void setHsvRange (int ... values) {
        hsvMax = new Scalar(values[0], values[1], values[2]);
        hsvMin = new Scalar(values[3], values[4], values[5]);
    }
    
    public final void initWindow (Dimension  windowSize, Point windowLocation) {
        setSize(windowSize);
        setLocation(windowLocation);
        setTitle("BestCameraApplicationEver");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        add(win);
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | IllegalAccessException | InstantiationException | UnsupportedLookAndFeelException e) {
            e.printStackTrace();
        }
        setVisible(true);
    }
    
}



