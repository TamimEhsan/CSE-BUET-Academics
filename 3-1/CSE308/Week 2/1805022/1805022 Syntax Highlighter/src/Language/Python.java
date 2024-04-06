package Language;

import Parser.Parser;
import Parser.PythonParser;

public class Python implements Language {
    Parser parser;
    public Python(){
        parser = new PythonParser();
    }

    @Override
    public String getName() {
        return "Python";
    }
    @Override
    public String toString() {
        return "Language: " + getName() + "\n" + parser;
    }
}
