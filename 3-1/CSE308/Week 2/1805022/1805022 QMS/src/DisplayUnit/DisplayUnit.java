package DisplayUnit;

import Display.Display;
import Processor.Processor;

public abstract class DisplayUnit {


    protected Processor processor;
    protected Display display;

    public Processor getProcessor() {
        return processor;
    }

    public Display getDisplay() {
        return display;
    }



}
