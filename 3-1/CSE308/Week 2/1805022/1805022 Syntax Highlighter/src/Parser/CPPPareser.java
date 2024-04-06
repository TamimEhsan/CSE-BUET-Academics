package Parser;

public class CPPPareser implements Parser {
    @Override
    public String getName() {
        return "CPP Parser";
    }
    @Override
    public String toString() {
        return "Parser: "+getName();
    }
}
