package Decorator.Decorator;

import Decorator.Burger.Burger;

public abstract class BurgerDecorator implements Burger {
    protected Burger burgerToBeDecorated;

    public BurgerDecorator(Burger burgerToBeDecorated) {
        this.burgerToBeDecorated = burgerToBeDecorated;
    }

    @Override
    public int getPrice() {
        return burgerToBeDecorated.getPrice();
    }
}
