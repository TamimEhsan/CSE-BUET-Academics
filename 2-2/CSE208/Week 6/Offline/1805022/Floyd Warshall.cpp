#include<bits/stdc++.h>
using namespace std;

const int INF = 100000005;
int main(){
    ifstream cin("input.in");
    int n,m;
    cin>>n>>m;
    int distance[n+1][n+1];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            if( i == j ) distance[i][j] = 0;
            else distance[i][j] = INF;

    while(m--){
        int u,v,w;
        cin>>u>>v>>w;
        distance[u][v] = w;
    }

    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if( distance[i][k] + distance[k][j]< distance[i][j] )
                    distance[i][j] = distance[i][k] + distance[k][j];
    cout<<"Shortest distance matrix\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            if( distance[i][j] == INF ) cout<<"INF ";
            else cout<<distance[i][j]<<" ";
        cout<<endl;
    }
}
