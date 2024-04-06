package com.tamimehsan.IO;

import com.tamimehsan.classes.Car;

import java.util.List;
import java.util.Scanner;

public class Console {
    public static Console instance;
    private Scanner scanner;
    private Console(){
        scanner = new Scanner(System.in);
    }
    public static Console getInstance() {
        if( instance == null ){
            instance = new Console();
        }
        return instance;
    }

    public int getOption(){
        System.out.print("Enter Selected Option: ");
        String s = scanner.nextLine();
        try{
            int option = Integer.parseInt(s);
            return option;
        } catch (Exception e){
            return -1;
        }
    }
    public void printError(String err){
        System.out.println(MyColor.ANSI_RED+"\n⚠ Error: "+ err +'\n'+MyColor.ANSI_RESET);
    }
    public void printCars(List<Car> cars){
        if( cars.size() == 0 ){
            printError("No such car with this Car Make and Car Model");
        } else{
            System.out.println(MyColor.ANSI_BLUE+  "############################################################");
            System.out.println("xxxxxxxxxxxxxxxxxxxxxx Selected Cars xxxxxxxxxxxxxxxxxxxxxxx");
            System.out.println("############################################################"+MyColor.ANSI_GREEN);
            for(Car car:cars){
                printCar(car);
                System.out.println(MyColor.ANSI_BLUE+"############################################################"+MyColor.ANSI_GREEN);
            }
            System.out.print(MyColor.ANSI_RESET);
        }
    }
    public void printCar(Car car){
        System.out.println(car.getCarMake()+" - "+car.getCarModel()+" ("+car.getYearMade()+")\n"+
                "Registration Number: "+car.getRegistrationNumber()+"\n"+
                "Color: "+car.getColor1()+" "+car.getColor2()+" "+car.getColor3()+"\n"+
                "Price: $"+car.getPrice());
    }

    public void printSuccess(String color,String message){
        System.out.println(color+"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓");
        int sz = message.length();
        int offset = (56 - sz)/2;
        for( int i = 0; i<offset;i++){
            System.out.print("▓");
        }
        System.out.print(message);
        for( int i = 0; i<offset;i++){
            System.out.print("▓");
        }
        System.out.println("\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"+MyColor.ANSI_RESET);
    }
    public String getInput(String prompt){
        System.out.print(prompt);
        String input = scanner.nextLine();
        return input;
    }
    public void closeScanner(){
        scanner.close();
    }

}
