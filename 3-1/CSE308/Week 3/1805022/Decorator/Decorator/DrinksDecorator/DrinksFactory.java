package Decorator.Decorator.DrinksDecorator;

import Decorator.Burger.BeefBurger;
import Decorator.Burger.Burger;
import Decorator.Burger.ChickenBurger;
import Decorator.Burger.VeggiBurger;

public class DrinksFactory {
    public static Burger getDrinks(String type,Burger burger){
        if( type.equalsIgnoreCase("coffee") ){
            return new Coffee(burger);
        }else if( type.equalsIgnoreCase("water") ){
            return new Water(burger);
        }else if( type.equalsIgnoreCase("coke") ){
            return new Coke(burger);
        }else{
            return null;
        }
    }
}
