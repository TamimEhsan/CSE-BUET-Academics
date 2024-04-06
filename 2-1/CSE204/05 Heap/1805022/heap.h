#include<bits/stdc++.h>
using namespace std;
#include<vector>
class Heap{
    int* heap;
    int heapSize;
    int maxSize;
public:
    Heap(int maximumSize);
    Heap(vector<int>&v);
    void heapify(int pos);
    void buildMaxHeap();
    void insert(int value);
    void deleteKey();
    int getMax();
    int size();
    ~Heap();
};
Heap::Heap(int maximumSize){
    heapSize = 0;
    heap = new int[maximumSize+5];
    maxSize = maximumSize;
}
Heap::Heap(vector<int>&v){
    int n = v.size();
    heap = new int[n+5];
    heapSize = n;
    for(int i=1;i<=heapSize;i++)
        heap[i] = v[i-1];
}
void Heap::heapify(int pos){
    int left = 2*pos;
    int right = 2*pos+1;
    int largest = pos;
    if( left<=heapSize and heap[left]>heap[largest] )
        largest = left;
    if( right<=heapSize and heap[right]>heap[largest] )
        largest = right;
    if( largest!=pos ){
        std::swap( heap[pos],heap[largest] );
        heapify(largest);
    }
}

void Heap::buildMaxHeap(){
    for( int i= heapSize/2;i>=1;i-- ){
        heapify(i);
    }
}
void Heap::insert(int value){
    if( heapSize == maxSize ) std::cout<<"Error! exceeded max capacity!"<<std::endl;
    heap[++heapSize] = value;
    int position = heapSize;
    while(position!=1 and heap[position]>heap[position/2]){
        std::swap( heap[position],heap[position/2] );
        position/=2;
    }
}
void Heap::deleteKey(){
    if( heapSize<1 ) return;
    heap[1] = heap[heapSize];
    heapSize--;
    heapify(1);
}
int Heap::getMax(){
    if( heapSize>=1 )
        return heap[1];
    else return -1;
}
int Heap::size(){
    return heapSize;
}
Heap::~Heap(){
    if( heap!=nullptr ) delete[] heap;
}

void heapsort(vector<int>&v){
    Heap heap(v);
    heap.buildMaxHeap();
    for(int i=0;i<v.size();i++){
        v[i] = heap.getMax();
        heap.deleteKey();
    }
}
