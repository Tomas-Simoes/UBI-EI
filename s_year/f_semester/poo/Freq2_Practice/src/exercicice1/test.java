package exercicice1;

import java.util.ArrayList;

public class test {
	public static void main(String[] args) {
		ArrayList<Integer> list = new ArrayList<Integer>();
		Boolean foundNumber = false;

		list.add(1);
		list.add(2);
		list.add(3);

		int searchNumber = 4;

		for (int i = 0; i <= list.size() - 1; i++) {
			if (list.get(i) == searchNumber) {
				foundNumber = true;
			}
		}

		System.out.println(foundNumber ? "asd" : "fds");
	}
}