package com.tamimehsan.Network;

import com.tamimehsan.Data.Database;
import com.tamimehsan.Model.Car;
import com.tamimehsan.Model.TransferObject;

import java.util.ArrayList;
import java.util.List;

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

    public TransferObject sendAllCarRequest(List<Car> cars) {
        TransferObject request = new TransferObject();
        request.setRequestType(11);
        List<String> carData = new ArrayList<>();
        for (Car car : cars) {
            carData.add(car.toString());
        }
        request.setCarsData(carData);
        return request;
    }

    public void sendLoginConfirmationRequest(boolean isConfirmed, Client client) {
        TransferObject request = new TransferObject();
        request.setRequestType(2);
        request.setConfirmed(isConfirmed);
        client.send(request);
    }

    public void processRequest(TransferObject request, Client client) {
        switch (request.getRequestType()) {
            case 31:
                processBuyCarRequest(request, client);
                break;
            case 1:
                processLogInCredentialRequest(request, client);
                break;
            case 22:
                processDeleteCarRequest(request, client);
                break;
            case 23:
                processAddCarRequest(request, client);
                break;
            case 24:
                processModifyCarRequest(request, client);
                break;
            default:
        }
    }

    public void processBuyCarRequest(TransferObject request, Client client) {
        Car car = Database.getInstance().assertBuyCar(request.getCar());
        if (car != null) {
            request.setRequestType(24);
            request.setCar(car.toString());
            Server.getInstance().broadcast(request);
            TransferObject success = new TransferObject();
            success.setRequestType(200);
            success.setCar("Your order is successful");
            client.send(success);
        } else {
            TransferObject error = new TransferObject();
            error.setRequestType(404);
            error.setCar("Your order is denied");
            client.send(error);
        }
    }

    public void processDeleteCarRequest(TransferObject request, Client client) {
        Database.getInstance().deleteCar(request.getModifyPosition());
        Server.getInstance().broadcast(request);
        TransferObject success = new TransferObject();
        success.setRequestType(200);
        success.setCar("Successfully deleted car");
        client.send(success);
    }

    public void processAddCarRequest(TransferObject request, Client client) {
        Car car = Database.getInstance().addCar(request.getCar());
        if (car != null) {
            request.setRequestType(12);
            Server.getInstance().broadcast(request);
            TransferObject success = new TransferObject();
            success.setRequestType(200);
            success.setCar("Successfully added car");
            client.send(success);
        } else {
            request.setRequestType(404);
            request.setCar("Couldn't add car. May be car already exists");
            client.send(request);
        }
    }

    public void processModifyCarRequest(TransferObject request, Client client) {
        Car car = Database.getInstance().modifyCar(request.getCar());
        if (car != null) {
            Server.getInstance().broadcast(request);
            TransferObject success = new TransferObject();
            success.setRequestType(200);
            success.setCar("Successfully modified car");
            client.send(success);
        } else {
            request.setRequestType(404);
            request.setCar("Couldn't modify or find car!");
            client.send(request);
        }
    }

    public void processLogInCredentialRequest(TransferObject request, Client client) {
        String username = request.getUsername();
        String password = request.getPassword();
        if (Database.getInstance().validateUser(username, password)) {
            sendLoginConfirmationRequest(true, client);
        } else {
            sendLoginConfirmationRequest(false, client);
        }
    }
}
