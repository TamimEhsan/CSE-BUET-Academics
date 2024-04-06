package com.tamimehsan.Model;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.util.List;

public class CarData {
    private static CarData instance;

    private ObservableList<Car> carObservableList;

    private CarData(){
        carObservableList= FXCollections.observableArrayList();
    }
    public static CarData getInstance(){
        if( instance == null ){
            instance = new CarData();
        }
        return instance;
    }
    public ObservableList<Car> getCarObservableList(){
        return carObservableList;
    }

    public void setCarObservableList(ObservableList<Car> carObservableList) {
        this.carObservableList = carObservableList;
    }
    public void setCarData(List<String> cars){
        for(String data:cars){
            Car car = getCarFromString(data);
            carObservableList.add(car);
        }
    }
    public Car getCarFromString(String data){
        String details[] = data.split(",");
        Car car = new Car(details[0],details[1],details[2],details[3],details[4],details[5],details[6],Integer.parseInt(details[7]),Integer.parseInt(details[8]),details[9]);
        return car;
    }
    public void updateCarAtIndex(String data,int index){
        Car car = getCarFromString(data);
        carObservableList.set(index,car);
        if( Intent.getInstance().getCarListInterface()!=null ) {
            Intent.getInstance().getCarListInterface().onListUpdated();
        }
    }
    public void deleteCarAtIndex(int index){
        carObservableList.remove(index);
        if( Intent.getInstance().getCarListInterface()!=null ) {
            Intent.getInstance().getCarListInterface().onListUpdated();
        }
    }
    public void addNewCar(String data){
        Car car = getCarFromString(data);
        carObservableList.add(car);
        if( Intent.getInstance().getCarListInterface()!=null ) {
            Intent.getInstance().getCarListInterface().onListUpdated();
        }
    }
    public void modifyCar(String data){
        Car car = getCarFromString(data);
        int index = -1;
        for(int i=0;i<carObservableList.size();i++){
            Car thisCar = carObservableList.get(i);
            if( thisCar.getRegistrationNumber().equals(car.getRegistrationNumber()) ){
                index = i;
                break;
            }
        }
        if( index == -1 ){
            return;
        }
        int finalIndex = index;
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                carObservableList.set(finalIndex,car);
                if( Intent.getInstance().getCarListInterface()!=null ) {
                    Intent.getInstance().getCarListInterface().onListUpdated();
                }
            }
        });
    }
}
