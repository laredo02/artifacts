package main;

import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.ArrayList;
import org.jsoup.nodes.Document;

public class LocalWebServer {

	private HttpServer server;
	private static String indexFileName;
	private int port;

	public LocalWebServer (int port, String indexFileName) {
		this.port = port;
		LocalWebServer.indexFileName = indexFileName;
		try {
			server = HttpServer.create(new InetSocketAddress(port), 0);
		} catch (IOException e) {
			e.printStackTrace();
		}
		HttpContext context = server.createContext("/");
		context.setHandler(LocalWebServer::handleRequest);
	}
	
	public void start () {
		server.start();
	}

	public static void handleRequest (HttpExchange exchange) throws IOException {
		exchange.sendResponseHeaders(200, getResponseBytes().length);
		OutputStream outputStream = exchange.getResponseBody();
		outputStream.write(getResponseBytes());
		outputStream.close();
	}

	private static byte[] getResponseBytes () {
		Document doc = URLManager.getDomFromFile(indexFileName);
		return doc.toString().getBytes();
	}

} 

