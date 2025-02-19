package class002;

import javax.swing.JOptionPane;

public class circleMath {

	public static void main(String[] args) {
		final double PI =3.14159273269;
		int radius = Integer.parseInt(JOptionPane.showInputDialog("Insert the radius of the circle"));
	
		JOptionPane.showMessageDialog(null, Double.toString(2 * PI * radius));
		JOptionPane.showMessageDialog(null, Double.toString(PI * radius * radius));
	}

}
