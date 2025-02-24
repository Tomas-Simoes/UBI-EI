package class002;

import javax.swing.JOptionPane;

public class higherNumber {

	public static void main(String[] args) {
		int num1, num2, num3, highest_num;
		
		num1 = Integer.parseInt(JOptionPane.showInputDialog(null, "Insert a number: "));
		num2 = Integer.parseInt(JOptionPane.showInputDialog(null, "Another one please: "));
		num3 = Integer.parseInt(JOptionPane.showInputDialog(null, "Just one more: "));
		
		highest_num = num1 > num2 ? num1 : num2;
		highest_num = num3 > highest_num ? num3 : highest_num;
		
		JOptionPane.showMessageDialog(null, "Thank you! The highest number is " + highest_num);
	}

}
