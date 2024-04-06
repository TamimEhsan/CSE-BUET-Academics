package Builder;

import Communication.Communication;
import Display.Display;
import Processor.Processor;

public class Product {
    private Processor processor;
    private Display display;
    private Communication communication;
    private int displayUnitNumber;

    private int YEARLY_COST = 1200;
    private int WEB_BASED_PLATFORM_PRICE = 10000;

    public Product(ProductBuilder productBuilder){
        processor = productBuilder.getQmsPackage().getProcessor();
        display = productBuilder.getQmsPackage().getDisplay();
        communication = productBuilder.getCommunication();
        displayUnitNumber = productBuilder.getDisplayUnitNumber();
    }

    public void show(){
        System.out.println(this);
    }

    public int getPrice(){
        return ( processor.getPrice() + display.getPrice() ) * displayUnitNumber+
                communication.getPrice()+
                YEARLY_COST+
                WEB_BASED_PLATFORM_PRICE;
    }

    @Override
    public String toString() {
        return "Product{" + "\n" +
                "  processor=" + processor + ",\n" +
                "  display=" + display + ",\n" +
                "  communication=" + communication + ",\n" +
                "  displayUnitNumber=" + displayUnitNumber + "\n" +
                '}';
    }
}
