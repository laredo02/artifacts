import javafx.animation.AnimationTimer;
import javafx.application.Application;

import javafx.geometry.Point3D;

import javafx.scene.Group;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.PerspectiveCamera;
import javafx.scene.Scene;
import javafx.scene.SceneAntialiasing;
import javafx.scene.shape.Box;
import javafx.scene.SubScene;
import javafx.scene.transform.Rotate;
import javafx.scene.transform.Translate;

import javafx.stage.Stage;

import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import java.io.IOException;
import java.io.DataInputStream;
import java.io.DataOutputStream;

public class Main extends Application {

	private static Box box = new Box(100, 100, 100);
	private static final int WIDTH = 400, HEIGHT = WIDTH;

	@Override
	public void start (Stage stage) {

		stage.setOnCloseRequest((e) -> {
			System.exit(0);
		});
		stage.setResizable(true);
		stage.setTitle("Network Shape Viewer");
		BorderPane rootNode = new BorderPane();
		Scene mainScene = new Scene(rootNode, 400, 400, false, SceneAntialiasing.BALANCED);

		Group mainGroup = new Group();
		SubScene subScene = new SubScene(mainGroup, 400, 400, true, SceneAntialiasing.BALANCED);
		subScene.setFill(Color.rgb(40, 80, 200, 0.5));
PerspectiveCamera perspectiveCamera = new PerspectiveCamera(true);
		perspectiveCamera.setNearClip(1);
		perspectiveCamera.setFarClip(10000);
		perspectiveCamera.setFieldOfView(100);
		subScene.setCamera(perspectiveCamera);

		box.setTranslateZ(150);
		AnimationTimer animationTimer = new AnimationTimer () {
			private Rotate rotate = new Rotate(2, new Point3D(45,45,45));
			private double xpos = 0, xspeed = 1;
			private double zpos = 0, zspeed = 1;
			@Override
			public void handle (long now) {
				double translateX = box.getTranslateX();
				double translateY = box.getTranslateY();
				double translateZ = box.getTranslateZ();
				if (translateX >= WIDTH/2) {
					xspeed = -xspeed;
				} else if (translateX <= 0-WIDTH/2) {
					xspeed = Math.abs(xspeed);
				}
				xpos += xspeed;
				box.setTranslateX(xpos);
				box.getTransforms().addAll(rotate);
				try {
					Thread.currentThread().sleep(10);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		};
		animationTimer.start();
		box.setMaterial(new PhongMaterial(Color.rgb(150, 100, 255)));

		mainGroup.getChildren().addAll(box);
		rootNode.getChildren().addAll();
		rootNode.setCenter(subScene);
		stage.setScene(mainScene);
		stage.show();

	}

	public static void main (String [] args) {
		Server server = new Server(5400);
		server.start();
		launch(args);
	}

}

class Server implements Runnable {

	private final Thread thread;
	private final int PORT;
	private static boolean isRunning;

	{
		thread = new Thread(this, "ServerThread");
	}

	public Server (int PORT) {
		this.PORT = PORT;
	}

	public void start () {
		isRunning = true;
		thread.start();
	}

	@Override
	public void run () {
		while (Server.isRunning) {
			try (
				ServerSocket serverSocket = new ServerSocket(PORT);
				Socket socket = serverSocket.accept();
				DataInputStream dataInputStream = new DataInputStream(socket.getInputStream());
				DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());
			) {
				System.out.println(dataInputStream.readUTF());
			} catch (UnknownHostException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}



