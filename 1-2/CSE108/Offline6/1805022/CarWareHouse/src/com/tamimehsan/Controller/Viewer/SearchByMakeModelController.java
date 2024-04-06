package com.tamimehsan.Controller.Viewer;

import com.jfoenix.controls.JFXTextField;
import com.tamimehsan.Model.Car;
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
import javafx.stage.Stage;

import java.io.IOException;

public class SearchByMakeModelController {
    @FXML
    private JFXTextField carMakeTextField;
    @FXML
    private JFXTextField carModelTextField;
    @FXML
    private ListView<Car> listView;
    private ObservableList<Car> filteredList;

    public void initialize() {
        filteredList = FXCollections.observableArrayList();
        listView.setItems(filteredList);
        listView.setCellFactory(carListView -> new ViewCarCellController());
    }

    public void goToMenu(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node) event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Viewer/menuClient.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));

    }

    public void searchCar() {
        String make = carMakeTextField.getText();
        String model = carModelTextField.getText();
        filteredList.clear();
        int index = 0;
        for (Car car : CarData.getInstance().getCarObservableList()) {
            if ( (car.getCarMake().equalsIgnoreCase(make) && car.getCarModel().equalsIgnoreCase(model)) || ( car.getCarMake().equalsIgnoreCase(make) && (model.equalsIgnoreCase("any") || model.equalsIgnoreCase("") ) ) ) {
                filteredList.add(car);
                index++;
            }
        }
        Intent.getInstance().showToast(index+" cars matched found",true);
    }
    public void searchPartial(){
        String make = carMakeTextField.getText();
        String model = carModelTextField.getText();
        make = make.toLowerCase();
        model = model.toLowerCase();
        filteredList.clear();
        int index = 0;
        for (Car car : CarData.getInstance().getCarObservableList()) {
            if ( (car.getCarMake().toLowerCase().contains(make) && car.getCarModel().toLowerCase().contains(model)) || ( car.getCarMake().toLowerCase().contains(make) && (model.equalsIgnoreCase("any") || model.equalsIgnoreCase("") ) ) ) {
                filteredList.add(car);
                index++;
            }
        }
        Intent.getInstance().showToast(index+" cars matched found",true);
    }

}