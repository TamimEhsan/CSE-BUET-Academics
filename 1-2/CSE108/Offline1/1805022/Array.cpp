
#include <iostream>
#include <cstdlib>
using namespace std;
#define SIZE 100
#define EMPTY -99

class Array
{
    int a[SIZE];
    int length;
    // you are not allowed to add any field; you can only add methods
public:
    // Constructors
    Array()
    {
        length = 0;
    }
    Array(int size)
    {
        length = size;
        for (int i = 0; i < size; i++)
        {
            a[i] = EMPTY;
        }
    }
    Array(int siz, int val){
        length = siz;
        for (int i = 0; i < siz; i++){
            a[i] = val;
        }
    }
    Array(int siz, int ara[]){
        length = siz;
        for(int i=0;i<siz;i++){
            a[i] = ara[i];
        }
    }
    // End of Constructors
    // Methods
    void setLength(int size)
    {
        length = size;
    }
    int getLength()
    {
        return length;
    }
    void setElementAt(int i, int e)
    {
        if(i >= length)
        {
            cout << "Invalid Index" << endl;
            exit(0);
        }
        else{
            a[i] = e;
        }
    }
    int getElementAt(int i)
    {
        if(i >= length)
        {
            cout << "Invalid Index" << endl;
            exit(0);
        }
        else{
            return a[i];
        }
    }
    void print()
    {
        for(int i =0; i < length; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    void clone(Array ara){
        for( int i=0;i<ara.length;i++ ){
            a[i] = ara.getElementAt(i);
        }
    }
    // End of Methods
};
