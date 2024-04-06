package Decorator.Decorator.DrinksDecorator;

import Decorator.Burger.Burger;

public class Coke extends Drinks {
    public Coke(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
    }

    @Override
    public String getOrderDetails() {
        return burgerToBeDecorated.getOrderDetails() +
                "Drinks: Coke\n" +
                "\tPrice: "+getDrinksPrice()+"\n";
    }

    @Override
    public int getDrinksPrice() {
        return 20;
    }
}
