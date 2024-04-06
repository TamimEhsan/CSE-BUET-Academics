package Decorator.Decorator.DrinksDecorator;

import Decorator.Burger.Burger;

public class Water extends Drinks {
    public Water(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
    }

    @Override
    public String getOrderDetails() {
        return burgerToBeDecorated.getOrderDetails() +
                "Drinks: Water\n" +
                "\tPrice: "+getDrinksPrice()+"\n";
    }

    @Override
    public int getDrinksPrice() {
        return 15;
    }

}
