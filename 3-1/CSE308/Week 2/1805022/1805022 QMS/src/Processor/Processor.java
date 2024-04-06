package Processor;

public abstract class Processor {
    String name;
    int price;

    public int getPrice(){
        return price;
    }
    @Override
    public String toString() {
        return "Microcontroller{" +
                "name='" + name + '\'' +
                '}';
    }
}
