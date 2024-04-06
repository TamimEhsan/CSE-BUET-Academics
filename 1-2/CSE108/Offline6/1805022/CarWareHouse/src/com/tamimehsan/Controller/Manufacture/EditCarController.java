package com.tamimehsan.Controller.Manufacture;

import com.jfoenix.controls.JFXTextField;
import com.jfoenix.validation.IntegerValidator;
import com.jfoenix.validation.RequiredFieldValidator;
import com.tamimehsan.Model.Car;
import com.tamimehsan.Model.Intent;
import com.tamimehsan.Network.RequestProcessor;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.DatePicker;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Circle;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class EditCarController {
    @FXML
    private JFXTextField carMake;
    @FXML
    private JFXTextField carModel;
    @FXML
    private JFXTextField regNumber;
    @FXML
    private JFXTextField carQuantity;
    @FXML
    private JFXTextField carPrice;
    @FXML
    private ColorPicker colorPicker1;
    @FXML
    private ColorPicker colorPicker2;
    @FXML
    private ColorPicker colorPicker3;
    @FXML
    private DatePicker datePicker;
    @FXML
    private Circle carImage;
    private Car car;
    private int modifyIndex;
    private String defaultImage;
    public void initialize(){
        car = Intent.getInstance().getData();
        modifyIndex = Intent.getInstance().getPosition();
        File file = new File(car.getImage());
        defaultImage = car.getImage();
        if(file!=null && file.exists()) {
            Image image = new Image(file.toURI().toString());
            carImage.setFill(new ImagePattern(image));
        }
        carMake.setText(car.getCarMake());
        carModel.setText(car.getCarModel());
        regNumber.setText(car.getRegistrationNumber());
        carQuantity.setText(car.getQuantity()+"");
        carPrice.setText(car.getPrice()+"");
        colorPicker1.setValue(Color.valueOf(car.getColor1()));
        colorPicker2.setValue(Color.valueOf(car.getColor2()));
        colorPicker3.setValue(Color.valueOf(car.getColor3()));
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        LocalDate localDate = LocalDate.parse(car.getYearMade(), formatter);
        datePicker.setValue(localDate);
        IntegerValidator integerValidator = new IntegerValidator();
        RequiredFieldValidator requiredFieldValidator = new RequiredFieldValidator();
        requiredFieldValidator.setMessage("Can't be empty");
        integerValidator.setMessage("Must be an integer");
        carPrice.getValidators().add(requiredFieldValidator);
        carPrice.getValidators().add(integerValidator);
        carQuantity.getValidators().add(requiredFieldValidator);
        carQuantity.getValidators().add(integerValidator);
        carPrice.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1) {
                if(!t1){
                    carPrice.validate();
                }
            }
        });
        carQuantity.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1) {
                if(!t1){
                    carQuantity.validate();
                }
            }
        });
    }
    public void backToMenu(ActionEvent event) throws IOException {
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node) event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Manufacturer/godown.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void validateInformation(ActionEvent event) throws IOException {
        String carQuantityText = carQuantity.getText();
        String carPriceText = carPrice.getText();
        String color1 = "#"+colorPicker1.getValue().toString().substring(2,8);
        String color2 = "#"+colorPicker2.getValue().toString().substring(2,8);
        String color3 = "#"+colorPicker3.getValue().toString().substring(2,8);
        if( carQuantityText.equals("") || carPriceText.equals("") ){
            carPrice.validate();
            carQuantity.validate();
            return;
        }
        int carPriceInt,carQuantityInt;
        try{
            carPriceInt = Integer.parseInt(carPriceText);
            carQuantityInt = Integer.parseInt(carQuantityText);
        }catch (Exception e){
            carPrice.validate();
            carQuantity.validate();
            return;
        }
        if( carPriceInt<0 ){
            Intent.getInstance().showToast("Price can't be lower than Zero!",false);
            return;
        }
        if( carQuantityInt<0 ){
            Intent.getInstance().showToast("Quantity can't be lower than Zero!",false);
            return;
        }
        Car newCar = new Car(car.getRegistrationNumber(),car.getYearMade(),car.getCarMake(),car.getCarModel(),color1,color2,color3,carPriceInt,carQuantityInt,defaultImage);
        RequestProcessor.getInstance().requestModifyCar(newCar);
        Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("../../View/Manufacturer/godown.fxml"));
        stageTheEventSourceNodeBelongs.setScene(new Scene(root));
    }
    public void editImage(ActionEvent event){
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Upload File Path");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("IMAGE FILES", "*.jpg", "*.png")
        );

        File file = fileChooser.showOpenDialog(((Node) event.getSource()).getScene().getWindow());

        if (file != null) {
            defaultImage = file.getAbsolutePath();
            Image image = new Image(file.toURI().toString());
            carImage.setFill(new ImagePattern(image));
        } else  {
            System.out.println("error"); // or something else
        }
    }
}
