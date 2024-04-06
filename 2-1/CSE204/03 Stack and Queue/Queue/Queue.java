package com.tamimehsan;


public class Queue {
    private Node head;
    private Node tail;
    private int size;

    public Queue() {
        head = null;
        tail = null;
    }

    public void push(char value) {
        Node node = new Node(value, null);
        if (head == null) {
            head = node;
            tail = node;
        } else {
            tail.setNext(node);
            tail = node;
        }
        size++;
    }

    public char front() {
        if (size == 0) return 0;
        return head.getValue();
    }

    public int last() {
        if (size == 0) return 0;
        return tail.getValue();
    }

    public void pop() {
        if (size == 0) return;
        head = head.getNext();
        size--;
    }

    public int size() {
        return size;
    }

    public boolean empty() {
        return size == 0;
    }
}
