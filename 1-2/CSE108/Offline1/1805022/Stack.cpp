#include <iostream>
#include <cstdlib>
using namespace std;

class Stack
{
    Array s;
    int size;
    int top;
    // you are not allowed to add any field; you can only add methods
public:
    // Constructors
    Stack(){
        top = -1;
    }
    Stack(int sz){
        size = sz;
        top = -1;
        s.setLength( sz );
    }
    // End of constructors
    // Methods
     int isFull(){
        if( top == size )
            return 1;
        else
            return 0;
    }
    int isEmpty(){
        if( top == -1 )
            return 1;
        else
            return 0;
    }
    void push(int x)
    {
        if(isFull())
        {
            cout << "Stack is full" << endl;
            exit(0);
        }
        else{
            top++;
            s.setElementAt(top,x);
        }
    }
    int pop()
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl;
            exit(0);
        }
        else{
            top--;
            return s.getElementAt(top+1);
        }
    }

    void clone( Stack cop ){

        s.setLength(cop.s.getLength());
        top = cop.top;
        for( int i=0;i<=top;i++ ){
            s.setElementAt(i, cop.s.getElementAt(top-i) );
        }
    }
};
