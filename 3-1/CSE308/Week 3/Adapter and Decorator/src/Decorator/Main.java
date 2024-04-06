package Decorator;


import Decorator.Burger.Burger;
import Decorator.Burger.BurgerFactory;
import Decorator.Decorator.AppetizerDecorator.AppetizerFactory;
import Decorator.Decorator.Cheese;
import Decorator.Decorator.DrinksDecorator.DrinksFactory;

import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        // write your code here

        Burger beefBurger = BurgerFactory.getBurger("beef");
        Burger veggiBurger = BurgerFactory.getBurger("veggi");
        Burger chickenBurger = BurgerFactory.getBurger("chicken");

        Burger beefBurgerWithFrenchFry = AppetizerFactory.getAppetizer("french_fry",beefBurger);
        Burger beefBurgerWithFrenchFryWithCheese = new Cheese(beefBurgerWithFrenchFry);
        Main.printOrderDetails(beefBurgerWithFrenchFryWithCheese);

        Burger veggiBurgerWithOnionRings = AppetizerFactory.getAppetizer("onion_rings",veggiBurger);
        Burger veggiBurgerWithOnionRingswithWater = DrinksFactory.getDrinks("water",veggiBurgerWithOnionRings);
        Main.printOrderDetails(veggiBurgerWithOnionRingswithWater);


        Burger veggiBurgerWithFrenchFry = AppetizerFactory.getAppetizer("french_fry",veggiBurger);
        Burger veggiBurgerWithFrenchFryWithCoke = DrinksFactory.getDrinks("coke",veggiBurgerWithFrenchFry);
        Main.printOrderDetails(veggiBurgerWithFrenchFryWithCoke);

        Burger veggiBurgerWithOnionRingsWithCoffee =  DrinksFactory.getDrinks("coffee",veggiBurgerWithOnionRings);
        Burger veggiBurgerWithOnionRingsWithCoffeeWithWater =  DrinksFactory.getDrinks("water",veggiBurgerWithOnionRingsWithCoffee);
        Main.printOrderDetails(veggiBurgerWithOnionRingsWithCoffeeWithWater);

        Main.printOrderDetails(beefBurger);
    }
    static void  printOrderDetails(Burger burger){
        System.out.println("#########################");
        System.out.println("Order Details\n" +
                "================\n"
                +burger.getOrderDetails());
        System.out.println("-----------------\n" +
                "Total Price: "+burger.getPrice()+"");
        System.out.println("^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    }
}
