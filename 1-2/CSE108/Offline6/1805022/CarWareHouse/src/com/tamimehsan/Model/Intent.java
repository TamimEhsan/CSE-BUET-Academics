package com.tamimehsan.Model;

import com.jfoenix.controls.JFXSnackbar;
import com.tamimehsan.Controller.Viewer.CarListInterface;
import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;

import java.io.IOException;

public class Intent {
    private static Intent instance;
    private CarListInterface carListInterface;
    private Car data;
    private int position;
    private Stage stage;
    private String userName;
    private String searchText = "";

    private Intent() {
    }

    public static Intent getInstance() {
        if (instance == null) {
            instance = new Intent();
        }
        return instance;
    }

    public Car getData() {
        return data;
    }

    public void setData(Car data) {
        this.data = data;
    }

    public int getPosition() {
        return position;
    }

    public void setPosition(int position) {
        this.position = position;
    }

    public Stage getStage() {
        return stage;
    }

    public void setStage(Stage stage) {
        this.stage = stage;
    }

    public void confirmLogin() {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("../View/Manufacturer/godown.fxml"));
            stage.setScene(new Scene(root));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void showSuccess(String header, String message) {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Success!");
        alert.setHeaderText(header);
        alert.setContentText(message);
        alert.showAndWait();
    }

    public void showError(String header, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error!");
        alert.setHeaderText(header);
        // alert.setContentText("The username and password you provided is not correct.");
        alert.setContentText(message);
        alert.showAndWait();
    }

    public void showToast(String toastMsg, boolean isSuccess) {
        Stage toastStage = new Stage();
        toastStage.initOwner(stage);

        toastStage.setResizable(false);
        toastStage.initStyle(StageStyle.TRANSPARENT);

        Text text = new Text(toastMsg);
        text.setFont(Font.font("Verdana", 20));
        text.setFill(Color.WHITE);

        StackPane root = new StackPane(text);
        if (isSuccess) {
            root.setStyle("-fx-background-color: #8ac932; -fx-padding: 10px;");
        } else {
            root.setStyle("-fx-background-color: #e05b36; -fx-padding: 10px;");
        }
        root.setPrefWidth(stage.getWidth() - 16);
        toastStage.setY(stage.getY() + stage.getHeight() - 50);
        toastStage.setX(stage.getX() + 8);

        root.setOpacity(0);

        Scene scene = new Scene(root);
        scene.setFill(Color.TRANSPARENT);
        toastStage.setScene(scene);
        toastStage.show();

        Timeline fadeInTimeline = new Timeline();
        KeyFrame fadeInKey1 = new KeyFrame(Duration.ZERO.millis(500), new KeyValue(toastStage.getScene().getRoot().opacityProperty(), 1));
        fadeInTimeline.getKeyFrames().add(fadeInKey1);
        fadeInTimeline.setOnFinished((ae) ->
        {
            new Thread(() -> {
                try {
                    Thread.sleep(1500);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                Timeline fadeOutTimeline = new Timeline();
                KeyFrame fadeOutKey1 = new KeyFrame(Duration.millis(500), new KeyValue(toastStage.getScene().getRoot().opacityProperty(), 0));
                fadeOutTimeline.getKeyFrames().add(fadeOutKey1);
                fadeOutTimeline.setOnFinished((aeb) -> toastStage.close());
                fadeOutTimeline.play();
            }).start();
        });
        fadeInTimeline.play();
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public CarListInterface getCarListInterface() {
        return carListInterface;
    }

    public void setCarListInterface(CarListInterface carListInterface) {
        this.carListInterface = carListInterface;
    }

    public String getSearchText() {
        return searchText;
    }

    public void setSearchText(String searchText) {
        this.searchText = searchText;
    }
}
