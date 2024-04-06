package com.tamimehsan;

public class Game {
    private int id;
    LinkedList linkedList;
    private int playerCount = 0;
    private int time=1;
    public Game(){
        linkedList = new LinkedList();
    }
    public Game(int[] reflexes){
        linkedList = new LinkedList(reflexes);
        playerCount = reflexes.length;
    }
    public void decide(int time,char c,int reflex){
        // traverse the whole time
        while(this.time<time){
            this.time++;
          //  System.out.print(this.time);
            linkedList.next();
        }
        if( c == 'P' ) {
            System.out.println("Player " + linkedList.getCurrentNode().getId() + " is holding the pillow at t=" + time);
        }else if( c == 'M' ) {
            System.out.println("Player "+linkedList.getCurrentNode().getId()+" has been eliminated at t="+time);
            linkedList.deleteCurrentNode();
        } else if( c == 'I' ){
            linkedList.addNode(++playerCount,reflex);
        } else if( c == 'R' ){
            linkedList.changeDirection();
        } else{
            if( linkedList.getNodeCount() > 1 ){
                System.out.print("Game Over: Player " + linkedList.getCurrentNode().getId() + " is holding the pillow at t=" + time);
                System.out.print(", pillow passing sequence = Player ");
                linkedList.printSequence();

            }
        }
    }
    public int getPlayerCount(){
        return linkedList.getNodeCount();
    }
    public int getCurrentPlayer(){
        return linkedList.getCurrentNode().getId();
    }
}
