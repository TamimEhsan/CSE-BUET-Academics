package Parser;

public class PythonParser implements Parser {
    @Override
    public String getName() {
        return "Python Parser";
    }
    @Override
    public String toString() {
        return "Parser: "+getName();
    }
}
