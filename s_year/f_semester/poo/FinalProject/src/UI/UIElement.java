package UI;

public class UIElement {
	private String content;

	public UIElement(String content) {
		this.content = content;
	}

	public void onIdle() {

	}

	public void onSelected() {
		String newContent = Colors.TEXT_BRIGHT_BLUE + "> " + content + Colors.TEXT_WHITE;
		this.setContent(newContent);
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}
}
