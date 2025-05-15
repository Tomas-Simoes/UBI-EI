package paint;

import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.Spinner;
import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import javafx.event.ActionEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.control.SpinnerValueFactory;

public class Controller {
    @FXML private Pane pane;
    @FXML private Canvas canvas;
    @FXML private ColorPicker colorPicker;
    @FXML private Spinner<Integer> spinSize;
    @FXML private Button clearButton;
    
    // Variables to track drawing state
    private double lastX;
    private double lastY;
    private GraphicsContext gc;
    
    @FXML
    private void handleClearAction(ActionEvent event) {
        if (gc != null) {
            gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        }
    }
    
    @FXML
    private void canvasOnMousePressed(MouseEvent event) {
        lastX = event.getX();
        lastY = event.getY();
        
        gc.setFill(colorPicker.getValue());
        double size = spinSize.getValue();
        gc.fillOval(lastX - size/2, lastY - size/2, size, size);
    }
    
    @FXML
    private void canvasOnMouseDragged(MouseEvent event) {
        double x = event.getX();
        double y = event.getY();
    
        gc.setStroke(colorPicker.getValue());
        gc.setLineWidth(spinSize.getValue());
    
        gc.strokeLine(lastX, lastY, x, y);
    
        lastX = x;
        lastY = y;
    
        System.out.printf("Drawing at: (%.2f, %.2f)%n", x, y);
    }

    
    @FXML
    public void initialize() {
        SpinnerValueFactory<Integer> valueFactory = 
            new SpinnerValueFactory.IntegerSpinnerValueFactory(1, 50, 5);
        spinSize.setValueFactory(valueFactory);
        
        colorPicker.setValue(Color.BLACK);
        
        gc = canvas.getGraphicsContext2D();
        
        gc.setLineCap(javafx.scene.shape.StrokeLineCap.ROUND);
        gc.setLineJoin(javafx.scene.shape.StrokeLineJoin.ROUND);
    }
}