import java.io.IOException;
import java.util.Random;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class MainController {
    @FXML
    TextField input1;

    @FXML
    TextField input2;

    @FXML
    TextField input3;

    @FXML
    Label points;
    int valPoints = 0;
    
    private final Random random = new Random();
    
    @FXML
    public void onNextButtonPress(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("results.fxml"));
            Parent root = loader.load();
               
            int val1 = Integer.parseInt(input1.getText());
            int val2 = Integer.parseInt(input2.getText());
            int val3 = Integer.parseInt(input3.getText());
            
            ResultsController controller = loader.getController();
            controller.receiveData(val1, val2, val3);

            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setScene(new Scene(root));
            stage.show();

        } catch (IOException | NumberFormatException e) {
            e.printStackTrace(); // Handle errors gracefully in production
        }
    }
    
    public void receivePoints(int receivedPoints) {
        valPoints += receivedPoints;
        points.setText(String.valueOf(valPoints) + " Points");
    }
            
    public void initialize() {
        TextField[] inputs = {input1, input2, input3};

        for (TextField input : inputs) {
            int number = random.nextInt(100);
            input.setText(String.valueOf(number));
        }
    }
}