package com.tamimehsan;

public class Officer extends Employee {
    private int serial;
    public Officer(int serial) {
        super("S"+serial,true, true, false,false);
        this.serial = serial;
    }
}
