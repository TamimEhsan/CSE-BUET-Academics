package com.tamimehsan.controller;

import com.tamimehsan.classes.Car;
import com.tamimehsan.IO.Console;
import com.tamimehsan.data.Database;
import com.tamimehsan.IO.MyColor;
import java.util.List;


public class SearchMenu {

    public void view(){
        boolean gameLoop = false;
        while(!gameLoop){
            gameLoop = showOptionMenu();
        }
    }

    public boolean showOptionMenu(){
        //"+ MyColor.ANSI_YELLOW +"Main Menu > Search Car"+ MyColor.ANSI_RESET +"
        System.out.println( "╔════════════════════════════════════════╗" + "\n" +
                            "║          "+ MyColor.ANSI_YELLOW +"Main Menu > Search Car"+ MyColor.ANSI_RESET +"        ║" + "\n" +
                            "╠════════════════════════════════════════╣" + "\n" +
                            "║ How would you like to search the car?  ║" + "\n" +
                            "║      (1) By registration number        ║" + "\n" +
                            "║      (2) By Car make and Car Model     ║" + "\n" +
                            "║      (3) Back to Main Menu             ║" + "\n" +
                            "╚════════════════════════════════════════╝");

        int option = Console.getInstance().getOption();
        switch(option){
            case 1:
                getRegNumber();
                break;
            case 2:
                getCarMakeModel();
                break;
            case 3:
                break;
            default:
                Console.getInstance().printError("Unknown option");
                return false;
        }
        return true;
    }

    public void getRegNumber(){
        System.out.println( "╔══════════════════════════════════════════════╗" + "\n" +
                            "║  "+ MyColor.ANSI_YELLOW +"Main Menu > Search Car > Reg Number"+ MyColor.ANSI_RESET +"         ║" + "\n" +
                            "╠══════════════════════════════════════════════╣" + "\n" +
                            "║ What is the registration number of the car?  ║" + "\n" +
                            "╚══════════════════════════════════════════════╝");

        String regNumber = Console.getInstance().getInput("Enter Registration Number: ");
        List<Car> car = Database.getInstance().searchCarByRegistrationNumber(regNumber);
        Console.getInstance().printCars(car);
    }
    public void getCarMakeModel(){
        System.out.println( "╔══════════════════════════════════════════════╗" + "\n" +
                            "║  "+ MyColor.ANSI_YELLOW +"Main Menu > Search Car > Car Make & Model"+ MyColor.ANSI_RESET +"   ║" + "\n" +
                            "╠══════════════════════════════════════════════╣" + "\n" +
                            "║ What is the car make of the car?             ║");

        String carMake = Console.getInstance().getInput("Enter Car Make: ");
        System.out.println( "║ What's the car model of your car?            ║" + "\n" +
                            "║ (any for any car under the above make)       ║");

        String carModel = Console.getInstance().getInput("Enter Car Model: ");
        System.out.println( "╚══════════════════════════════════════════════╝");
        List<Car> cars =  Database.getInstance().searchByMadeAndMake(carMake,carModel);
        Console.getInstance().printCars(cars);
    }

}
