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
vector<Vertex>vertices;

void dfs(int u,bool vis[],vector<vector<int>>& capacity,int currentTeam){
    vis[u] = true;
    for(int i=0;i<adj[u].size();i++){
        int v = adj[u][i].index;
        if( vertices[v].v == currentTeam or vertices[v].v2 == currentTeam ) continue;
        if( !vis[v] and capacity[u][v]>0 )
            dfs(v,vis,capacity,currentTeam);
    }
}
int bfs(Vertex s, Vertex t, int current, vector<int>& parent,vector<vector<int>>& capacity) {

    fill(parent.begin(), parent.end(), -1);
    parent[s.index] = -2;
    queue<pair<Vertex, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        Vertex cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (Vertex next : adj[cur.index]) {
            if( next.v == current or next.v2 == current ) continue;

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


vector<int> isEliminated(int currentTeam,int n,Team teams[]){

    int s = n, t = n+1, flow = 0, new_flow;
    vector<int> parent(vertices.size());
    vector<vector<int>> newCapacity;
    newCapacity = capacity;
    for(int i=0;i<n;i++){
        // VERTEX to SINK
        if( i == currentTeam )
            continue;
        newCapacity[i][n+1] += teams[currentTeam].wins+teams[currentTeam].rem;
        if( newCapacity[i][n+1]<0 ) {
            return {i};
        }
    }
    while (new_flow = bfs(vertices[n],vertices[n+1],currentTeam, parent,newCapacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            newCapacity[prev][cur] -= new_flow;
            newCapacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    vector<int> unbeatens;
    bool vis[vertices.size()] = {0};
    dfs(s,vis,newCapacity,currentTeam);
    for(int i=n+2;i<vertices.size();i++){
        if( vis[i] == 1 ){
            unbeatens.push_back( vertices[i].v );
            unbeatens.push_back( vertices[i].v2 );
        }
    }
    sort(unbeatens.begin(), unbeatens.end());
    unbeatens.erase(unique(unbeatens.begin(), unbeatens.end()), unbeatens.end());
    return unbeatens;
}

void addEdge(int u,int v,int cap){
    adj[u].push_back(vertices[v]);
    capacity[u][v] = cap;
    // REVERSE GRAPH
    adj[v].push_back(vertices[u]);
}


void printDeduction(Team teams[],int i,vector<int>& res){
    cout<<teams[i].name<<" is eliminated."<<endl;
    printf("They can win at most %d + %d = %d games.\n",teams[i].wins,teams[i].rem,teams[i].wins+teams[i].rem);
    int interGames = 0;
    int totWin = 0;
    for(int j=0;j<res.size();j++){
        totWin+=teams[ res[j] ].wins;
        for(int k=j+1;k<res.size();k++)
            interGames+=teams[ res[j] ].games[ res[k] ];
    }
    for(int j=0;j<res.size();j++){
        cout<<teams[ res[j] ].name;
        if( j == res.size()-2 ) cout<<" and ";
        else if( j !=res.size()-1 ) cout<<" , ";
        else cout<<" ";
    }
    printf("has won a total of %d games\nThey play each other %d times\nSo on average, each of the teams wins %d/%d = %0.1f games.\n\n",totWin,interGames,totWin+interGames,res.size(),(double)(totWin+interGames)/res.size());

}

int main(){
    ifstream cin("input.in");
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
    /**
        vertices
        0 to n-1 => Vertex
        n => Source
        n+1 => Sink
        n+2 to end => Match
    */
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

    /**
        Edge graph adj
    */
    for(int i = n+2;i<vertices.size();i++){
        // MATCH to VERTEX
        addEdge(i,vertices[i].v,INF);
        addEdge(i,vertices[i].v2,INF);
        // SOURCE to MATCH
        addEdge(n,i,teams[vertices[i].v].games[vertices[i].v2]);
    }
    for(int i=0;i<n;i++){
        // VERTEX to SINK
        addEdge(i,n+1, -teams[i].wins);
    }

    for(int i=0;i<n;i++){
        vector<int> unbeatens = isEliminated(i,n,teams);
        if( unbeatens.size() ){
            printDeduction(teams,i,unbeatens);
        }
    }

}


