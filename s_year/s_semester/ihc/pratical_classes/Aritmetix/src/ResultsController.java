import java.io.IOException;
import java.util.Random;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class ResultsController {
    @FXML
    TextField input1;

    @FXML
    TextField input2;

    @FXML
    TextField input3;
    
    @FXML
    Label operator1;

    @FXML
    Label operator2;
    
    int pointsReceived;
    
    private final Random random = new Random();

    public void receiveData(int val1, int val2, int val3) {
        input1.setText(String.valueOf(val1));
        input2.setText(String.valueOf(val2));
        input3.setText(String.valueOf(val3));
        
        String op1 = operator1.getText();
        String op2 = operator2.getText();
        
        boolean isFirstEquals = op1.equals("=");
        
        pointsReceived = validateEquation(val1, val2, val3, op2, isFirstEquals);
        System.out.println("points gained: " + pointsReceived);
    }
    
    private int validateEquation(int val1, int val2, int val3, String op, boolean isReversed) {
        int result, userGuess;
        
        if(isReversed) {
            result = calculateResult(val2, val3, op);
            userGuess = val1;
        } else {
            result = calculateResult(val1, val2, op);
            userGuess = val3;
        }
        
        return userGuess - result;
    }
    
    private int calculateResult(int a, int b, String op) {
        switch (op) {
            case "+":
                return a + b;
            case "-":
                return a - b;
            case "*":
                return a * b;
            case "/":
                return a / b;
            default:
                return 0;
        }
    }
    
    @FXML
    public void onPlayAgainPress(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("main.fxml"));
            Parent root = loader.load();
               
            MainController controller = loader.getController();
            controller.receivePoints(pointsReceived);

            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setScene(new Scene(root));
            stage.show();

        } catch (IOException | NumberFormatException e) {
            e.printStackTrace(); // Handle errors gracefully in production
        }
    }
    
    @FXML 
    public void initialize() {
        String[] operators = {"+", "-", "*", "/"};
        Label[] labels = {operator1, operator2};
    
        int equalsIndex = random.nextInt(2);
        int operatorIndex = 1 - equalsIndex;
    
        labels[equalsIndex].setText("=");
        labels[operatorIndex].setText(operators[random.nextInt(operators.length)]);
    }
}