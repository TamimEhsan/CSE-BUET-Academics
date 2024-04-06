package com.tamimehsan.classes;

public class Car {
    private String registrationNumber;
    private int yearMade;
    private String color1;
    private String color2;
    private String color3;
    private String carMake;
    private String carModel;
    private int price;


    public Car(String registrationNumber, int yearMade, String color1, String color2, String color3, String carMake, String carModel, int price) {
        this.registrationNumber = registrationNumber;
        this.yearMade = yearMade;
        this.color1 = color1;
        this.color2 = color2;
        this.color3 = color3;
        this.carMake = carMake;
        this.carModel = carModel;
        this.price = price;
    }

    public String getRegistrationNumber() {
        return registrationNumber;
    }

    public void setRegistrationNumber(String registrationNumber) {
        this.registrationNumber = registrationNumber;
    }

    public int getYearMade() {
        return yearMade;
    }

    public void setYearMade(int yearMade) {
        this.yearMade = yearMade;
    }

    public String getColor1() {
        return color1;
    }

    public void setColor1(String color1) {
        this.color1 = color1;
    }

    public String getColor2() {
        return color2;
    }

    public void setColor2(String color2) {
        this.color2 = color2;
    }

    public String getColor3() {
        return color3;
    }

    public void setColor3(String color3) {
        this.color3 = color3;
    }

    public String getCarMake() {
        return carMake;
    }

    public void setCarMake(String carMake) {
        this.carMake = carMake;
    }

    public String getCarModel() {
        return carModel;
    }

    public void setCarModel(String carModel) {
        this.carModel = carModel;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return registrationNumber +
                "," + yearMade +
                "," + color1 +
                "," + color2 +
                "," + color3 +
                "," + carMake +
                "," + carModel +
                "," + price;
    }
}
