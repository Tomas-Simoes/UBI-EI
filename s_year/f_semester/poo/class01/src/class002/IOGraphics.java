package class002;
import javax.swing.*;

public class IOGraphics {

	public static void main(String[] args) {
		int num;
		String s_num;
		String name;
		
		JOptionPane.showMessageDialog(null, "Welcome!");
		
		name = JOptionPane.showInputDialog(null, "Insert your name:");
		s_num = JOptionPane.showInputDialog(null, "Input a number:");
		
		num = Integer.parseInt(s_num);
		
		JOptionPane.showMessageDialog(null, "Bye Bye " + name + " who likes number " + s_num);
	}
}
