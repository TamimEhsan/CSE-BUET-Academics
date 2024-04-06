package AdapterOld;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class HybridCalculator implements Calculator{
    CalculatorAdapter calculatorAdapter;
    @Override
    public int calculateSum(String seperatorType,String fileName) {
        if( seperatorType.equalsIgnoreCase("space") ){
            File file = new File(fileName);
            String fileIO = "";
            try {
                Scanner scanner = new Scanner(file);
                while ( scanner.hasNextLine())
                    fileIO = fileIO.concat(scanner.nextLine());

                String[] strings = fileIO.split(" ");
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
        }else{
            calculatorAdapter = new CalculatorAdapter();
            return calculatorAdapter.calculateSum(seperatorType,fileName);
        }
    }
}
