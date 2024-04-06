package com.tamimehsan;

import com.jfoenix.controls.JFXSnackbar;
import com.tamimehsan.Model.Intent;
import com.tamimehsan.Network.Connection;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class Main extends Application {
    static Stage stage;
    @Override
    public void start(Stage primaryStage) throws Exception{
        Intent.getInstance().setStage(primaryStage);
        Parent root = FXMLLoader.load(getClass().getResource("View/login.fxml"));
        primaryStage.setTitle("Car warehouse");
        primaryStage.getIcons().add(new Image(this.getClass().getResourceAsStream("resources/cwds2.png")));
        primaryStage.setScene(new Scene(root, 300 , 520));
        primaryStage.show();
        primaryStage.setResizable(false);
        primaryStage.setOnCloseRequest((event) -> {
            Platform.exit(); // Stage Exit
            System.exit(0); // All thread Close
        });
        Connection.getInstance().startConnection();
    }

    public static void main(String[] args) {
        launch(args);
    }

}
