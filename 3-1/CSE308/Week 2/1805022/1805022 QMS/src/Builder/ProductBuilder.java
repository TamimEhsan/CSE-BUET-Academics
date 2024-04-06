package Builder;

import Communication.Communication;
import Communication.CommunicationFactory;
import DisplayUnit.DisplayUnit;
import DisplayUnit.DisplayUnitFactory;

public class ProductBuilder {

    private DisplayUnit displayUnit;
    private Communication communication;
    private int displayUnitNumber;

    public ProductBuilder setPackage(String type){
        displayUnit = DisplayUnitFactory.getDisplayUnit(type);
        return this;
    }
    public ProductBuilder setCommunication(String type){
        communication = CommunicationFactory.getCommunication(type);
        return this;
    }
    public ProductBuilder setDisplayUnit(int displayUnitNumber){
        this.displayUnitNumber = displayUnitNumber;
        return this;
    }

    public DisplayUnit getQmsPackage() {
        return displayUnit;
    }

    public Communication getCommunication() {
        return communication;
    }

    public int getDisplayUnitNumber() {
        return displayUnitNumber;
    }

    public Product getProduct(){
        return new Product(this);
    }
}
