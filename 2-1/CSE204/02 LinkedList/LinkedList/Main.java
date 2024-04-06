package com.tamimehsan;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] reflexes = new int[n];
        for(int i=0;i<n;i++){
            reflexes[i] = scanner.nextInt();
        }
        Game game = new Game(reflexes);
        scanner.nextLine();
        char c = 'A';
        while(c!='F'){
            int time,reflex;
            String s;
            s = scanner.nextLine();
            String[] token = s.split(" ");
            c = token[1].charAt(0);
            time = Integer.parseInt(token[0]);
            if( c == 'I' ){
                reflex = Integer.parseInt(token[2]);
                game.decide(time,'I',reflex);

            }else{
                game.decide(time,c,0);
            }
            if(game.getPlayerCount() == 1){
                System.out.print("Game over : Player "+game.getCurrentPlayer()+" wins!!");
                c = 'F';
            }
        }
    }
}

/*
3
4 5 2
6 P
6 M
6 P
7 P
8 P
9 P
10 I 1
12 P
13 P
15 P
17 P
22 R
23 P
24 P
25 F
 */