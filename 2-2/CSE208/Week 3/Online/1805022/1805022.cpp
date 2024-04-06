#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
vector<int> topsort;
int vis[maxn];
vector<int> adj[maxn];
void dfs(int u){
    vis[u] = 1;
    for(int i=0;i<adj[u].size();i++){
        int v = adj[u][i];
        if( vis[v] == 0 ) dfs(v);
    }
    topsort.push_back(u);
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
    }
    for(int i=0;i<n;i++)
        if( vis[i] == 0 ) dfs(i);
    reverse(topsort.begin(),topsort.end());
    fill(vis,vis+n+5,0);
    dfs(topsort[0]);
    for(int i=0;i<n;i++){
        if( vis[i] == 0 ){
            cout<<-1;
            return 0;
        }
    }
    cout<<topsort[0]<<endl;
    return 0;
}
