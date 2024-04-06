#include<bits/stdc++.h>
using namespace std;

#define DE cout<<"Hello general Kenobi"<<endl;

struct Node{
    int key,degree;
    Node *child,*parent,*sibling;
    Node(){
        child = parent = sibling = NULL;
    }
    Node(int _key){
        key = _key;
        degree = 0;
        child = parent = sibling = NULL;
    }
};

struct Binomial_Heap{
    Node *head;
    map<int,Node*>hashedMap;
    Binomial_Heap(){
        head = NULL;
    }

    // Returns the maximum value present in heap or else returns INT_MIN
    int BINOMIAL_HEAP_MAXIMUM(){
        Node* curr = head;
        int mx = INT_MIN;
        while(curr!=NULL){
            mx = max(mx,curr->key);
            curr = curr->sibling;
        }
        return mx;
    }

    // Finds the Node with maximum value, deletes it and returns the key. Else returns INT_MIN
    int BINOMIAL_HEAP_EXTRACT_MAX(){
        //find the root x with the maximum key in the root list of H ,

        Node* prevx;
        Node* x;

        Node* prev = NULL;
        Node* curr = head;

        int mx = INT_MIN;
        while(curr!=NULL){
            if( curr->key >mx ){
                mx = curr->key;
                prevx = prev;
                x = curr;
            }
            prev = curr;
            curr = curr->sibling;
        }
        if( mx == INT_MIN ) return mx;
        hashedMap[mx] = NULL;
        //and remove x from the root list of H
        if( prevx!=NULL ) prevx->sibling = x->sibling;
        else head = x->sibling;

        //reverse the order of the linked list of x’s children,
        Node* rev = BINOMIAL_HEAP_REVERSE(x->child);
        // and set head[H'] to point to the head of the resulting list
        head = BINOMIAL_HEAP_UNION(head,rev);
        return mx;
    }

    // Increases the value of node with key key to newKey
    void BINOMIAL_HEAP_INCREASE_KEY(int key,int newKey){
        Node* x = hashedMap[key];

        if( newKey<key ) return;
        hashedMap[key] = NULL;
        x->key = newKey;
        hashedMap[newKey] = x;
        Node* y = x;
        Node* z = y->parent;
        while(z!=NULL and y->key > z->key){
            swap( y->key,z->key );
            hashedMap[y->key] = y;
            hashedMap[z->key] = z;
            y = z;
            z = y->parent;
        }
    }

    // Reverses the order of a linked list of nodes
    Node* BINOMIAL_HEAP_REVERSE(Node* x){
        if( x == NULL ) return NULL;
        Node* tail = NULL;
        Node* nextx;
        x->parent = NULL;

        while(x->sibling!=NULL){
            nextx = x->sibling;
            x->sibling = tail;
            tail = x;
            x = nextx;
            x->parent = NULL;
        }
        x->sibling = tail;
        return x;
    }

    // Merge two binomial heap into one according to sorted size of degree
    Node* BINOMIAL_HEAP_MERGE(Node* h1,Node* h2){
        Node* h = NULL;
        Node** temp = &h;
        while(h1 and h2){
            if( h1->degree<=h2->degree ){
                *temp = h1;
                h1 = h1->sibling;
            }else{
                *temp = h2;
                h2 = h2->sibling;
            }
            temp = &(*temp)->sibling;
        }
        if( h1 ) *temp = h1;
        if( h2 ) *temp = h2;
        return h;
    }

    // Links two trees of same degree into one
    void BINOMIAL_LINK(Node* y, Node* z){
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree+1;
    }

    // Union operation on two seperate binomial heap
    Node* BINOMIAL_HEAP_UNION(Node* h1, Node* h2){
        Node* h = BINOMIAL_HEAP_MERGE(h1,h2);
        if( h == NULL ) return NULL;
        Node* prevx = NULL;
        Node* x = h;
        Node* nextx = x->sibling;
        while(nextx!=NULL){
            if( x->degree!=nextx->degree or ( nextx->sibling !=NULL and nextx->sibling->degree ==x->degree ) ){
                prevx = x;
                x = nextx;
            }else if( x->key >=nextx->key ){
                x->sibling = nextx->sibling;
                BINOMIAL_LINK(nextx,x);
            }else{
                if( prevx == NULL ) {
                    h = nextx;
                }else{
                    prevx->sibling = nextx;
                }
                BINOMIAL_LINK(x,nextx);
                x = nextx;
            }
            nextx = x->sibling;
        }
        return h;
    }

    // Inserts a new value into the heap by UNION
    void BINOMIAL_HEAP_INSERT(int val){
        Node* newNode = new Node(val);
        hashedMap[val] = newNode;
        head = BINOMIAL_HEAP_UNION(head,newNode);
    }

    // Prints the heap by BFS traversal
    void PRINT(){
        Node* x = head;

        cout<<"Printing Binomial Heap...\n-------------------------\n";
        while(x!=NULL){
           cout<<"Binomial Tree, B"<<x->degree<<endl;
           cout<<"Level 0 : "<<x->key;
           vector<vector<int>> nodes;
           bfs(x->child);
           cout<<endl;
           x = x->sibling;
        }
        cout<<"--------------------------\n";
    }

    void bfs(Node* u){
        if( u == NULL ) return;
        int level = 1;
        queue<Node*>q;
        q.push(u);
        while(!q.empty()){
            cout<<endl<<"Level "<<level++<<" : ";
            queue<Node*>qq;
            Node* u =q.front();
            q.pop();
            while(u!=NULL){
                qq.push(u);
                cout<<u->key<<" ";
                u = u->sibling;
            }
            queue<Node*>qqq;
            while(!qq.empty()){
                Node* u = qq.front();
                qq.pop();
                if( u->child!=NULL ) qqq.push( u->child );
            }
            q = qqq;
        }

    }

};


int main(){
    ifstream cin("in4.txt");
    Binomial_Heap heap;
    string s;
    while(cin>>s){

        if( s == "INS" ){
            int val;
            cin>>val;
            heap.BINOMIAL_HEAP_INSERT(val);
            cout<<"Insertd "<<val<<endl;
        }else if( s == "FIN" ){
            int mx = heap.BINOMIAL_HEAP_MAXIMUM();
            if( mx == INT_MIN ){
                cout<<"FindMax returned null"<<endl;
            }else{
                cout<<"FindMax returned "<<mx<<endl;
            }
        }else if( s == "EXT" ){
            int mx = heap.BINOMIAL_HEAP_EXTRACT_MAX();
            if( mx == INT_MIN ){
                cout<<"ExtractMax returned null"<<endl;
            }else{
                cout<<"ExtractMax returned "<<mx<<endl;
            }

        }else if( s == "INC" ){
            int prevKey,newKey;
            cin>>prevKey>>newKey;
            heap.BINOMIAL_HEAP_INCREASE_KEY(prevKey,newKey);
            printf("Increased %d. The updated value is %d.\n",prevKey,newKey);
        }else if( s == "PRI" ){
            heap.PRINT();
        }else{
            break;
        }
    }
}

/*
INS 7
INS 12
INS 19
INS 5
INS 16
INS 6
PRI
*/
