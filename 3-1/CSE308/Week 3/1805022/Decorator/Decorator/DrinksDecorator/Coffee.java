package Decorator.Decorator.DrinksDecorator;

import Decorator.Burger.Burger;

public class Coffee extends Drinks {
    public Coffee(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
    }

    @Override
    public String getOrderDetails() {
        return burgerToBeDecorated.getOrderDetails() +
                "Drinks: Coffee\n" +
                "\tPrice: "+getDrinksPrice()+"\n";
    }
    @Override
    public int getDrinksPrice() {
        return 149;
    }
}
