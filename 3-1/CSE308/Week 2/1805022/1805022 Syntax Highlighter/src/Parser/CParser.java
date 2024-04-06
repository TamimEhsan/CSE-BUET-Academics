package Parser;

public class CParser implements Parser {
    @Override
    public String getName() {
        return "C Parser";
    }

    @Override
    public String toString() {
        return "Parser: "+getName();
    }
}
