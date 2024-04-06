package Language;

import Parser.Parser;
import Parser.CPPPareser;

public class CPP implements Language {
    Parser parser;
    public CPP(){
        parser = new CPPPareser();
    }

    @Override
    public String getName() {
        return "CPP";
    }
    @Override
    public String toString() {
        return "Language: " + getName() + "\n" + parser;
    }
}
