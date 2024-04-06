#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
int parent[N];
int rnk[N];
void Dsu(int n){
    for(int i=0;i<=n;i++) {
        parent[i] = i;
        rnk[i] = 0;
    }

}
int Find(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = Find(parent[v]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}

int main(){
}
