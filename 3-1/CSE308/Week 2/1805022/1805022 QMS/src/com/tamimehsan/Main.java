package com.tamimehsan;

import Builder.Product;
import Builder.ProductBuilder;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Scanner scanner = new Scanner(System.in);
        System.out.println("Package Type: (Deluxe/Optimal/Poor)");
        String packageType = scanner.nextLine();
        System.out.println("Communication module: (Wifi/Mobile)");
        String communicationType = scanner.nextLine();
        System.out.println("Display Count:");
        int displayCount = scanner.nextInt();

        ProductBuilder productBuilder = new ProductBuilder();
        Product product = productBuilder
                            .setPackage(packageType)
                            .setCommunication(communicationType)
                            .setDisplayUnit(displayCount)
                            .getProduct();
        product.show();
        System.out.println("Product price "+product.getPrice());

    }
}
