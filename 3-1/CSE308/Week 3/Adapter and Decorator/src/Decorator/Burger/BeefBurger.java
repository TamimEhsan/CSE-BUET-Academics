package Decorator.Burger;

public class BeefBurger implements Burger {
    @Override
    public int getPrice() {
        return 229;
    }

    @Override
    public String getOrderDetails() {
        return "Burger: Beef Burger \n" +
                "\tPrice: "+getPrice()+"\n";
    }
}
