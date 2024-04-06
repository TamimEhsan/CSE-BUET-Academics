package com.tamimehsan;


import java.util.Arrays;

public class Array {
    private int PREDEFINED_SIZE = 100;
    private int arraySize = 0;
    private int elements = 0;
   // private ArrayList<String> stringArrayList;
    private String[] stringArray;
    public Array() {
        stringArray = new String[PREDEFINED_SIZE];
        elements = 0;
        arraySize = PREDEFINED_SIZE;
    }
    public Array(int size){
        elements = 0;
        arraySize = size;
        stringArray = new String[size];
    }
    public Array(String[] strings){
        stringArray = strings;
        elements = strings.length;
        arraySize = elements;
        System.out.println(elements);
    }
    public String[] getArray(){
        return Arrays.copyOfRange(stringArray, 0, elements);
    }
    public String getAnElement(int index) throws IndexOutOfBoundsException{
        if( index<0 || index>=elements ){
            throw new IndexOutOfBoundsException();
        } else{
            return stringArray[index];
        }
    }
    public void add(String string){
        if( elements == arraySize ){
            arraySize = arraySize*2+1;
            stringArray = Arrays.copyOf(stringArray, arraySize);
        }
        stringArray[elements] = string;
        elements++;
    }
    public void add(int index,String string) throws IndexOutOfBoundsException{
        if( index<0 || index>=elements ){
            throw new IndexOutOfBoundsException();
        } else{
            stringArray[index] = string;
        }
    }
    public void remove(String string){
        // Two pointer
        int index = 0;
        for(int i=0;i<elements;i++){
            if( !stringArray[i].equals(string) ){
                stringArray[index++] = stringArray[i];
            }
        }
        elements = index;
        if( 2*elements<=arraySize ){
            arraySize = elements;
            stringArray = Arrays.copyOf(stringArray, arraySize);
        }
    }
    public int[] findIndex(String string){
        int[] indexes = new int[elements];
        // Two pointers
        int index = 0;
        for(int i=0;i<elements;i++){
            if( stringArray[i].equals(string) ){
                indexes[index++] = i;
            }
        }
        return Arrays.copyOfRange(indexes, 0, index);
    }
    public String[] subArray(int start,int end) throws IndexOutOfBoundsException{
        if( start<0 || start>=elements || end<0 || end>=elements ){
            throw new IndexOutOfBoundsException();
        } else{
            return Arrays.copyOfRange(stringArray, start, end);
        }
    }
    public void merge(String[] A1,String[] A2){
        // Check for size
        if( A1.length + A2.length > arraySize ){
            arraySize = A1.length+A2.length;
            stringArray = new String[arraySize];
        }
        elements = A1.length+A2.length;
        // Two pointers
        int i = 0,j = 0,index = 0;
        while(i<A1.length || j<A2.length){
            if( i == A1.length ){
                stringArray[index++] = A2[j++];
            } else if( j == A2.length ){
                stringArray[index++] = A1[i++];
            }else{
                if( A1[i].compareTo(A2[j])<0  ){
                    stringArray[index++] = A1[i++];
                }else{
                    stringArray[index++] = A2[j++];
                }
            }
        }
    }
    public int length(){
        return elements;
    }
    public boolean isEmpty(){
        return elements == 0;
    }
}
