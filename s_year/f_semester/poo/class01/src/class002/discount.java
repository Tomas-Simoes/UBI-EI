package class002;

import javax.swing.JOptionPane;

public class discount {

	public static void main(String[] args) {
		double total = Integer.parseInt(JOptionPane.showInputDialog(args, "Input the total: "));
		
		if (total <= 10) JOptionPane.showMessageDialog(null, Double.toString(total));
		else if (total <= 100) JOptionPane.showMessageDialog(null, Double.toString(total - (total * 0.5)));
		else if (total <= 1000) JOptionPane.showMessageDialog(null, Double.toString(total - (total * 0.10)));
		else if (total <= 10000) JOptionPane.showMessageDialog(null, Double.toString(total - (total * 0.20)));
		else JOptionPane.showMessageDialog(null, Double.toString(total - (total * 0.25)));

	}

}
