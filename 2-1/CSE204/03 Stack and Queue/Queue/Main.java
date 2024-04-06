package com.tamimehsan;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        // write your code here
        Scanner scanner = new Scanner(System.in);
        String string = scanner.nextLine();
        StringProcessor stringProcessor = new StringProcessor(string);
        stringProcessor.process();
        System.out.println(stringProcessor.getNewString());
    }
}
