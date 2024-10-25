package class002;

import java.util.Random;
import java.util.random.*;

import javax.swing.JOptionPane;

public class randomNumbers {

	public static void main(String[] args) {
		int positiveNum = 0, negativeNum = 0;
		int lowerBound = -100, upperBound = 100;
		
		Random rand = new Random();
		
		for(int i = 0; i < 1000; i++) {
			int _newInt = rand.nextInt(upperBound-lowerBound) + lowerBound;
			
			if (_newInt < 0) negativeNum++;
			else positiveNum++;
		}
		
		JOptionPane.showMessageDialog(null, "In 1000 random numbers you got: \n Positive Numbers:" + Integer.toString(positiveNum) + "\n Negative Numbers: " + Integer.toString(negativeNum));
	}

}
