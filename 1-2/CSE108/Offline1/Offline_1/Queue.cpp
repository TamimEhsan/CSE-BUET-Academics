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
    void enqueue(int x)
    {
        //if(isFull())
        {
            cout << "Queue is full" << endl;
            exit(0);
        }
        // your code
    }
    int dequeue()
    {
        //if(isEmpty())
        {
            cout << "Queue is empty" << endl;
            exit(0);
        }
        // your code
    }
    // your code
};
