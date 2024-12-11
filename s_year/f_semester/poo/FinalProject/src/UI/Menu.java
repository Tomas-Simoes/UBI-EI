package UI;

import java.util.ArrayList;

public class Menu {
	private ArrayList<UIElement> menuContent;

	public Menu(String[] options) {
		this.setMenuContent(this.stringToUIElement(options));
	}

	public ArrayList<UIElement> getMenuContent() {
		return menuContent;
	}

	public void setMenuContent(ArrayList<UIElement> menuContent) {
		this.menuContent = menuContent;
	}

	public ArrayList<UIElement> stringToUIElement(String[] options) {
		ArrayList<UIElement> result = new ArrayList<UIElement>();

		for (String str : options) {
			UIElement el = new UIElement(str);
			result.add(el);
		}

		return result;
	}
}
