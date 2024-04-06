package Communication;

public class CommunicationFactory {
    public static Communication getCommunication(String type){
        if( type == null )
            return null;
        if( type.equalsIgnoreCase("wifi") )
            return new Wifi();
        else if( type.equalsIgnoreCase("mobile") )
            return new MobileData();
        else return null;
    }
}
