#include<bits/stdc++.h>
using namespace std;

class DSU{
    vector<int> parent,rnk;
    public:
    DSU(int n){
        parent.resize(n+5,0);
        rnk.resize(n+5,0);
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
};

struct Edge{
    int u;
    int v;
};
int main(){

    int n,m;
    cin>>n>>m;
    DSU dsu[4](n);
    vector<Edge> edges[4];

    for(int i=0;i<m;i++){
        int u,v;
        int type;
        cin>>u>>v>>type;
        edges[type].push_back({u,v});
    }
    int taken3 = 0;
    int taken1 = 0;
    int taken2 = 0;
    for(Edge edge:edges[3]){
        int u = edge.u;
        int v = edge.v;
        if( dsu[3].Find(u)!=dsu[3].Find(v) ){
            dsu[1].Union(u,v);
            dsu[2].Union(u,v);
            dsu[3].Union(u,v);
            taken3++;
        }
    }
    for(Edge edge:edges[1]){
        int u = edge.u;
        int v = edge.v;
        if( dsu[1].Find(u)!=dsu[1].Find(v) ){
            dsu[1].Union(u,v);
            taken1++;
        }
    }
    for(Edge edge:edges[2]){
        int u = edge.u;
        int v = edge.v;
        if( dsu[2].Find(u)!=dsu[2].Find(v) ){
            dsu[2].Union(u,v);
            taken2++;
        }
    }
    if( taken1+taken3!=n-1 or taken2+taken3!=n-1 ){
        cout<<-1<<endl;
        return 0;
    }
    cout<<m - (taken1+taken2+taken3)<<endl;

}
/*
6 6
1 2 3
2 3 3
3 4 3
5 3 3
5 4 3
4 6 3
*/
/*
5 7
1 2 3
2 3 3
3 4 3
5 3 3
5 4 3
5 2 3
1 5 3
*/
