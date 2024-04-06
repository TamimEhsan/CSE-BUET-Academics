package Adapter;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class CalculatorSpaceSeperated implements Calculator {
    @Override
    public int calculateSum(File file) throws IOException {
        String fileIO = "";
        Scanner scanner = new Scanner(file);
        while ( scanner.hasNextLine())
            fileIO = fileIO.concat(scanner.nextLine());

        String[] strings = fileIO.split(" ");
        int sum = 0;
        for(String string:strings){
            int value = Integer.parseInt(string);
            sum+=value;
        }
        scanner.close();
        return sum;


    }
}
