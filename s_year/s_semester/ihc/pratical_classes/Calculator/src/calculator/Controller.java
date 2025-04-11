package calculator;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import pt.ubi.ihc.Registadora;

public class Controller {

    @FXML private TextArea inputArea;
    @FXML private Label result;

    private Registadora model;
    // Use StringBuilder to accumulate digit inputs efficiently.
    private StringBuilder currentInput = new StringBuilder();

    public void initialize() {
        model = new Registadora();
    }
    
    private void processBtn(Button btn) {
        String btnText = btn.getText();
        Double res;
        
        switch (btnText) {
            case "+":
            case "-":
            case "x":
            case "/":
                if (currentInput.length() > 0) {
                    try {
                        double number = Double.parseDouble(currentInput.toString());
                        model.regista(number);
                    } catch (NumberFormatException e) {
                        System.out.println("Erro: Número inválido: " + currentInput.toString());
                    }
                    
                    currentInput.setLength(0); 
                }
                
                model.defineOperador(btnText.charAt(0));
                inputArea.appendText(btnText);
                
                res = model.getResultado();
                result.setText(res.toString());
                
                break;
            case "C":
                inputArea.setText(" ");
                result.setText("0.00");
                currentInput.setLength(0);
                
                model = new Registadora();
                break;
            case "Result":
                // Flush any pending number before calculating the result.
                if (currentInput.length() > 0) {
                    try {
                        double number = Double.parseDouble(currentInput.toString());
                        model.regista(number);
                    } catch (NumberFormatException e) {
                        System.out.println("Erro: Número inválido: " + currentInput.toString());
                    }
                    
                    currentInput.setLength(0);
                }
                
                res = model.getResultado();
                result.setText(res.toString());
                
                inputArea.appendText("\n-------------\n");
                inputArea.appendText("Result: " + res);
                break;
            default:
                currentInput.append(btnText);
                inputArea.appendText(btnText);
                break;
        }
    }
    
    @FXML
    private void handleButtonAction(ActionEvent event) {
        if (event.getSource() instanceof Button btn) {
            processBtn(btn);
        }
    }
}
