package calculator;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;

import pt.ubi.ihc.Registadora;

public class Controller {
    String lastOperator;
    
    @FXML
    private Label label;

    private Registadora model;
    
    @FXML private TextArea inputArea;
    @FXML private Label result;
    
    public void initialize() {
        model = new Registadora();
    }
    
    private void processBtn(Button btn) {
        String btnStr = btn.getText();
                
        switch(btnStr) {
            case "+":
            case "-":
            case "x":
            case "/":
                // button is operator
                System.out.println("Got a operator: " + btnStr);
                
                model.defineOperador(btnStr.charAt(0));

                inputArea.appendText(btnStr);
                inputArea.appendText("\n");
                break;
            case "C":
                System.out.println("Got a clear operator: " + btnStr);

                // clear
                break;
            case "Result":
                // get result
                System.out.println("Got a result operator: " + btnStr);

                Double res = model.getResultado();
                result.setText(res.toString());
                break;
            default:
                try {
                    System.out.println("Got a number: " + btnStr);

                    double number = Double.parseDouble(btnStr);
                    model.regista(number);
                } catch (NumberFormatException e) {
                    System.out.println("error");
                }
                break;
        }
    }
    
    @FXML private void handleButtonAction(ActionEvent event) {
        if(event.getSource() instanceof Button pressedBtn) {
            processBtn(pressedBtn);
        }
    }
}
