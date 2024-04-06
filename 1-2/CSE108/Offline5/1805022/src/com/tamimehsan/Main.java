package com.tamimehsan;

import com.tamimehsan.IO.Console;
import com.tamimehsan.controller.MainMenu;
import com.tamimehsan.data.Database;

public class Main {

    public static void main(String[] args) {
        Database.getInstance().readData();
        new MainMenu().view();
        Console.getInstance().closeScanner();
        Database.getInstance().writeData();
    }
}
