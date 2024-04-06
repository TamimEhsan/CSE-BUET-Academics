package Display;

public abstract class Display {
    String name;
    int price;

    public int getPrice(){
        return price;
    }
    @Override
    public String toString() {
        return "Display{" +
                "name='" + name + '\'' +
                '}';
    }
}
