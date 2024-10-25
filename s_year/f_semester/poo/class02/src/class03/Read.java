package class03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Read {

	public static String umaString() {
		String s = "";
		try {
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			s = in.readLine();
		} catch (IOException e) {
			System.out.println("Erro ao Read fluxo de entrada.");
		}
		return s;
	}

	public static int umInt() {
		while (true) {
			try {
				return Integer.parseInt(umaString().trim());
			} catch (NumberFormatException e) {
				System.out.println("Não é um inteiro válido!!!");
			}
		}
	}

	public static byte umByte() {
		while (true) {
			try {
				return Byte.parseByte(umaString().trim());
			} catch (NumberFormatException e) {
				System.out.println("Não é um byte válido!!!");
			}
		}
	}

	public static short umShort() {
		while (true) {
			try {
				return Short.parseShort(umaString().trim());
			} catch (NumberFormatException e) {
				System.out.println("Não é um short válido!!!");
			}
		}
	}

	public static long umLong() {
		while (true) {
			try {
				return Long.parseLong(umaString().trim());
			} catch (NumberFormatException e) {
				System.out.println("Não é um long válido!!!");
			}
		}
	}

	public static float umFloat() {
		while (true) {
			try {
				return Float.parseFloat(umaString().trim());
			} catch (NumberFormatException e) {
				System.out.println("Não é um float válido!!!");
			}
		}
	}

	public static double umDouble() {
		while (true) {
			try {
				return Double.valueOf(umaString().trim());
			} catch (NumberFormatException e) {
				System.out.println("Não é um double válido!!!");
			}
		}
	}

	public static char umChar() {
		while (true) {
			try {
				return umaString().charAt(0);
			} catch (Exception e) {
				System.out.println("Não é um char válido!!!");
			}
		}
	}

	public static boolean umBoolean() {
		while (true) {
			try {
				return Boolean.parseBoolean(umaString().trim());
			} catch (Exception e) {
				System.out.println("Não é um boolean válido!!!");
			}
		}
	}
}