package com.tamimehsan;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        String[] strings = {"abla", "Cfasdf", "efsdfs","bla","bla","abla"};
        String[] strings2 = {"bsdfla", "dfassdf", "fsdfs","gzBla"};
        // Constructor check
        Array array = new Array();
        Array array1 = new Array(5);
        Array array2 = new Array(strings2);
        // Methods check
        System.out.println(Arrays.toString(array2.getArray()));
        try{
            System.out.println(array2.getAnElement(2));
        } catch (IndexOutOfBoundsException e){
            System.out.println(e.getMessage());
        }
        for(int i=0;i<strings.length;i++){
            array1.add(strings[i]);
        }
        array1.add(1,strings[2]);
        array1.remove("bla");
        System.out.println(Arrays.toString(array1.findIndex("abla")));
        try{
            System.out.println(Arrays.toString(array1.subArray(1,3)));
        } catch (IndexOutOfBoundsException e){
            System.out.println(e.getMessage());
        }
        array.merge(array2.getArray(),array1.getArray());
        System.out.println(array.length());
        System.out.println(array.isEmpty());
   }
}
