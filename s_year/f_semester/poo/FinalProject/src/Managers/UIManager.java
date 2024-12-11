package Managers;

import java.util.ArrayList;

import UI.LoginMenu;
import UI.Menu;
import UI.UIElement;

public class UIManager {
	private static ArrayList<UIElement> activeElements;

	private LoginMenu loginMenu;
	private final String[] loginOptions = { " Username: ", " Password: " };

	public UIManager() {
		activeElements = new ArrayList<UIElement>();
	}

	public void initializeMenu(Menu newMenu) {
		ArrayList<UIElement> menuContent = newMenu.getMenuContent();
		menuContent.get(0).onSelected();

		for (UIElement el : newMenu.getMenuContent()) {
			System.out.println(el.getContent());

			if (!activeElements.contains(el)) {
				activeElements.add(el);
			}
		}
	}

	public void initializeLogin() {
		LoginMenu newLoginMenu = new LoginMenu(loginOptions);

		setLoginMenu(newLoginMenu);
		initializeMenu(newLoginMenu);
	}

	public void setLoginMenu(LoginMenu loginMenu) {
		this.loginMenu = loginMenu;
	}
}
