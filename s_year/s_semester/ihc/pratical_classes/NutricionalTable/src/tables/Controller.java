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
    public TableView<TableEntry> table;

    @FXML private TableColumn<TableEntry, String> nameColumn;
    @FXML private TableColumn<TableEntry, Integer> calciumColumn;
    @FXML private TableColumn<TableEntry, Integer> weightColumn;
    @FXML private TableColumn<TableEntry, Integer> waterColumn;
    @FXML private TableColumn<TableEntry, Integer> energyColumn;

    Random r = new Random();

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        calciumColumn.setCellValueFactory(new PropertyValueFactory<>("calcium"));
        weightColumn.setCellValueFactory(new PropertyValueFactory<>("weight"));
        waterColumn.setCellValueFactory(new PropertyValueFactory<>("water"));
        energyColumn.setCellValueFactory(new PropertyValueFactory<>("energy"));
    }

    @FXML
    public void onToggle(ActionEvent event) {
        String toggleText = ((ToggleButton) event.getSource()).getText();
        String alignmentStyle;

        switch (toggleText) {
            case "Toggle Left":
                alignmentStyle = "-fx-alignment: CENTER_LEFT;";
                break;
            case "Toggle Center":
                alignmentStyle = "-fx-alignment: CENTER;";
                break;
            case "Toggle Right":
                alignmentStyle = "-fx-alignment: CENTER_RIGHT;";
                break;
            default:
                System.out.println("something is not right");
                return;
        }

        nameColumn.setStyle(alignmentStyle);
        calciumColumn.setStyle(alignmentStyle);
        weightColumn.setStyle(alignmentStyle);
        waterColumn.setStyle(alignmentStyle);
        energyColumn.setStyle(alignmentStyle);

        table.refresh();
    }

    @FXML
    public void onButtonPressed() {
        int calcium = r.nextInt(101);
        int weight = r.nextInt(101);
        int water = r.nextInt(101);
        int energy = r.nextInt(101);
        
        TableEntry data = new TableEntry(" ", calcium, weight, water, energy);

        table.getItems().add(data);
    }
}

