package com.tamimehsan;

public class Node {
    private char value;
    private Node next;

    public Node() {
    }

    public Node(char value, Node next) {
        this.value = value;
        this.next = next;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    public Node getNext() {
        return next;
    }

    public char getValue() {
        return value;
    }

    public void setValue(char value) {
        this.value = value;
    }
}
