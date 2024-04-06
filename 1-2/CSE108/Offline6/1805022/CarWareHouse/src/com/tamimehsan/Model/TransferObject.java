package com.tamimehsan.Model;

import java.io.Serializable;
import java.util.List;

public class TransferObject implements Serializable {
    private static final long serialVersionUID = 1L;
    private int requestType;
    private List<String> carsData;
    private String car;
    // Login Credentials
    // Request log in ; request type 1
    private String username;
    private String password;
    // data will have user name and password
    // Response log in;  request type 2
    private boolean confirmed;
    // Sending and receiving car infos, data stored in data
    // Send the whole array list at firs; request type 11
    // Send a new car that was added; request type 12

    // Modifying current information
    // Decrement the amount of requested position by changedAmount; request type 21
    private int modifyPosition;
    private int changeAmount;

    // delete car
    // request type 22
    // modifyposition

    // add new Car
    // request type 23
    // date in string car

    // Modify other informations
    // Just send the whole data =_=; request type 24
    // position to be changed => modify position
    // data will be stored in car

    // Ordering a car; request type 31
    // by registration number or index :/
    private int indexToBuy;


    public int getRequestType() {
        return requestType;
    }

    public void setRequestType(int requestType) {
        this.requestType = requestType;
    }

    public List<String> getCarsData() {
        return carsData;
    }

    public void setCarsData(List<String> carsData) {
        this.carsData = carsData;
    }

    public String getCar() {
        return car;
    }

    public void setCar(String car) {
        this.car = car;
    }

    public boolean isConfirmed() {
        return confirmed;
    }

    public void setConfirmed(boolean confirmed) {
        this.confirmed = confirmed;
    }

    public int getModifyPosition() {
        return modifyPosition;
    }

    public void setModifyPosition(int modifyPosition) {
        this.modifyPosition = modifyPosition;
    }

    public int getChangeAmount() {
        return changeAmount;
    }

    public void setChangeAmount(int changeAmount) {
        this.changeAmount = changeAmount;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public int getIndexToBuy() {
        return indexToBuy;
    }

    public void setIndexToBuy(int indexToBuy) {
        this.indexToBuy = indexToBuy;
    }
}
