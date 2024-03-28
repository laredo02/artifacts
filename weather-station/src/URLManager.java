package main;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

public class URLManager {

	private String urlName;

	public URLManager () {}
	
	public URLManager (String path) {
		urlName = path;
	}

	public Document getDom () {
		try {
			return Jsoup.connect(urlName).get();
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}

	public static Document getDomFromUrl (String urlName) {
		try {
			return Jsoup.connect(urlName).get();
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public static Document getDomFromFile (String fileName) {
		try {
			return Jsoup.parse(new File(fileName), "UTF-8");
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}

	public void cacheUrl (String fileName) {
		try (
			FileWriter fileWriter = new FileWriter(fileName, false);
		) {
			String [] cache = this.getDom().toString().split("\n");
			for (String s: cache) {
				fileWriter.write(s + "\n");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	

}
