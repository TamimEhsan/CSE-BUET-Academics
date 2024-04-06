package com.tamimehsan;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public class Main {

    public static void main(String[] args)  {

        File file = new File("input.txt");

        Scanner scanner = null;
        try {
            scanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        AVL avl = new AVL();
        boolean loop = true;
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            String[] tokens = input.split(" ");
            String character = tokens[0];
            int item = Integer.parseInt(tokens[1]);

            int decision = 0;
            switch (character) {
                case "I":
                    avl.insertItem(item);
                    avl.printPreOrder();
                    break;
                case "F":
                    avl.searchItem(item);
                    break;
                case "D":
                    avl.deleteItem(item);
                    avl.printPreOrder();
                    break;
                default:
                    loop = false;

            }

        }
        scanner.close();

    }
}

