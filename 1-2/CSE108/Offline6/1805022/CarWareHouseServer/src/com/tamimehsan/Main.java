package com.tamimehsan;

import com.tamimehsan.Data.Database;
import com.tamimehsan.Network.Server;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        // write your code here
        Database.getInstance().readData();
        Database.getInstance().readUserData();
        new Thread() {
            @Override
            public void run() {
                String s;
                Scanner scanner = new Scanner(System.in);
                do {
                    s = scanner.nextLine();
                } while (!s.equals("-1"));
                Database.getInstance().writeData();
                Server.getInstance().closeConnection();
            }
        }.start();
        Server.getInstance().startServer();
    }
}
