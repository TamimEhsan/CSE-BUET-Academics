package Font;

public class Consolas implements Font{
    @Override
    public String getFont() {
        return "Consolas";
    }

    @Override
    public String toString() {
        return "Font: "+getFont();
    }
}
