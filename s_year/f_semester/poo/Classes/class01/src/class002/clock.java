package class002;

import javax.swing.JOptionPane;

public class clock {

	public static void main(String[] args) {
	
		int hour = Integer.parseInt(JOptionPane.showInputDialog(null, "Please choose a hour of the day: "));
		
		switch (hour) {
			case 21:
			case 22:
			case 23:
		    case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				JOptionPane.showMessageDialog(null, "Good Night!");
				break;
			case 7:
			case 8:
			case 9: 
			case 10:
				JOptionPane.showMessageDialog(null, "Good Morning!");
				break;
			default:
				JOptionPane.showMessageDialog(null, "Good Afternoon!");
				break;
		}
	}
}
