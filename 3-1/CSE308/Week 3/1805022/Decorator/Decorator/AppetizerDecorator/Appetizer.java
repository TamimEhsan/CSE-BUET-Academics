package Decorator.Decorator.AppetizerDecorator;

import Decorator.Burger.Burger;
import Decorator.Decorator.BurgerDecorator;

public abstract class Appetizer extends BurgerDecorator {
//    protected Burger burgerToBeDecorated;

    public Appetizer(Burger burgerToBeDecorated) {
        super(burgerToBeDecorated);
//        this.burgerToBeDecorated = burgerToBeDecorated;
    }

    @Override
    public int getPrice() {
        return burgerToBeDecorated.getPrice() + getAppetizerPrice();
    }

    @Override
    public abstract String getOrderDetails();

    public abstract int getAppetizerPrice();
}
