package DisplayUnit;

import Display.LED;
import Processor.ATMega32;

public class Poor extends DisplayUnit {
    Poor(){
        this.processor = new ATMega32();
        this.display = new LED();
    }
}
