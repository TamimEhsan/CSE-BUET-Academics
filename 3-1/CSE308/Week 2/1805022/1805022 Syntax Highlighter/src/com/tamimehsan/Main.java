package com.tamimehsan;

import Editor.Editor;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Scanner scanner = new Scanner(System.in);
        Editor editor = Editor.getInstance();
        System.out.println("Enter file name with extension");
        String file_name = scanner.nextLine();

        String file_type = file_name.strip().split("\\.")[1];
        editor.setLanguage(file_type);



    }
}
