package org.camera;

import java.awt.FlowLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class ImageDisplay extends JFrame {
    
    public ImageDisplay () {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocation(100, 100);
        setTitle("asd");
        ImageIcon imageIcon = new ImageIcon("image.png");
        JLabel label = new JLabel(imageIcon);
        getContentPane().add(label);
        setVisible(true);
    }
    
}
