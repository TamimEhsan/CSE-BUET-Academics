package Font;



public class FontFactory {
    public static Font getFont(String type){
        if( type == null )
            return null;
        if( type.equalsIgnoreCase("C") )
            return new CourierNew();
        else if( type.equalsIgnoreCase("cpp") )
            return new Monaco();
        else if( type.equalsIgnoreCase("py") )
            return new Consolas();
        else return null;
    }
}
