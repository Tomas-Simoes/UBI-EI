package paint;

import javafx.fxml.FXML;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.Spinner;
import javafx.scene.control.ToggleButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.input.MouseEvent;
import javafx.event.ActionEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Polygon;
import javafx.scene.control.SpinnerValueFactory;
import javafx.scene.control.SpinnerValueFactory.IntegerSpinnerValueFactory;

public class Controller {

    @FXML private Pane pane;
    @FXML private ColorPicker colorPicker;
    @FXML private Spinner<Integer> spinSize;

    @FXML private ToggleGroup togGroup;
    @FXML private ToggleButton togCircle;
    @FXML private ToggleButton togSquare;
    @FXML private ToggleButton togTriang;

    @FXML
    private void handleButtonAction(ActionEvent event) {
        pane.getChildren().clear();
    }

    @FXML
    private void panOnMouseReleased(MouseEvent event) {
        if (pane == null) {
            System.err.println("Pane is not injected!");
            return;
        }

        double x = event.getX();
        double y = event.getY();

        Color color = colorPicker.getValue();
        Integer size = spinSize.getValue(); // Ensure it's initialized

        if (size == null) {
            System.err.println("Spinner size is null!");
            return;
        }

        if (togCircle.isSelected()) {
            Circle circle = new Circle(size / 2.0, color);
            circle.setCenterX(x);
            circle.setCenterY(y);
            pane.getChildren().add(circle);
        } else if (togSquare.isSelected()) {
            Rectangle square = new Rectangle(size, size, color);
            square.setX(x - size / 2.0);
            square.setY(y - size / 2.0);
            pane.getChildren().add(square);
        } else if (togTriang.isSelected()) {
            double half = size / 2.0;
            Polygon triangle = new Polygon(
                x, y - half,
                x - half, y + half,
                x + half, y + half
            );
            triangle.setFill(color);
            pane.getChildren().add(triangle);
        }

        System.out.printf("Mouse clicked at: (%.2f, %.2f)%n", x, y);
    }

    @FXML
    public void initialize() {
        // Apenas necessário se não foi definido no FXML
        togCircle.setToggleGroup(togGroup);
        togSquare.setToggleGroup(togGroup);
        togTriang.setToggleGroup(togGroup);

        SpinnerValueFactory<Integer> valueFactory = new SpinnerValueFactory.IntegerSpinnerValueFactory(1, 100, 10);
        spinSize.setValueFactory(valueFactory);
    }
}
