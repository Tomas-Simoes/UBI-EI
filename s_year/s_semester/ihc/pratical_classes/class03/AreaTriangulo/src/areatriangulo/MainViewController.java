package areatriangulo ;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.Initializable;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

public class MainViewController implements Initializable {

    @FXML
    TextField txfA;

    @FXML
    TextField txfB;

    @FXML
    TextField txfC;

    @FXML
    Label lblArea;

    @FXML
    private void butCalcular(){
        try {                       
            Double a = validateInput(txfA); 
            Double b = validateInput(txfB);
            Double c = validateInput(txfC);
            
            if(a == null || b == null || c == null ) { return; }
            
            if(a > b + c) { txfA.setText("error: a > b + c"); return; }
            if(b > a + c) { txfB.setText("error: b > a + c"); return; }
            if(c > a + b) { txfC.setText("error: c > a + b"); return; }
            
            double s = (a + b + c) / 2; 
            double area = Math.sqrt(s * (s-a) * (s-b) * (s-c));
            
            lblArea.setText(Double.toString(area));
        } catch (NumberFormatException e) {
           System.out.println("An error ocurred: " + e.getMessage());
        }
    }
    
    private Double validateInput(TextField txtField) {
        Double num;
        
        try {                       
            return Double.parseDouble(txtField.getText());
        } catch (NumberFormatException e) {            
            System.out.println("An error ocurred: " + e.getMessage());
            
            txtField.requestFocus();
            txtField.selectAll();
                    
            return null;
        }
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {

    }

}
