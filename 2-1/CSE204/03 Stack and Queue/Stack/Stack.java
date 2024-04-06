package com.tamimehsan;

public class Stack<T> {
    private Node<T> head;
    private int size;

    public Stack() {
    }

    /**
     * returns the topmost element of the stack if exists
     *
     * @return
     */
    public T top() {
        if (head == null) return null;
        return head.getValue();
    }

    /**
     * Adds value to the top of stack
     *
     * @param value
     */
    public void push(T value) {
        if (size == 0) {
            Node<T> node = new Node<T>(value, null);
            head = node;
        } else {
            Node<T> node = new Node<T>(value, head);
            head = node;
        }
        size++;
    }

    /**
     * takes out the topmost element of the stack if it exists
     */
    public void pop() {
        if (size != 0) {
            head = head.getNext();
            size--;
        }
    }

    /**
     * Returns the size of the stack
     *
     * @return size
     */
    public int size() {
        return size;
    }

    /**
     * Checks if the stack has any element
     *
     * @return true if empty
     */
    public boolean empty() {
        return size == 0;
    }
}
