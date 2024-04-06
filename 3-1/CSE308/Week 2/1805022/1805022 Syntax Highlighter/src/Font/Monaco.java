package Font;

public class Monaco implements Font {


    @Override
    public String getFont() {
        return "Monaco";
    }

    @Override
    public String toString() {
        return "Font: "+getFont();
    }
}
