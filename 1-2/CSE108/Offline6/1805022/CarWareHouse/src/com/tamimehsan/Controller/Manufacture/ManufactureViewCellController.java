package com.tamimehsan.Controller.Manufacture;

import com.jfoenix.controls.JFXButton;
import com.tamimehsan.Model.Intent;
import com.tamimehsan.Network.RequestProcessor;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.ImagePattern;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import com.tamimehsan.Model.Car;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class ManufactureViewCellController extends ListCell<Car> {
    @FXML
    private Label carMake;
    @FXML
    private Label carModel;
    @FXML
    private Label yearMade;
    @FXML
    private Label quantity;
    @FXML
    private Label price;
    @FXML
    private Label regNumber;
    @FXML
    private AnchorPane pane;
    @FXML
    private ImageView stockEnd;
    @FXML
    private Circle circleImage;
    @FXML
    private Circle colorCircle1;
    @FXML
    private Circle colorCircle2;
    @FXML
    private Circle colorCircle3;
    private FXMLLoader mLLoader;
    private Car car;

    @Override
    protected void updateItem(Car car, boolean empty) {
        super.updateItem(car, empty);
        int index = getIndex();
        if (empty || car == null) {
            setText(null);
            setGraphic(null);
        } else {
            if (mLLoader == null) {
                mLLoader = new FXMLLoader(getClass().getResource("../../View/Manufacturer/listViewCellManufacture.fxml"));
                mLLoader.setController(this);
                try {
                    mLLoader.load();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            this.car = car;
            carMake.setText(car.getCarMake());
            carModel.setText(car.getCarModel());
            yearMade.setText(car.getYearMade());
            quantity.setText(car.getQuantity() + "");
            regNumber.setText(car.getRegistrationNumber());
            if (car.getQuantity() == 0) {
                stockEnd.setOpacity(1);
            } else {
                stockEnd.setOpacity(0);
            }
            price.setText("$" + car.getPrice());
            colorCircle1.setFill(Paint.valueOf(car.getColor1()));
            colorCircle2.setFill(Paint.valueOf(car.getColor2()));
            colorCircle3.setFill(Paint.valueOf(car.getColor3()));
            File file = new File(car.getImage());
            if (file != null && file.exists()) {
                Image image = new Image(file.toURI().toString());
                circleImage.setFill(new ImagePattern(image));
            }
            setText(null);
            setGraphic(pane);
        }
    }

    public void editCar(ActionEvent event) throws IOException {
        Intent.getInstance().setData(car);
        Intent.getInstance().setPosition(getIndex());
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node) event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Manufacturer/editCar.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }

    public void deleteCar() {
        RequestProcessor.getInstance().requestDeleteCar(getIndex());
    }
}