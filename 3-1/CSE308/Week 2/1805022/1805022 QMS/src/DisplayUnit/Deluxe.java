package DisplayUnit;

import Display.LCD;
import Processor.RaspberryPi;

public class Deluxe extends DisplayUnit {

    Deluxe(){
        this.processor = new RaspberryPi();
        this.display = new LCD();
    }

}
