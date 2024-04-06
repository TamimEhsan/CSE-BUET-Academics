package Language;

import Parser.Parser;
import Parser.CParser;

public class C implements Language {
    Parser parser;
    public C(){
        parser = new CParser();
    }

    @Override
    public String getName() {
        return "C";
    }

    @Override
    public String toString() {
        return "Language: " + getName() + "\n" + parser;
    }
}
