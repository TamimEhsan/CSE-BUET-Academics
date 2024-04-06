package com.tamimehsan.Model;

public class Car {
    private String registrationNumber;
    private String carMake;
    private String carModel;
    private String yearMade;
    private String color1;
    private String color2;
    private String color3;
    private int price;
    private int quantity;
    private String image;

    public Car(String registrationNumber, String yearMade, String carMake, String carModel, String color1, String color2, String color3, int price, int quantity, String image) {
        this.registrationNumber = registrationNumber;
        this.carMake = carMake;
        this.carModel = carModel;
        this.yearMade = yearMade;
        this.color1 = color1;
        this.color2 = color2;
        this.color3 = color3;
        this.price = price;
        this.quantity = quantity;
        this.image = image;
    }

    public Car() {
    }

    public String getRegistrationNumber() {
        return registrationNumber;
    }

    public void setRegistrationNumber(String registrationNumber) {
        this.registrationNumber = registrationNumber;
    }

    public String getYearMade() {
        return yearMade;
    }

    public void setYearMade(String yearMade) {
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

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public String getImage() {
        return image;
    }

    public void setImage(String image) {
        this.image = image;
    }

    @Override
    public String toString() {
        return registrationNumber +
                "," + yearMade +
                "," + carMake +
                "," + carModel +
                "," + color1 +
                "," + color2 +
                "," + color3 +
                "," + price +
                "," + quantity +
                "," + image;
    }
}
