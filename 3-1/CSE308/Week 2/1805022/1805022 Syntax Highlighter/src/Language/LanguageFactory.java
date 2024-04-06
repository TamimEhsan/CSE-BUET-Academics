package Language;

public class LanguageFactory {
    public static Language getLanguage(String type){
        if( type == null )
            return null;
        if( type.equalsIgnoreCase("C") )
            return new C();
        else if( type.equalsIgnoreCase("cpp") )
            return new CPP();
        else if( type.equalsIgnoreCase("py") )
            return new Python();
        else return null;
    }
}
