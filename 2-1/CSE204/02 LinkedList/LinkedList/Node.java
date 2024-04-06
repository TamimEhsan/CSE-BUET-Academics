package com.tamimehsan;

public class Node {
    private int id;
    private Node previous;
    private Node next;
    private int reflexTime;
    private int remainingTime;
    public Node() {
    }

    public Node(int id, Node previous, Node next, int reflexTime) {
        this.id = id;
        this.previous = previous;
        this.next = next;
        this.reflexTime = reflexTime;
        remainingTime = reflexTime;
    }

    public Node getPrevious() {
        return previous;
    }

    public Node getPrevious(int direction){
        if( direction == 0 ) return previous;
        else return next;
    }
    public void setPrevious(Node previous) {
        this.previous = previous;
    }

    public Node getNext() {
        return next;
    }

    public Node getNext(int direction){
        if( direction == 0 ) return next;
        else return previous;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    public int getId() {
        return id;
    }

    public int getReflexTime() {
        return reflexTime;
    }

    public int getRemainingTime() {
        return remainingTime;
    }

    public void setRemainingTime(int remainingTime) {
        this.remainingTime = remainingTime;
    }

    public void reset(){
        remainingTime = reflexTime;
    }
    public void decrease(){
        remainingTime--;
    }
}
