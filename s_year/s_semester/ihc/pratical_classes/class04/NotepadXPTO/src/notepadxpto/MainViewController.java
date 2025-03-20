package notepadxpto;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.Initializable;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.TextArea;
import javafx.scene.control.CheckBox;
import javafx.scene.text.Font;


public class MainViewController implements Initializable {
    @FXML
    TextField fontTextArea;
    
    @FXML
    TextField wordToFindTxtField;
    
    @FXML 
    TextField wordCountResult;
    
    @FXML
    CheckBox caseSensitiveCheckBox;
    
    @FXML
    TextArea textArea;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }  
    
    @FXML
    private void onFontChange() {
        try {
            int font = Integer.parseInt(fontTextArea.getText());
            
            textArea.setFont(new Font("System", font));
        } catch (NumberFormatException e) {
            fontTextArea.requestFocus();
            fontTextArea.selectAll();
        }
    }
    
    @FXML
    private void btnCount() {
        String wordToFind = wordToFindTxtField.getText();
        String currentTextArea = textArea.getText();
        boolean caseSensitive = caseSensitiveCheckBox.isSelected();
        
        int count = 0;    
        
        String[] textAreaArr = currentTextArea.split("[,\\s\\.]");
        for (String word : textAreaArr) {
            if(caseSensitive) {
                if (word.equals(wordToFind)) {
                    count++;
                }
            } else {
                if(word.equalsIgnoreCase(wordToFind)) {
                    count++;
            }
            }
        }
        
        wordCountResult.setText(Integer.toString(count));
    }
    
}
