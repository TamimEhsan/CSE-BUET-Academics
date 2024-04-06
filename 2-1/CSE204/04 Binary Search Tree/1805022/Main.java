package com.tamimehsan;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Scanner scanner = new Scanner(System.in);
        int nodes[] = {8,3,10,1,6,14,4,7,13,15};
        BinarySearchTree BST = new BinarySearchTree();
        Menu menu = new Menu();
        while(true){
            menu.showMenu();
            String dec = scanner.nextLine();
            int decision;
            try{
                decision = Integer.parseInt(dec);
            }catch (Exception e){
                decision = 0;
            }
            switch (decision){
                case 1:
                    String string = scanner.nextLine();
                    try{
                        int number = Integer.parseInt(string);
                        BST.insertItem(number);
                    }catch (ArithmeticException e){
                        System.out.println("Please give proper input");
                    }
                    break;
                case 2:
                    string = scanner.nextLine();
                    try{
                        int number = Integer.parseInt(string);
                        BST.searchItem(number);
                    }catch (ArithmeticException e){
                        System.out.println("Please give proper input");
                    }
                    break;
                case 3:
                    string = scanner.nextLine();
                    try{
                        int number = Integer.parseInt(string);
                        System.out.println("In order Successor: "+BST.getInOrderSuccessor(number));
                    }catch (ArithmeticException e){
                        System.out.println("Please give proper input");
                    }
                    break;
                case 4:
                    string = scanner.nextLine();
                    try{
                        int number = Integer.parseInt(string);
                        System.out.println("In order Predecessor: "+BST.getInOrderPredecessor(number));;
                    }catch (ArithmeticException e){
                        System.out.println("Please give proper input");
                    }
                    break;
                case 5:
                    string = scanner.nextLine();
                    try{
                        int number = Integer.parseInt(string);
                        BST.deleteItem(number);
                    }catch (ArithmeticException e){
                        System.out.println("Please give proper input");
                    }
                    break;
                case 6:
                    string = scanner.nextLine();
                    try{
                        int number = Integer.parseInt(string);
                        System.out.println("Item depth: "+BST.getItemDepth(number));;
                    }catch (ArithmeticException e){
                        System.out.println("Please give proper input");
                    }
                    break;
                case 7:
                    System.out.println("Max item: "+BST.getMaxItem());;
                    break;
                case 8:
                    System.out.println("Min item: "+BST.getMinItem());;
                    break;
                case 9:
                    System.out.println("Height: "+BST.getHeight());;
                    break;
                case 10:
                    System.out.println("In order traversal");
                    BST.printInOrder();
                    System.out.println("");
                    break;
                case 11:
                    System.out.println("Pre order traversal");
                    BST.printPreOrder();
                    System.out.println("");
                    break;
                case 12:
                    System.out.println("Post order traversal");
                    BST.printPostOrder();
                    System.out.println("");
                    break;
                case 13:
                    System.out.println("Size: "+BST.getSize());;
                    break;
                default:
                    System.out.println("Please give proper input");
            }
        }

    }
}

