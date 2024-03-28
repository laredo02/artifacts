package imageclienttester;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import org.ocp.OCP;
import org.ocp.action.Action;

public class ImageClientTester {

    public static void main(String[] args) {
        System.out.println("Tester");
        try (
            Socket socket = new Socket("localhost", 9090);
            ObjectOutputStream objOut = new ObjectOutputStream(socket.getOutputStream());
	) {
            objOut.writeObject(new OCP(Action.GET_IMG));
	} catch (UnknownHostException e) {
            e.printStackTrace();
	} catch (IOException e) {
            e.printStackTrace();
	}
    }
    
}
