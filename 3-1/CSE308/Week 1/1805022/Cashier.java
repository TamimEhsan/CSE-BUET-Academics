package com.tamimehsan;

public class Cashier extends Employee{
    private int serial;
    public Cashier(int serial){
        super("O"+serial,true, false, false,false);
        this.serial = serial;
    }

}
