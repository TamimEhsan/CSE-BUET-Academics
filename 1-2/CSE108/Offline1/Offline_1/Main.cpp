#include <iostream>
#include "Array.cpp"
#include "Stack.cpp"
#include "Queue.cpp"
using namespace std;

int main()
{
    int x[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Array a(10, 1); // create an  Array of length 10 and all values are initialized to 1
    Array b(5, x); // create an Array with first 5 elements of given x
    Array c(10); // create an Array of length 10
    c.clone(a); // Array c will be a clone of Array a
    cout << "Elements of Array a: " << endl;
    a.print();
    cout << "Elements of Array b: " << endl;
    b.print();
    cout << "Elements of Array c: " << endl;
    c.print();

    Stack s(10); // create a Stack with size 10
    for (int i = 0; i < 5; i++)
    {
        s.push(i+1);
    }
    Stack t; // create an empty Stack
    t.clone(s); // Stack t will be a clone of Stack s
    cout << "Elements of Stack t: " << endl;
    while(!t.isEmpty())
    {
        cout << t.pop() << " " ;
    }
    cout << endl;
    cout << "Elements of Stack s: " << endl;
    while(!s.isEmpty())
    {
        cout << s.pop() << " " ;
    }
    cout << endl;

    Queue q(10); // create a Queue with size 10
    for (int i = 0; i < 5; i++)
    {
        q.enqueue(i+1);
    }
    Queue r; // create an empty Queue
    r.clone(q); // Queue r will be a clone of Queue q
    cout << "Elements of Queue r: " << endl;
    while(!r.isEmpty())
    {
        cout << r.dequeue() << " " ;
    }
    cout << endl;
    cout << "Elements of Stack q: " << endl;
    while(!q.isEmpty())
    {
        cout << q.dequeue() << " ";
    }
    cout << endl;
}

