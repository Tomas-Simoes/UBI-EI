package class03;

public class practiceExercices {
	public static void main(String args[]) {
		// sums();
		// ascii();
		// invert();
		// totoloto();
		totolotoRandom();

	}

	private static void sums() {
		System.out.println("Insert two numbers, p and u such as p <= u: \n p: ");
		int p = Read.umInt();

		System.out.println("u: ");
		int u = Read.umInt();

		int total = p;
		for (int i = p++; i <= u; i++) {
			total += i + 1;
		}

		System.out.println("The sum is: " + total);
	}

	private static void ascii() {
		System.out.println("Insert a word: ");
		String str = Read.umaString();

		int lowestAscii = 1000;

		for (char c : str.toCharArray()) {
			int charAscii = (int) c;
			lowestAscii = charAscii < lowestAscii ? charAscii : lowestAscii;
		}

		System.out.println("The character with the lowest ASCII code is " + Character.toString(lowestAscii)
				+ " which is " + lowestAscii);
	}

	private static void invert() {
		System.out.println("Insert a number: ");

		int number = Read.umInt();
		int newNumber = 0;
		String numberStr = String.valueOf(number);

		for (int i = 0, z = 1; i < numberStr.length(); i++, z *= 10) {
			newNumber += Character.getNumericValue(numberStr.charAt(i)) * z;
		}

		System.out.println("Your inverted number is: " + newNumber);
	}

	private static void totoloto() {
		System.out.println("Insert 6 numbers in a row: ");
		String totolotoKey = "";
		for (int i = 0; i < 6; i++) {
			String c = String.valueOf(Read.umInt());
			totolotoKey += c + "; ";
		}
		System.out.println("Your Totoloto key is: " + totolotoKey);
	}

	private static void totolotoRandom() {
		int totolotoKey[] = new int[6];
		int range = 49 - 1 + 1;

		for (int i = 0; i < 6; i++) {
			int randomNum = (int) (Math.random() * range);

			for (int y : totolotoKey) {
				if (y == randomNum) {
					y--;
					continue;
				}
			}
			totolotoKey[i] = (int) randomNum;
		}

		System.out.print("Your Totoloto key is: ");
		for (int z : totolotoKey)
			System.out.print(z + ", ");
	}
}
