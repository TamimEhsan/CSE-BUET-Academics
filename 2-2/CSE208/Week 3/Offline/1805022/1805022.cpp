
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
    double w;
    bool operator<(const Edge& B){
        return w<B.w;
    }
};

struct Vertex{
    double w = 100000;
    int par = -1;
    bool taken = false;
};

void printKruskal(vector<Edge> &kruskal){
    printf("List of edges selected by Kruskal's:{");
    for(auto [u,v,w]:kruskal){
        printf("(%d,%d),",u,v);
    }
    printf("\b}\n");
}

void printPrim(Vertex vertices[],int n){
    printf("List of edges selected by Prim's:{");
    for(int i=0;i<n;i++){
        if( vertices[i].par !=-1 ) printf("(%d,%d),",vertices[i].par,i);
    }
    printf("\b}\n");
}
int main(){
    ifstream cin;
    cin.open("mst.in");
    int n,m;
    cin>>n>>m;
    DSU dsu(n);
    Edge edges[m];
    Vertex vertices[n];
    vector<pair<int,double>>adj[n];

    for(int i=0;i<m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        edges[i] = {u,v,w};
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    sort(edges,edges+m);
    vector<Edge> kruskal;
    double mstWeight = 0;
    for(auto [u,v,w]:edges) {
        if( dsu.Find(u)!=dsu.Find(v) ){
            dsu.Union(u,v);
            kruskal.push_back({u,v,w});
            mstWeight+=w;
        }
    }

    priority_queue<pair<double,int>,vector <pair<double,int>> , greater<pair<double,int>>> pq;
    vertices[0].w = 0;

    pq.push({0.0,0});
    while( !pq.empty() ){
        auto [w,u] = pq.top();
        pq.pop();
        if( vertices[u].taken == true ) continue;
        vertices[u].taken = true;
        for(auto [v,w]:adj[u]){
            if( vertices[v].taken == false and w<vertices[v].w ){
                vertices[v].w = w;
                vertices[v].par = u;
                pq.push({w,v});
            }
        }
    }

    cout<<"Cost of the minimum spanning tree : "<<mstWeight<<endl;
    printKruskal(kruskal);
    printPrim(vertices,n);



}
/*
6 9
0 1 1.0
1 3 5.0
3 0 3.0
3 4 1.0
1 4 1.0
1 2 6.0
5 2 2.0
2 4 4.0
5 4 4.0
*/

