package Font;

public class CourierNew implements Font {
    @Override
    public String getFont() {
        return "Courier New";
    }

    @Override
    public String toString() {
        return "Font: "+getFont();
    }
}
