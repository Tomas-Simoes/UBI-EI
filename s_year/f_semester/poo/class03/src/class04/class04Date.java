package class04;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import class03.Read;

public class class04Date {

	private static String[] greatings = { "Bom dia", "Boa tarde", "Boa noite" };
	private static String name = "Escreva aqui o seu nome";
	private static LocalDateTime localDate;
	private static int hours;
	private static int minutes;

	public static void getHours() {
		localDate = LocalDateTime.now();
		hours = localDate.getHour();
		minutes = localDate.getMinute();
	}

	private static int periodDay(int h) {
		return (h + 20) / 8 % 3;
	}

	static void next13Fridays() {
		int fridaysNumber = 0;

		for (LocalDate date = LocalDate.now(); fridaysNumber < 14; date = date.plusDays(1)) {
			if (date.getDayOfMonth() == 13 && date.getDayOfWeek() == DayOfWeek.valueOf("FRIDAY")) {
				System.out.println(date);
				fridaysNumber++;
			}
		}
	}

	public static void main(String args[]) {
		getHours();

		System.out.print("Qual o seu nome? ");
		name = Read.umaString();

		System.out.println(greatings[periodDay(hours)] + ", " + name);
		System.out.print("São " + localDate.format(DateTimeFormatter.ofPattern("HH:mm:ss")));
		System.out.println("e hoje é dia " + localDate.format(DateTimeFormatter.ofPattern("dd/MM/yyyy")));

		next13Fridays();
	}
}
