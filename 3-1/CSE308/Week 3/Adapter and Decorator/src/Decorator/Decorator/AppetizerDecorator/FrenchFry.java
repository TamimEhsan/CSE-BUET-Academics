package Decorator.Decorator.AppetizerDecorator;

import Decorator.Burger.Burger;

public class FrenchFry extends Appetizer {
    public FrenchFry(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
    }

    @Override
    public String getOrderDetails() {
        return burgerToBeDecorated.getOrderDetails() +
                "Appetizer: French Fry\n" +
                "\tPrice: "+getAppetizerPrice()+"\n";
    }

    @Override
    public int getAppetizerPrice() {
        return 129;
    }
}
