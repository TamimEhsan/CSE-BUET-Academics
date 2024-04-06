package Decorator.Decorator.AppetizerDecorator;

import Decorator.Burger.BeefBurger;
import Decorator.Burger.Burger;
import Decorator.Burger.ChickenBurger;
import Decorator.Burger.VeggiBurger;

public class AppetizerFactory {
    public static Burger getAppetizer(String type,Burger burger){
        if( type.equalsIgnoreCase("French_fry") ){
            return new FrenchFry(burger);
        }else if( type.equalsIgnoreCase("onion_rings") ){
            return new OnionRings(burger);
        }else{
            return null;
        }
    }
}
