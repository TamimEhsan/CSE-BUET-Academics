package com.tamimehsan.Controller.Manufacture;

import com.tamimehsan.Model.Car;
import com.tamimehsan.Model.CarData;
import com.tamimehsan.Model.Intent;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.io.IOException;

public class GodownController {
    @FXML
    private ListView<Car> carListView;
    @FXML
    private Label username;
    public void initialize(){
        username.setText(Intent.getInstance().getUserName());
        carListView.setItems(CarData.getInstance().getCarObservableList());
        carListView.setCellFactory( carListView -> new ManufactureViewCellController());
    }
    public void addNewCar(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Manufacturer/addCar.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void goToLogin(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/login.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void clicked(){
        int index = carListView.getSelectionModel().getSelectedIndex();
        System.out.println(index);
    }
}
