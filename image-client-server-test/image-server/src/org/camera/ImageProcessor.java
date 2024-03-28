package org.camera;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;

public class ImageProcessor {
    public static BufferedImage bufferImage (Mat mat) {
        int type = BufferedImage.TYPE_BYTE_GRAY;
        if ( mat.channels() > 1 ) {
            type = BufferedImage.TYPE_3BYTE_BGR;
        }
        byte [] buffer = new byte[mat.channels()*mat.cols()*mat.rows()];
        mat.get(0,0,buffer);
        BufferedImage image = new BufferedImage(mat.cols(),mat.rows(), type);
        final byte[] targetPixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
        System.arraycopy(buffer, 0, targetPixels, 0, buffer.length);
        Imgproc.blur(mat, mat, new Size(30, 30));
        return image;
    }
}
