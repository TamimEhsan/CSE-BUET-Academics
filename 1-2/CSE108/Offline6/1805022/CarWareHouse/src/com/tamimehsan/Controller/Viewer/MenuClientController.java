package com.tamimehsan.Controller.Viewer;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MenuClientController {
    public void goToViewCar(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/viewAllCar.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void goToBuyCar(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/showRoom.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void goToSearchByReg(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/searchByReg.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void goToSearchByMakeModel(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/searchByMakeModel.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void goToLogin(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/login.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
}
