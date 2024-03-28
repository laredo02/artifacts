import javafx.scene.transform.Rotate;
import javafx.scene.transform.Translate;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import org.opencv.core.Mat;
import javafx.application.Application;
import javafx.stage.Stage;
import org.opencv.core.Core;
import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;
import javafx.scene.layout.BorderPane;
import javafx.scene.Scene;
import javafx.scene.SceneAntialiasing;
import javafx.scene.PerspectiveCamera;
import javafx.scene.shape.Box;
import javafx.scene.shape.Sphere;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.paint.Color;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.core.MatOfRect;
import org.opencv.imgproc.Imgproc;
import org.opencv.core.Scalar;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import java.awt.BorderLayout;
import java.io.File;
import java.io.IOException;
import com.interactivemesh.jfx.importer.stl.StlMeshImporter;
import javafx.scene.shape.TriangleMesh;
import javafx.scene.shape.MeshView;
import javafx.scene.Group;
import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.Image;
import javafx.util.Duration; 
import javafx.animation.TranslateTransition;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;
 
public class Main extends Application {

	public static Box box = new Box(1280, 720, 720);
	public static Sphere sphere = new Sphere(65);
	public static Box head = new Box(30, 30, 10000);
	public static PerspectiveCamera camera = getCamera();
	public static Box ground = new Box(10000, 10, 10000);

	public static void main(String[] args) {
		ImageServer imageServer = new ImageServer();
		imageServer.start();
		launch(args);
	}
    
	@Override
	public void start (Stage stage) {
		stage.setOnCloseRequest((e) -> {
			System.exit(0);
		});
		stage.setResizable(true);
		stage.setTitle("VariablePerspective");
		stage.setMaximized(true);
		BorderPane rootNode = new BorderPane();
		Scene mainScene = new Scene(rootNode, 1280, 720, true, SceneAntialiasing.BALANCED);
		mainScene.setCamera(camera);

		box.setTranslateX(2000);
		box.setTranslateY(-300);
		box.setTranslateZ(2000);

		sphere.setMaterial(new PhongMaterial(Color.rgb(150, 255, 0)));
		sphere.setTranslateX(100);
		sphere.setTranslateY(-50);
		sphere.setTranslateZ(400);
		
			TranslateTransition translateTransition = new TranslateTransition();
			translateTransition.setDuration(Duration.millis(1000)); 
			translateTransition.setNode(sphere);
			translateTransition.setByX(300); 
			translateTransition.setCycleCount(2000); 
			translateTransition.setAutoReverse(true); 
			translateTransition.play(); 

		head.setMaterial(new PhongMaterial(Color.rgb(100, 250, 20)));
		head.setTranslateX(-200);
		head.setTranslateY(-50);
		head.setTranslateZ(200);

		ground.setMaterial(new PhongMaterial(Color.rgb(100, 100, 100)));
		ground.setTranslateX(0);
		ground.setTranslateY(200);
		ground.setTranslateZ(0);

		Box b = new Box(500, 500, 500);
		b.setMaterial(new PhongMaterial(Color.rgb(100, 100, 100)));
		b.setTranslateX(300);
		b.setTranslateY(200);
		b.setTranslateZ(2000);

		StlMeshImporter stlMeshImporter = new StlMeshImporter();
		stlMeshImporter.read("../models/bike.stl"); 
		TriangleMesh bikeMesh = stlMeshImporter.getImport();
		stlMeshImporter.close();
		MeshView bike = new MeshView(bikeMesh);
		bike.setMaterial(new PhongMaterial(Color.rgb(100, 100, 200)));
		bike.setScaleX(10);
		bike.setScaleY(10);
		bike.setScaleZ(10);
		bike.setTranslateX(-300);
		bike.setTranslateY(0);
		bike.setTranslateZ(3000);
		bike.getTransforms().addAll(new Rotate(90, Rotate.Z_AXIS));
		bike.setTranslateY(-50);

		StlMeshImporter stlMeshImporter2 = new StlMeshImporter();
		stlMeshImporter2.read("../models/map.stl"); 
		TriangleMesh mapMesh = stlMeshImporter.getImport();
		stlMeshImporter.close();
		MeshView map = new MeshView(mapMesh);
		map.setMaterial(new PhongMaterial(Color.rgb(100, 100, 200)));
		map.setScaleX(1000);
		map.setScaleY(1000);
		map.setScaleZ(1000);
		map.setTranslateX(0);
		map.setTranslateY(0);
		map.setTranslateZ(50000);
		//map.getTransforms().addAll(new Rotate(90, Rotate.Z_AXIS));
		map.setTranslateY(0);

		rootNode.getChildren().addAll(box, bike, ground, b, sphere, head, map);
		stage.setScene(mainScene);
		stage.show();
	}

	public static PerspectiveCamera getCamera () {
		PerspectiveCamera perspectiveCamera = new PerspectiveCamera(true);
		perspectiveCamera.setNearClip(1);
 		perspectiveCamera.setFarClip(10000);
 		perspectiveCamera.setFieldOfView(100);
		return perspectiveCamera;
	}

}

class ImageServer implements Runnable {

	private Thread thread;
	private boolean running;
	public static BufferedImage bufferedImage;
    
    static {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }
    
    {
        thread = new Thread(this, "ImageServerThread");
        running = false;
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
		Window win = new Window();
		Mat mat = new Mat();
		VideoCapture videoCapture = new VideoCapture(0);
		videoCapture.set(Videoio.CAP_PROP_FRAME_WIDTH, 1920);
		videoCapture.set(Videoio.CAP_PROP_FRAME_HEIGHT, 1080);
		if (videoCapture.isOpened()) {
			while (running) {
				videoCapture.read(mat);
				if (!mat.empty()) {
					//Imgproc.blur(mat, mat, new Size(20, 20));
					//Imgproc.cvtColor(mat, mat, Imgproc.COLOR_BGR2GRAY);
					//Imgproc.threshold(mat, mat, 150, 255, Imgproc.THRESH_BINARY);
					MatOfRect matOfRect = new MatOfRect();
					CascadeClassifier cascadeClassifier = new CascadeClassifier("/usr/java/opencv-4.1.1/data/haarcascades/haarcascade_frontalface_default.xml");
					cascadeClassifier.detectMultiScale(mat, matOfRect);
					for (Rect rect: matOfRect.toArray()) {
						Imgproc.rectangle(mat,
							new Point(rect.x, rect.y),
							new Point(rect.x + rect.width, rect.y + rect.height),
							new Scalar(255, 0, 0));
						Main.camera.setTranslateX(-(matOfRect.toArray()[0].x - 1280/2));
						Main.camera.setTranslateY(matOfRect.toArray()[0].y - 720/2);
					}
					bufferedImage = bufferImage(mat);
					win.setImage(bufferedImage);
					PhongMaterial material = new PhongMaterial();
					material.setBumpMap(SwingFXUtils.toFXImage(bufferedImage, null));
					material.setDiffuseMap(SwingFXUtils.toFXImage(bufferedImage, null));
					material.setSpecularMap(SwingFXUtils.toFXImage(bufferedImage, null));
					
					Main.box.setMaterial(material);
                		} else {
					System.err.println("IMAGE COULD NOT BE CAPTURED");
				}
			}
		} else {
			System.err.println("YOUR CAMERA IS NOT SUPPORTED BY " + Core.VERSION);
		}
	}
    
    public static BufferedImage bufferImage (Mat mat) {
        int type = BufferedImage.TYPE_BYTE_GRAY;
        if (mat.channels() > 1) {
            type = BufferedImage.TYPE_3BYTE_BGR;
        }
        byte buffer [] = new byte[mat.channels()*mat.cols()*mat.rows()];
        mat.get(0, 0, buffer);
        bufferedImage = new BufferedImage(mat.cols(), mat.rows(), type);
        final byte [] targetPixels = ((DataBufferByte) bufferedImage.getRaster().getDataBuffer()).getData();
        System.arraycopy(buffer, 0, targetPixels, 0, buffer.length);
        return bufferedImage;
    }
    
}

class Window extends JFrame {

	private JLabel label;

	{
		label = new JLabel();
	}

	public Window () {
		setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
		setLocationRelativeTo(null);
		setSize(1280, 720);
		add(label, BorderLayout.CENTER);
		setVisible(true);
	}

	public void setImage (BufferedImage bufferedImage) {
		label.setIcon(new ImageIcon(bufferedImage));
	}

}











