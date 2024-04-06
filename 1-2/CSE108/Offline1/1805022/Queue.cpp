#include <iostream>
#include <cstdlib>
using namespace std;

class Queue
{
    Array s;
    int size;
    int front;
    int rear;
    // you are not allowed to add any field; you can only add methods
public:
    // your code
    //Constructors
    Queue(){
        front = 0;
        rear = 0;
        size = 0;
    }
    Queue(int sz){
        size = sz;
        front = 0;
        rear = 1;
        s.setLength(sz);
    }
    // End of contructors
    //Methods
    int isFull(){
        if( front - rear +1 >= size )
            return 1;
        else
            return 0;
    }
    int isEmpty(){
        if( front - rear + 1 <= 0 )
            return 1;
        else
            return 0;
    }
    void enqueue(int x)
    {
        if(isFull())
        {
            cout << "Queue is full" << endl;
            exit(0);
        }
        else{
            front++;
            s.setElementAt(front,x);
        }
    }
    int dequeue()
    {
        if(isEmpty())
        {
            cout << "Queue is empty" << endl;
            exit(0);
        }
        else{
            rear++;
            return s.getElementAt(rear-1);
        }
    }
    void clone(Queue cop){
        size = cop.size;
        front = cop.front;
        rear = cop.rear;
        s = cop.s;
    }
};
