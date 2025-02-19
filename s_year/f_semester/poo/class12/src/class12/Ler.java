package class12;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Ler {
	public static int umInt() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			return br.read();
		} catch (IOException e) {
			e.printStackTrace();
			return -1;
		}
	}

	public static String umaString() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			return br.readLine();
		} catch (IOException e) {
			e.printStackTrace();
			return " ";
		}
	}
}
