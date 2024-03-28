package droneimageclient;

import java.awt.image.BufferedImage;
import java.net.MalformedURLException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import java.io.IOException;
import java.net.Socket;
import java.net.URL;
import javax.swing.JOptionPane;

public class DroneImageClient {
    
    public static void main (String [] args) {

        Window window = new Window(100, 100, 640, 480);
        String serverInfo = JOptionPane.showInputDialog(window, "Server's ip and port: ");
        
    }
    
}

class Client {

    public void sendLiveFeedRequest (String serverInfo) {
        Socket socket = new Socket();
    }

}

class Window extends JFrame {
    
    public static ImageIcon imageIcon;
    private BufferedImage bufferedImage;
    
    {
        try {
            bufferedImage = ImageIO.read(new URL("https://goes.gsfc.nasa.gov/pub/goes/101124.itcz.jpg"));
        } catch (MalformedURLException e) {
            //e.printStackTrace();
        } catch (IOException e) {
            //e.printStackTrace();
        }
        imageIcon = new ImageIcon(bufferedImage);
    }
    
    public Window (int x, int y, int width, int height) {
        setTitle("Drone camera client");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(x, y, width, height);
        add(new JLabel(imageIcon));
        setVisible(true);
    }
    
    public static void setImage (BufferedImage bufferedImage) {
        imageIcon.setImage(bufferedImage);
    }

}
