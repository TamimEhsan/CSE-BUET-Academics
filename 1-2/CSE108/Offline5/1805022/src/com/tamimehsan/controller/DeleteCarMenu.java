package com.tamimehsan.controller;

import com.tamimehsan.classes.Car;
import com.tamimehsan.IO.Console;
import com.tamimehsan.data.Database;
import com.tamimehsan.IO.MyColor;

import java.util.List;


public class DeleteCarMenu {
    public void view(){
        System.out.println( "╔══════════════════════════════════════╗" + "\n" +
                            "║     "+ MyColor.ANSI_YELLOW +"Main Menu > Delete Car"+ MyColor.ANSI_RESET +"           ║" + "\n" +
                            "╠══════════════════════════════════════╣" + "\n" +
                            "║   Enter the reg number of the car    ║" + "\n" +
                            "╚══════════════════════════════════════╝");

        String regNumber = Console.getInstance().getInput("Enter Registration Number: ");
        List<Car> car = Database.getInstance().searchCarByRegistrationNumber(regNumber);
        if( car.size() == 0 ){
            Console.getInstance().printError("Given information about the car is not found in the database");
        }else{
            Database.getInstance().deleteCar(car.get(0));
            Console.getInstance().printSuccess( MyColor.ANSI_GREEN, "Success:The car was deleted from the database");
        }
    }
}
