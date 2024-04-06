package DisplayUnit;

public class DisplayUnitFactory {
    public static DisplayUnit getDisplayUnit(String packageName){
        if( packageName == null )
            return null;
        if( packageName.equalsIgnoreCase("Deluxe") )
            return new Deluxe();
        else if( packageName.equalsIgnoreCase("Optimal") )
            return new Optimal();
        else if( packageName.equalsIgnoreCase("Poor") )
            return new Poor();
        else return null;
    }
}

