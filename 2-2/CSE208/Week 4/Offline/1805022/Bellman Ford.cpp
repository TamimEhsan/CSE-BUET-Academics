#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int INF = 1000000;


struct Edge{
    int from;
    int to;
    int weight;
};

struct Vertex{
    int distance = INF;
    int parent = -1;
};

vector<Edge> edges;
vector<Vertex> vertices;

void bellmanFord(int source){
    int vv = vertices.size();
    int e = edges.size();
    vertices[source].distance = 0;
    for(int i=1;i<vv;i++){
        for(int j=0;j<e;j++){
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].weight;
            if( vertices[u].distance!=INF and vertices[u].distance + w<vertices[v].distance ){
                vertices[v].distance = vertices[u].distance + w;
                vertices[v].parent = u;
            }
        }
    }

    for(int j=0;j<e;j++){
        int u = edges[j].from;
        int v = edges[j].to;
        int w = edges[j].weight;
        if( vertices[u].distance!=INF and vertices[u].distance + w<vertices[v].distance ){
            cout<<"The graph contains a negative cycle";
            exit(0);
        }
    }

}

void printPath(int source,int dest,bool start = false){
    if(source == dest){
        printf("%d->",dest);
        return;
    }
    printPath(source,vertices[dest].parent);
    if( start ) printf("%d",dest);
    else printf("%d->",dest);

}


int main(){
    ifstream cin("graph.in");
    int n,m;
    cin>>n>>m;
    vertices.resize(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }
    int source,dest;
    cin>>source>>dest;
    bellmanFord(source);
    printf("The graph does not contain a negative cycle\nShortest path cost: %d\n",vertices[dest].distance);
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
/*
4 4
0 1 1
1 2 -1
2 3 -1
3 0 -1
0 3
*/
