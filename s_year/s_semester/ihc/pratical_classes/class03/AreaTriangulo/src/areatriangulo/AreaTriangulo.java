package areatriangulo;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class AreaTriangulo extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        // Load the FXML file (make sure the resource path is correct)
        Parent root = FXMLLoader.load(getClass().getResource("MainView.fxml"));
        primaryStage.setTitle("Area do Triangulo");
        primaryStage.setScene(new Scene(root));
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    public static void main(String[] args) {
        // Launches the JavaFX application which will call start()
        launch(args);
    }
}
