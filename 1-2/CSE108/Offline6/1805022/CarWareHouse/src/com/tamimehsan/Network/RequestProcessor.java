package com.tamimehsan.Network;

import com.tamimehsan.Main;
import com.tamimehsan.Model.Car;
import com.tamimehsan.Model.CarData;
import com.tamimehsan.Model.Intent;
import com.tamimehsan.Model.TransferObject;
import javafx.application.Platform;

public class RequestProcessor {
    private static RequestProcessor instance;

    private RequestProcessor() {
    }

    public static RequestProcessor getInstance() {
        if (instance == null) {
            instance = new RequestProcessor();
        }
        return instance;
    }

    public void sendLoginRequest(String username, String password) {
        TransferObject transferObject = new TransferObject();
        transferObject.setRequestType(1);
        transferObject.setUsername(username);
        transferObject.setPassword(password);
        Connection.getInstance().send(transferObject);
    }

    public void processRequest(TransferObject request) {
        switch (request.getRequestType()) {
            case 2:
                processLogin(request);
                break;
            case 11:
                CarData.getInstance().setCarData(request.getCarsData());
                break;
            case 12:
                processAddCarRequest(request);
                break;
            case 22:
                processDeleteRequest(request);
                break;
            case 24:
                processModifyCarRequest(request);
                break;
            case 404:
                processError(request);
                break;
            case 200:
                processSusccess(request);
                break;
            default:
        }

    }

    public void processLogin(TransferObject transferObject) {
        Platform.runLater(() -> {
            if (transferObject.isConfirmed()) {
                System.out.println("confirmed");
                Intent.getInstance().confirmLogin();
                Intent.getInstance().showToast("Welcome to Scarlet!", true);
            } else {
                Intent.getInstance().showToast("The username or password \n doesn't match or exist", false);
            }
        });
    }

    public void requestBuyCar(String regNumber) {
        TransferObject transferObject = new TransferObject();
        transferObject.setRequestType(31);
        transferObject.setCar(regNumber);
        Connection.getInstance().send(transferObject);
    }

    public void requestDeleteCar(int index) {
        TransferObject transferObject = new TransferObject();
        transferObject.setRequestType(22);
        transferObject.setModifyPosition(index);
        Connection.getInstance().send(transferObject);
    }

    public void requestAddCar(Car car) {
        TransferObject request = new TransferObject();
        request.setRequestType(23);
        request.setCar(car.toString());
        Connection.getInstance().send(request);
    }

    public void requestModifyCar(Car car) {
        TransferObject transferObject = new TransferObject();
        transferObject.setRequestType(24);
        transferObject.setCar(car.toString());
        Connection.getInstance().send(transferObject);
    }

    public void processDeleteRequest(TransferObject request) {
        Platform.runLater(
                () -> CarData.getInstance().deleteCarAtIndex(request.getModifyPosition())
        );
    }

    public void processModifyCarRequest(TransferObject request) {
        CarData.getInstance().modifyCar(request.getCar());
    }

    public void processAddCarRequest(TransferObject request) {
        CarData.getInstance().addNewCar(request.getCar());
    }

    public void processError(TransferObject request) {
        Platform.runLater(() -> Intent.getInstance().showToast(request.getCar(), false));
    }

    public void processSusccess(TransferObject request) {
        Platform.runLater(() -> {
            Intent.getInstance().showToast(request.getCar(), true);
        });
    }
}
