package Decorator.Burger;

public class ChickenBurger implements Burger {
    @Override
    public int getPrice() {
        return 219;
    }

    @Override
    public String getOrderDetails() {
        return "Burger: Chicken Burger \n" +
                "\tPrice: "+getPrice()+"\n";
    }
}
