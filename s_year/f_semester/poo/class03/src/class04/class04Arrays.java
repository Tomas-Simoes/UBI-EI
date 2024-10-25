package class04;

import class03.Read;

public class class04Arrays {
	static int[] arr1 = new int[] { 1, 2, 3, 4, 5 };
	static int[] arr2;
	static int[][] matrix = new int[][] { { 1, 2, 3 }, { 4, 5, 6 } };

	static int menu() {
		System.out.println("Opções: ");
		System.out.println("1 – Ler array ");
		System.out.println("2 - Escrever array ");
		System.out.println("3 - Produto Interno ");
		System.out.println("4 - Maior valor");
		System.out.println("0 - Terminar ");
		System.out.println("Qual a sua opção? ");

		int op = Read.umInt();
		return op;
	}

	static int[] lerArray() {
		System.out.println("Qual a dimensão do array? ");
		int dim = Read.umInt();
		int[] arr = new int[dim];

		System.out.println("Introduza os valores do array: ");
		for (int i = 0; i < arr.length; i++) {
			System.out.println("Posição " + i + ":");
			arr[i] = Read.umInt();
		}

		return arr;
	}

	static void printArray(int[] arr) {
		for (int i = 0; i < arr.length; i++) {
			System.out.println("Element " + i + ": " + arr[i]);
		}
	}

	static void internalProduct(int[] arr1, int[] arr2) {
		for (int i = 0; i < arr1.length; i++) {
			System.out.println("The internal product is: " + arr1[i] * arr2[i]);
		}
	}

	static void higherNumber() {
		int higher = arr1[0];

		for (int i = 1; i < arr1.length; i++) {
			if (arr1[i] > higher) {
				higher = arr1[i];
			}
		}
	}

	static boolean searchNumber() {
		System.out.print("Which number you want to search? ");
		int num = Read.umInt();

		for (int i = 0; i < arr1.length; i++) {
			if (arr1[i] == num) {
				return true;
			}
		}

		return false;
	}

	static int[] multiple() {
		int[] newArr = new int[arr1.length];
		for (int i = 0; i < arr1.length; i++) {
			newArr[i] = arr1[i] * 3;
		}

		return newArr;
	}

	static void readMatrix() {
		System.out.println("How many rows: ");
		int row = Read.umInt();

		System.out.println("How many columns: ");
		int column = Read.umInt();

		for (int i = 0; i < row; i++) {
			for (int z = 0; z < column; z++) {
				System.out.println("Insert a number: ");
				int newNum = Read.umInt();

				matrix[i][z] = newNum;
			}
		}
	}

	static void writeMatrix() {
		for (int i = 0; i < matrix.length; i++) {
			for (int z = 0; z < matrix[0].length; z++) {
				System.out.print(matrix[i][z] + ", ");
			}
			System.out.println();
		}
	}

	static void transposedMatrix() {
		int[][] newMatrix = new int[matrix.length][matrix[0].length];
		for (int i = 0; i < matrix.length; i++) {
			for (int z = 0; z < matrix[0].length; z++) {
				newMatrix[z][i] = matrix[i][z];
			}
			System.out.println();
		}
	}

	public static void main(String[] args) {
		int escolha, dim;
		do {
			escolha = menu();
			switch (escolha) {
			case 1:
				lerArray();
				break;
			case 2:
				arr1 = lerArray();
				printArray(arr1);
				break;
			case 3:
				System.out.println("Insert two arrays! ");

				arr1 = lerArray();
				arr2 = lerArray();

				internalProduct(arr1, arr2);

				break;
			case 4:
				System.out.println();

				higherNumber();
				break;

			case 5:
				searchNumber();
				break;
			case 6:
				multiple();
				break;
			case 7:
				readMatrix();
				break;
			case 8:
				writeMatrix();
				break;
			}
		} while (escolha != 0);
	}

}
