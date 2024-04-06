package com.tamimehsan.Controller.Viewer;

import com.jfoenix.controls.JFXTextField;
import com.tamimehsan.Model.CarData;
import com.tamimehsan.Model.Intent;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ListView;
import com.tamimehsan.Model.Car;
import javafx.stage.Stage;

import java.io.IOException;

public class ShowRoomController {
    @FXML
    private ListView<Car> listView;
    @FXML
    private JFXTextField liveSearch;
    private ObservableList<Car> filteredList;
    public void initialize(){
       // listView.setItems(CarData.getInstance().getCarObservableList());
       // listView.setCellFactory( carListView -> new BuyViewCellController());
        filteredList = FXCollections.observableArrayList();
        listView.setItems(filteredList);
        searchCarLive("");
        listView.setCellFactory( carListView -> new BuyViewCellController());
        liveSearch.textProperty().addListener((observableValue, oldValue, newValue) -> {
            Intent.getInstance().setSearchText(newValue);
            searchCarLive(newValue);
        });
        Intent.getInstance().setCarListInterface(new CarListInterface() {
            @Override
            public void onListUpdated() {
                searchCarLive(Intent.getInstance().getSearchText());
            }
        });
    }
    public void goToMenu(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/menuClient.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void goToLogin(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/login.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void searchCarLive(String newValue){
        filteredList.clear();
        for(Car car:CarData.getInstance().getCarObservableList()){
            String carString = car.toString().toLowerCase();
            if( carString.contains(newValue.toLowerCase()) ){
                filteredList.add(car);
            }
        }
    }
}
