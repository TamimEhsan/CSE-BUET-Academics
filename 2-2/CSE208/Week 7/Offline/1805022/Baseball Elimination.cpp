#include<bits/stdc++.h>
using namespace std;

#define INF 100000

struct Team{
    string name;
    int wins;
    int losses;
    int rem;
    vector<int> games;
};

#define SOURCE 1
#define SINK 2
#define MATCH 3
#define VERTEX 4
struct Vertex{
    int type;
    int v;
    int v2;
    int index;

};
bool operator==(Vertex A,Vertex B){
    return A.index == B.index;

}
vector<vector<Vertex>> adj;
vector<vector<int>> capacity;

int bfs(Vertex s, Vertex t, int current, vector<int>& parent,vector<vector<int>>& capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s.index] = -2;
    queue<pair<Vertex, int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        Vertex cur = q.front().first;
        int flow = q.front().second;
        q.pop();
       // for (Vertex next : adj[cur.index]) {
        for (int ind = 0;ind<adj[cur.index].size();ind++) {
            Vertex next = adj[cur.index][ind];
            if( next.v == current or next.v2 == current ) {
                continue;
            }
            if (parent[next.index] == -1 && capacity[cur.index][next.index]>0) {
                parent[next.index] = cur.index;
                int new_flow = min(flow, capacity[cur.index][next.index]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}


bool isEliminated(int currentTeam,int n,vector<Vertex> vertices,Team teams[]){
    int s = n;
    int t = n+1;
    int flow = 0;
    vector<int> parent(vertices.size());
    int new_flow;
    vector<vector<int>> newCapacity;
    newCapacity = capacity;
    for(int i=0;i<n;i++){
        // VERTEX to SINK
        if( i == currentTeam )
            continue;
        newCapacity[i][n+1] += teams[currentTeam].wins+teams[currentTeam].rem;
        if( newCapacity[i][n+1]<=0 ) return true;
    }
    while (new_flow = bfs(vertices[n],vertices[n+1],currentTeam, parent,newCapacity)) {
        flow += new_flow;
        int current = t;
        while (current != s) {
            int prev = parent[current];
            newCapacity[prev][current] -= new_flow;
            newCapacity[current][prev] += new_flow;
            current = prev;
        }
    }
    int requiredFlow = 0;
    int totFlow = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            totFlow+=teams[i].games[j];
            if( i == currentTeam or j == currentTeam ) continue;
            requiredFlow+=teams[i].games[j];
        }
    }
    return flow!=requiredFlow;
}

int main(){
    ifstream cin("teams29.txt");
    int n;
    cin>>n;
    Team teams[n];
    for(int i=0;i<n;i++){
        string name;
        int w,l,r;
        vector<int> g;
        cin>>name>>w>>l>>r;
        for(int j=0;j<n;j++){
            int remGame;
            cin>>remGame;
            g.push_back(remGame);
        }
        teams[i] = {name,w,l,r,g};
    }

    vector<Vertex> vertices;
    for(int i=0;i<n;i++){
        vertices.push_back({VERTEX,i,-1,vertices.size()});
    }
    vertices.push_back({SOURCE,-1,-1,vertices.size()});
    vertices.push_back({SINK,-1,-1,vertices.size()});
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            vertices.push_back({MATCH,i,j,vertices.size()});
        }
    }
    adj.resize(vertices.size(),vector<Vertex>());
    capacity.resize(vertices.size(),vector<int>());
    for(int i=0;i<capacity.size();i++)
        capacity[i].resize(vertices.size(),0);

    for(int i = n+2;i<vertices.size();i++){
        // MATCH to VERTEX
        adj[i].push_back( vertices[vertices[i].v] );
        adj[i].push_back( vertices[vertices[i].v2] );
        capacity[i][vertices[i].v] = INF;
        capacity[i][vertices[i].v2] = INF;
        // SOURCE to MATCH
        adj[n].push_back(vertices[i]);
        capacity[n][i] = teams[vertices[i].v].games[vertices[i].v2];

        // reverse graph
        //  VERTEX TO MATCH
        adj[vertices[i].v].push_back( vertices[i] );
        adj[vertices[i].v2].push_back( vertices[i] );

        // MATCH TO SOURCE
        adj[i].push_back(vertices[n]);

    }
    for(int i=0;i<n;i++){
        // VERTEX to SINK
        adj[i].push_back(vertices[n+1]);
        capacity[i][n+1] = -teams[i].wins;

        // REVERSE GRAPH
         //  SINK TO VERTEX
        adj[n+1].push_back(vertices[i]);

    }

    for(int i=0;i<n;i++){
        if( isEliminated(i,n,vertices,teams) ){
            cout<<teams[i].name<<" is eliminated."<<endl;
        }
    }

}



/*
4
Atlanta 83 71 8 0 1 6 1
Philadelphia 80 79 3 1 0 0 2
New_York 78 78 6 6 0 0 0
Montreal 77 82 3 1 2 0 0
*/

/*
teams29
teams30
*/
