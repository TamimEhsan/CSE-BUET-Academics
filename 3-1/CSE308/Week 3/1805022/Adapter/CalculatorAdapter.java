package Adapter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class CalculatorAdapter implements Calculator {

    Calculator calculator;
    CalculatorAdapter(){
        calculator = new CalculatorSpaceSeperated();
    }
    @Override
    public int calculateSum(File file) throws IOException {
        Scanner scanner = new Scanner(file);
        FileWriter fw = new FileWriter("src/Adapter/temp.txt");
        String input = "";
        while (scanner.hasNextLine()) {
            input = scanner.nextLine();
            String[] inputs = input.split("~");
            for (String string : inputs) {
                fw.write(string);
                fw.write(" ");
            }
        }
        fw.close();
        File newFile = new File("src/Adapter/temp.txt");
        int sum = calculator.calculateSum(newFile);
        newFile.delete();
        return sum;
    }
}
