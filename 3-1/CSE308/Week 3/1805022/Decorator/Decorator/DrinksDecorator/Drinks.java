package Decorator.Decorator.DrinksDecorator;

import Decorator.Burger.Burger;
import Decorator.Decorator.BurgerDecorator;

public abstract class Drinks extends BurgerDecorator {
//    protected Burger burgerToBeDecorated;

    public Drinks(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
//        this.burgerToBeDecorated = burgerToBeDecorated;
    }

    @Override
    public int getPrice() {
        return burgerToBeDecorated.getPrice() + getDrinksPrice();
    }
    @Override
    public abstract String getOrderDetails();
    public abstract int getDrinksPrice();
}
