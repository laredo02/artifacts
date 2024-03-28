package main;

import java.io.*;
import java.util.*;

import opennlp.tools.langdetect.*;
import opennlp.tools.sentdetect.*;

public class Main {

	public static void main (String [] args) {
		try {
			new Main().detectSentences(new Main().readFile("rsc/text.txt"));
			new Main().detectLang("d");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void detectLang (String sentence) throws IOException {
		InputStream inputStream = new FileInputStream("models/.bin");
		LanguageDetectorModel languageDetectorModel = new LanguageDetectorModel(inputStream);
		LanguageDetector languageDetector = new LanguageDetectorME(languageDetectorModel);
		Language lang = languageDetector.predictLanguage(new Main().readFile("rsc/text.txt"));
		System.out.println("\n\n\n" + lang.getLang());
	}

	public void detectSentences (String sentence) throws IOException {
		InputStream inputStream = new FileInputStream("models/en-sent.bin");
		SentenceModel sentenceModel = new SentenceModel(inputStream);
		SentenceDetectorME detector = new SentenceDetectorME(sentenceModel);
		String sentences [] = detector.sentDetect(sentence);
		for (String sent: sentences) {
			System.out.println(sent);
		}
	}

	public String readFile (String fileName) throws IOException {
		StringBuilder stringBuilder = new StringBuilder();
		BufferedReader bufferedReader = new BufferedReader(new FileReader(new File(fileName)));
		String string;
		while ((string = bufferedReader.readLine()) != null) {
			stringBuilder.append(string);
		}
		return stringBuilder.toString();
	}

}
