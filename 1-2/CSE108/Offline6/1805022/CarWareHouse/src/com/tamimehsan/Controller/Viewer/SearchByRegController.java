package com.tamimehsan.Controller.Viewer;

import com.jfoenix.controls.JFXTextField;
import com.tamimehsan.Model.Car;
import com.tamimehsan.Model.CarData;
import com.tamimehsan.Model.Intent;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.io.IOException;

public class SearchByRegController {
    @FXML
    private JFXTextField regNumberTextField;
    @FXML
    private ListView<Car> listView;
    private ObservableList<Car> filteredList;
    public void initialize(){
        filteredList = FXCollections.observableArrayList();
        listView.setItems(filteredList);
        listView.setCellFactory( carListView -> new ViewCarCellController());
    }
    public void goToMenu(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/menuClient.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));

    }
    public void searchCar(){
        String reg = regNumberTextField.getText();
        filteredList.clear();
        int matched = 0;
        for(Car car:CarData.getInstance().getCarObservableList()){
            if( car.getRegistrationNumber().equals(reg) ){
                filteredList.add(car);
                matched++;
            }
        }
        Intent.getInstance().showToast(matched+" cars matched found",true);
    }
    public void searchPartial(){
        String reg = regNumberTextField.getText();
        filteredList.clear();
        int matched = 0;
        for(Car car:CarData.getInstance().getCarObservableList()){
            if( car.getRegistrationNumber().toLowerCase().contains(reg.toLowerCase()) ){
                filteredList.add(car);
                matched++;
            }
        }
        Intent.getInstance().showToast(matched+" cars matched found",true);
    }
}
