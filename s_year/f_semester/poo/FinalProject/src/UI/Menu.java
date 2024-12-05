package UI;

import java.util.ArrayList;

public class Menu {
	private ArrayList<UIElement> menuContent;

	public Menu(ArrayList<UIElement> menuContent) {
		this.setMenuContent(menuContent);
	}

	public ArrayList<UIElement> getMenuContent() {
		return menuContent;
	}

	public void setMenuContent(ArrayList<UIElement> menuContent) {
		this.menuContent = menuContent;
	}

	public void stringToUIElement(String str) {
	}
}
