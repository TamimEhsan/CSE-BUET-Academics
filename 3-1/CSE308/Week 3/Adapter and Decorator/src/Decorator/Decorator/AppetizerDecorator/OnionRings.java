package Decorator.Decorator.AppetizerDecorator;

import Decorator.Burger.Burger;

public class OnionRings extends Appetizer {
    public OnionRings(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
    }

    @Override
    public int getAppetizerPrice() {
        return 119;
    }

    @Override
    public String getOrderDetails() {
        return burgerToBeDecorated.getOrderDetails() +
                "Appetizer: Onion Rings\n" +
                "\tPrice: "+getAppetizerPrice()+"\n";
    }
}
