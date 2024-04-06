package com.tamimehsan.Controller.Manufacture;

import com.jfoenix.controls.JFXTextField;
import com.jfoenix.validation.IntegerValidator;
import com.jfoenix.validation.RequiredFieldValidator;
import com.tamimehsan.Main;
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
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Circle;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class AddCarController {
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
    private String defaultImage = "G:\\JavaFX\\CarWareHouse\\src\\com\\tamimehsan\\resources\\auto_car-16.jpg";
    public void initialize(){
        datePicker.setValue(LocalDate.now());

        File file = new File(defaultImage);
        if(file!=null && file.exists()) {
            Image image = new Image(file.toURI().toString());
            carImage.setFill(new ImagePattern(image));
        }
        IntegerValidator integerValidator = new IntegerValidator();
        RequiredFieldValidator requiredFieldValidator = new RequiredFieldValidator();
        carPrice.getValidators().add(integerValidator);
        carPrice.getValidators().add(requiredFieldValidator);
        carQuantity.getValidators().add(integerValidator);
        carQuantity.getValidators().add(requiredFieldValidator);
        carMake.getValidators().add(requiredFieldValidator);
        carModel.getValidators().add(requiredFieldValidator);
        regNumber.getValidators().add(requiredFieldValidator);
        integerValidator.setMessage("Must be a number");
        requiredFieldValidator.setMessage("Can't be empty");
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
        carMake.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1) {
                if(!t1){
                    carMake.validate();
                }
            }
        });
        carModel.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1) {
                if(!t1){
                    carModel.validate();
                }
            }
        });
        regNumber.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1) {
                if(!t1){
                    regNumber.validate();
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
        String carMakeText = carMake.getText();
        String carModelText = carModel.getText();
        String regNumberText = regNumber.getText();
        String carQuantityText = carQuantity.getText();
        String carPriceText = carPrice.getText();
        String color1 = "#"+colorPicker1.getValue().toString().substring(2,8);
        String color2 = "#"+colorPicker2.getValue().toString().substring(2,8);
        String color3 = "#"+colorPicker3.getValue().toString().substring(2,8);
        String date = datePicker.getValue().format(DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        if( carMakeText.equals("") || carModelText.equals("") || regNumberText.equals("") || carQuantityText.equals("") || carPriceText.equals("") ){
            carMake.validate();
            carModel.validate();
            regNumber.validate();
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
        Car car = new Car(regNumberText,date,carMakeText,carModelText,color1,color2,color3,carPriceInt,carQuantityInt,defaultImage);
        RequestProcessor.getInstance().requestAddCar(car);
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
            // pickUpPathField it's your TextField fx:id
           // pickUpPathField.setText(file.getPath());
           // System.out.println(file.getAbsolutePath());
            defaultImage = file.getAbsolutePath();
            Image image = new Image(file.toURI().toString());
            carImage.setFill(new ImagePattern(image));
        } else  {
            System.out.println("error"); // or something else
        }
    }
}
