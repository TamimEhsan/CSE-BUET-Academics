package Adapter;

import java.io.File;
import java.io.IOException;

public interface Calculator {
    public int calculateSum(File file) throws IOException;
}
