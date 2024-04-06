package Decorator.Decorator;

import Decorator.Burger.Burger;

public class Cheese extends BurgerDecorator {

    public Cheese(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
    }

    @Override
    public int getPrice() {
        return burgerToBeDecorated.getPrice() + getCheesePrice() ;
    }

    @Override
    public String getOrderDetails() {
        return burgerToBeDecorated.getOrderDetails() +
                "Add-ons: Cheese\n" +
                "\tPrice: "+getCheesePrice()+"\n";
    }

    private int getCheesePrice(){
        return 56;
    }
}
