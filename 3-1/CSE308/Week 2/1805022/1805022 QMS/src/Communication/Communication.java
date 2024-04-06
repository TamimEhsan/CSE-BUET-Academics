package Communication;

public abstract class Communication {
    String name;
    int price;
    String communicator;
    public int getPrice(){
        return price;
    }

    @Override
    public String toString() {
        return "Communication{" +
                "name='" + name + "\' , " +
                "module='" + communicator + '\'' +
                '}';
    }
}
