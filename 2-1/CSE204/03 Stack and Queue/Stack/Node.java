package com.tamimehsan;

public class Node<T> {
    private T value;
    private Node next;

    public Node() {
        next = null;
        value = null;
    }

    public Node(T value, Node next) {
        this.value = value;
        this.next = next;
    }

    /**
     * @return value stored in node
     */
    public T getValue() {
        return value;
    }

    /**
     * Sets value as the value of this node
     *
     * @param value
     */
    public void setValue(T value) {
        this.value = value;
    }

    /**
     * returns the next value next of current node
     *
     * @return next
     */
    public Node getNext() {
        return next;
    }

    /**
     * Sets
     *
     * @param next
     */
    public void setNext(Node next) {
        this.next = next;
    }
}
