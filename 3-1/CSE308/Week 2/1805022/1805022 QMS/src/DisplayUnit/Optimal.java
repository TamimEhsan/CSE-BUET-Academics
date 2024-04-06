package DisplayUnit;

import Display.LED;
import Processor.ArduinoMega;

public class Optimal extends DisplayUnit {
    Optimal(){
        this.processor = new ArduinoMega();
        this.display = new LED();
    }
}
