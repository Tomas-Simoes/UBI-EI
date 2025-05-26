package tables;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.ToggleButton;
import javafx.event.ActionEvent;

import java.net.URL;
import java.util.Random;
import java.util.ResourceBundle;

import tables.TableEntry;

public class Controller implements Initializable {

    @FXML
    private TableView table;
    @FXML private TableColumn<TableEntry, Integer> intColumn;
    @FXML private TableColumn<TableEntry, Float> floatColumn;
    @FXML private TableColumn<TableEntry, String> stringColumn;
    
    Random r = new Random();
    
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        intColumn.setCellValueFactory(new PropertyValueFactory<>("integer"));
        floatColumn.setCellValueFactory(new PropertyValueFactory<>("decimal"));
        stringColumn.setCellValueFactory(new PropertyValueFactory<>("word"));
    }
    
    @FXML
    public void onToggle(ActionEvent event) {
        System.out.println("yo");
        System.out.println(((ToggleButton)event.getSource()).getText());
        
        switch (((ToggleButton) event.getSource()).getText()) {
            case "Toggle Left":
                intColumn.setStyle("-fx-alignment: CENTER_LEFT;");
                floatColumn.setStyle("-fx-alignment: CENTER_LEFT;");
                stringColumn.setStyle("-fx-alignment: CENTER_LEFT;");
                break;
            case "Toggle Center":
                intColumn.setStyle("-fx-alignment: CENTER;");
                floatColumn.setStyle("-fx-alignment: CENTER;");
                stringColumn.setStyle("-fx-alignment: CENTER;");
                break;
            case "Toggle Right":
                intColumn.setStyle("-fx-alignment: CENTER_RIGHT;");
                floatColumn.setStyle("-fx-alignment: CENTER_RIGHT;");
                stringColumn.setStyle("-fx-alignment: CENTER_RIGHT;");
                break;
            default:
                System.out.println("something is not right");
                break;
        }
        
        table.refresh();
    }
    
    public void onButtonPressed() {
        StringBuilder randomWord = new StringBuilder();
        
        for(int i = 0; i <= 10; i++) {
            int randAscii = r.nextInt(95) + 32;
            randomWord.append((char) randAscii);
        }
        
        TableEntry data = new TableEntry(r.nextInt(100), r.nextFloat(), randomWord.toString());
        
        table.getItems().add(data);
    }
}

