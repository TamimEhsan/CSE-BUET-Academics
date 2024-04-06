package com.tamimehsan.Controller;

import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXSnackbar;
import com.jfoenix.controls.JFXSnackbarLayout;
import com.jfoenix.controls.JFXTextField;
import com.jfoenix.validation.RequiredFieldValidator;
import com.tamimehsan.Main;
import com.tamimehsan.Model.Intent;
import com.tamimehsan.Network.RequestProcessor;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.IOException;

public class LoginController {
    @FXML
    private JFXTextField usernameField;
    @FXML
    private JFXPasswordField passwordField;
    @FXML
    private AnchorPane rootPane;
    public void initialize(){
        RequiredFieldValidator requiredFieldValidator = new RequiredFieldValidator();
        requiredFieldValidator.setMessage("Can't be empty");
        usernameField.getValidators().add(requiredFieldValidator);
        usernameField.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1) {
                if(!t1){
                    usernameField.validate();
                }
            }
        });
    }

    public void validateLogin(ActionEvent event) throws IOException {
        String usernmae = usernameField.getText();
        String password = passwordField.getText();
        if( usernmae.equalsIgnoreCase("public") ){
            // go to buy
            Stage stageTheEventSourceNodeBelongs = (Stage) ((Node)event.getSource()).getScene().getWindow();
            Parent root = FXMLLoader.load(getClass().getResource("../View/Viewer/menuClient.fxml"));
            stageTheEventSourceNodeBelongs.setScene(new Scene(root));
            Intent.getInstance().showToast("Welcome to Scarlet!",true);
        } else{
            if( usernmae.equals("") ){
                usernameField.validate();
                return;
            }
            Intent.getInstance().setUserName(usernmae);
            RequestProcessor.getInstance().sendLoginRequest(usernmae,password);
        }
    }
}