
public class Player {
	private static int lastNumber = 0;
	private String name;
	private double salary;
	private int[] goals;
	private int number;

	public Player(String name, double salary, int[] goals) {
		this.name = name;
		this.salary = salary;
		this.goals = goals;
		this.number = lastNumber;
		lastNumber++;
	}

}
