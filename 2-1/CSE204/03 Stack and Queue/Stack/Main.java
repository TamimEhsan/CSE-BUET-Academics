package com.tamimehsan;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        // test cases
      /*  String equations[] = {
                "(9*3-(7*8+((-4)/2)))",     //valid -27
                "(9*3-(7*8+((-4/2)))",      // invalid => Unary
                "(9*3-(7*8+((4/2)))",        // invalid => invalid RBS
                "(((0)+(-4)+3*(2-7*8/(2-1)))/(2))",     // valid -83
                "12*123/((-5)+2)",          // valid -492
                "123.45*(678.90/((-2.5)+11.5)-(80-19)*33.25)/20+11",    // valid -1242.761
                "(123.45*(678.90/((-2.5)+11.5)-(((80-(19)))*33.25))/20)-(123.45*(678.90/((-2.5)+11.5)-(((80-(19)))*33.25))/20)+(13-2)/(-11)", // valid -1
                "12.5-8.6/(12-(18-(2*3)))", // Invalid => divided by zero
                "((-(4*8))/2)",             // valid -16
                "(-(-(-4)))",               // valid -4
                "2*4/5",                    // valid 1.6
                "2/5*4",                    // valid 1.6
                "1 + 2 + 3",                // valid 6
                "9+2(56)",                  // Invalid => Incorrect syntax
                "45+15^3",                  // Invalid => Unknown character
                "1-1/(1*1-(2-3)*3/7*0.4)"   // Valid 0.14634144
        };

        for (String equation : equations) {
            System.out.println(equation);
            Parser parser = new Parser(equation);
            try {
                float value = parser.parse();
                if ((int) value == value) System.out.println("Valid expression, Computed value:    " + (int) value);
                else System.out.println("Valid expression, Computed value:    " + value);
            } catch (ArithmeticException e) {
                System.out.println("Not valid");
            }
            System.out.println("");
        }
*/

        //  while(scanner.hasNext()){
        String equation = scanner.nextLine();
        Parser parser = new Parser(equation);
        try {
            float value = parser.parse();
            if ((int) value == value) System.out.println("Valid expression, Computed value:    " + (int) value);
            else System.out.println("Valid expression, Computed value:    " + value);
        } catch (ArithmeticException e) {
            System.out.println("Not valid");
        }
        // }
    }
}
