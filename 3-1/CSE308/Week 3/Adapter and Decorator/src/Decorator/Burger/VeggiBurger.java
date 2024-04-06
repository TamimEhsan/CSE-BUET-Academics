package Decorator.Burger;

public class VeggiBurger implements Burger {
    @Override
    public int getPrice() {
        return 299;
    }
    @Override
    public String getOrderDetails() {
        return "Burger: Veggi Burger \n" +
                "\tPrice: "+getPrice()+"\n";
    }
}
