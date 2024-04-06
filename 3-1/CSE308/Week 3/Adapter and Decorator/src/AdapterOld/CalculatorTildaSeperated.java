package AdapterOld;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class CalculatorTildaSeperated implements AdvancedCalculator {
    @Override
    public int calculateSum(String fileName) {
        File file = new File(fileName);
        String fileIO = "";
        try {
            Scanner scanner = new Scanner(file);
            while ( scanner.hasNextLine())
                fileIO = fileIO.concat(scanner.nextLine());

            String[] strings = fileIO.split("~");
            int sum = 0;
            for(String string:strings){
                int value = Integer.parseInt(string);
                sum+=value;
            }
            return sum;

        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return 0;
        }
    }
}
