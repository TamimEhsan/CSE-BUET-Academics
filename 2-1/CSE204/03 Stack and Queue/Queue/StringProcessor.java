package com.tamimehsan;

public class StringProcessor {
    private int[] letters;
    private Queue queue;
    private String string;
    public String newString;
    private int size;

    public StringProcessor(String string) {
        this.string = string;
        size = string.length();
        letters = new int[26];
        newString = "";
        queue = new Queue();
    }

    public void process() {
        for (int i = 0; i < size; i++) {
            char c = string.charAt(i);
            letters[getValue(c)]++;
            queue.push(c);
            while (!queue.empty() && letters[getValue(queue.front())] > 1) {
                queue.pop();
            }
            if (queue.empty()) {
                newString += "#";
            } else {
                newString += queue.front() + "";
            }

        }
    }

    public String getNewString() {
        return newString;
    }

    private int getValue(char c) {
        return (int) c - (int) 'a';
    }
}
