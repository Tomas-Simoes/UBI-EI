package Managers;

import java.util.ArrayList;

import UI.Menu;
import UI.UIElement;

public class UIManager extends Singleton {
	private static ArrayList<UIElement> activeElements;

	public static void initializeMenu(Menu newMenu) {
		for (UIElement el : newMenu.getMenuContent()) {
			System.out.println(el);

			if (!activeElements.contains(el)) {
				activeElements.add(el);
			}
		}
	}
}
