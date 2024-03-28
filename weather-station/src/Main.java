package main;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class Main {
 
	private final String userHome, indexFileName, yrnoUrl, yrnoUrlCache;

	{
		userHome = System.getProperty("user.home");
		indexFileName = userHome + "/WeatherStation/html/index.html";
		yrnoUrl = "https://www.yr.no/place/Norway/Oslo/Oslo/Oslo/";
		yrnoUrlCache = userHome + "/WeatherStation/cache/yrno.html";
	}

	protected void startLocalWebServer (int port) {	
		LocalWebServer localWebServer = new LocalWebServer(port, indexFileName);
		localWebServer.start();
	}

	protected void startConfigurationServer (int port) {
		ConfigurationServer configurationServer = new ConfigurationServer(port);
		configurationServer.start();
	}

	protected void setCacheUpdater (Main main) {
		TimerTask timerTask = main.new CacheUrlTask();
		Timer timer = new Timer("MyCacheTimer", false);
		Date date = Calendar.getInstance().getTime();
		timer.schedule(timerTask, date, 1200000);
	}

	protected void setHtmlUpdater (Main main) {
		TimerTask timerTask = main.new UpdateHtml();
		Timer timer = new Timer("MyHtmlUpdater", false);
		Date date = Calendar.getInstance().getTime();
		timer.schedule(timerTask, date, 1000);
	}

	//////////////////////////////////////////////////////////////
							//Main
	//////////////////////////////////////////////////////////////
	public static void main(String[] args) {
		Main main = new Main();
		main.startLocalWebServer(9090);
		main.startConfigurationServer(9091);
		main.setCacheUpdater(main);
		main.setHtmlUpdater(main);
	}
	//////////////////////////////////////////////////////////////
							//Main
	//////////////////////////////////////////////////////////////

	class CacheUrlTask extends TimerTask {

		@Override
		public void run () {
			cacheUrlIndex(yrnoUrl, yrnoUrlCache);
		}
		
		private void cacheUrlIndex (String urlName, String fileName) {
			URLManager urlManager = new URLManager(urlName);
			urlManager.cacheUrl(fileName);
		}

		private void writeElementsToFile (String fileName, Elements elements) {
			try (FileWriter fileWriter = new FileWriter(fileName, false)) {
				for (Element e: elements) {
					fileWriter.write(e.text() + "\n");
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	class UpdateHtml extends TimerTask {

		private Element todayFirstTime, todayFirstTemperature, todaySecondTime, todaySecondTempertature;

		public UpdateHtml () {

		}

		@Override
		public void run () {
			reloadIndex();
		}

		private void reloadIndex() {
			Document indexDocument = URLManager.getDomFromFile(indexFileName);
			Document urlDocument = URLManager.getDomFromUrl(yrnoUrl);
			if (urlDocument == null) {
				urlDocument = URLManager.getDomFromFile(yrnoUrlCache);
			}
			Element indexWrapperDiv = indexDocument.getElementById("today-overview");
			indexWrapperDiv.empty();
			Elements urlWrapperDiv = urlDocument.getElementsByClass("yr-table yr-table-overview2 yr-popup-area");
			indexWrapperDiv.append(urlWrapperDiv.toString());
			writeDocumentToIndex(indexDocument);
		}

		private void writeDocumentToIndex (Document doc) {
			try (
				BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(new File(indexFileName), false));
			) {
				bufferedWriter.write(doc.toString());
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

}




