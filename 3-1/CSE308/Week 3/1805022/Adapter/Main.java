package Adapter;


import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
	// write your code here

        String fileSpace = "src/Adapter/inputSpaceSeperated.txt";
        String fileTilda = "src/Adapter/inputTildaSeperated.txt";
        Calculator calculatorSpace = new CalculatorSpaceSeperated();
        Calculator calculatorAdapter = new CalculatorAdapter();
        int sum1 = 0;
        try {
            sum1 = calculatorSpace.calculateSum(new File(fileSpace));
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(sum1);
        int sum2 = 0;
        try {
            sum2 = calculatorAdapter.calculateSum(new File(fileTilda));
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(sum2);
    }
}
