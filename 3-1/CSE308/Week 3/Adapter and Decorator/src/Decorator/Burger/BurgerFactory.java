package Decorator.Burger;

public class BurgerFactory {
    public static Burger getBurger(String type){
        if( type.equalsIgnoreCase("veggi") ){
            return new VeggiBurger();
        }else if( type.equalsIgnoreCase("beef") ){
            return new BeefBurger();
        }else if( type.equalsIgnoreCase("chicken") ){
            return new ChickenBurger();
        }else{
            return null;
        }
    }
}
