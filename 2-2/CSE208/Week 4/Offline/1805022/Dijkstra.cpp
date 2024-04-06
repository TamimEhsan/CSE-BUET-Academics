#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

struct Edge{
    int to;
    int weight;
};

struct Vertex{

    int distance = 1000000;
    int vertex;
    int parent;
    Vertex operator<(const Vertex& rhs){
        if( distance < rhs.distance ) return {distance,vertex,parent};
        else return rhs;
    }
};

vector< vector<Edge> > adj;
vector< Vertex > vertices;
bool compareDistance(const Vertex& lhs,const Vertex& rhs){
    return lhs.distance<rhs.distance;
}

void dijstra(int source){
    priority_queue<pii,vector<pii>, greater<pii>> pq;
    int n = adj.size();
    vertices.resize(n);
    for(int i=0;i<n;i++) vertices[i].vertex = i;
    vertices[source].distance = 0;
    pq.push({vertices[source].distance,vertices[source].vertex});

    while( !pq.empty() ){
        pii u = pq.top();
        pq.pop();
        for(auto edge:adj[u.second]){
            if( u.first + edge.weight < vertices[ edge.to ].distance ){
                vertices[ edge.to ].distance = u.first + edge.weight;
                vertices[ edge.to ].parent = u.second;
                pq.push({vertices[ edge.to ].distance,edge.to});
            }
        }
    }
}

void printPath(int source,int dest,bool start = false){
    if(source == dest){
        printf("%d->",dest);
        return;
    }

    printPath(source,vertices[dest].parent);
   // cout<<dest<<"->";

    if( start ) printf("%d",dest);
    else printf("%d->",dest);

}

int main(){
    ifstream cin("graph.in");
    int n,m;
    cin>>n>>m;
    adj.resize(n,vector<Edge>());
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        //adj[v].push_back({u,w});
    }
    int source,dest;
    cin>>source>>dest;
    dijstra(source);
    printf("Shortest path cost: %d\n",vertices[dest].distance);
    printPath(source,dest,true);


}

/*
9 17
0 7 60
7 1 150
4 8 70
6 4 80
5 1 4000
8 0 100000
2 3 200
8 2 1000
0 3 300
3 8 50000
3 7 200
2 5 120
6 3 1500
4 0 90
5 7 50
1 6 100
4 1 90
0 5
*/
/*
9 17
0 7 60
7 1 -150
4 8 -70
6 4 80
5 1 4000
8 0 100000
2 3 -200
8 2 1000
0 3 300
3 8 50000
3 7 -200
2 5 120
6 3 1500
4 0 90
5 7 -50
1 6 100
4 1 -90
0 5
*/
