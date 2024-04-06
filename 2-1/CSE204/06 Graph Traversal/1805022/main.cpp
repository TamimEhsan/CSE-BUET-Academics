#include<iostream>
#include <vector>
#include <fstream>
#include "DFS.h"
#include "BFS.h"

using namespace std;


int main(){

    int C,R,L,F;
    cin>>C>>R>>L>>F;
    vector<vector<int>> adj(C,vector<int>());
    vector<int> gems(C,0);
    vector<int> friends(F,0);
    while(R--){
        int c1,c2;
        cin>>c1>>c2;
        adj[c1].push_back(c2);
        adj[c2].push_back(c1);
    }
    for(int i=0;i<L;i++){
        int cx,px;
        cin>>cx>>px;
        gems[cx] = px;
    }
    for(int i=0;i<F;i++){
        int cy,fy;
        cin>>cy>>fy;
        friends[fy] = cy;
    }

    //DFS dfs(adj,gems,friends);
   // dfs.start();

    BFS bfs(adj,gems,friends);
    bfs.start();
}
/*
10 8 4 3
0 4
0 1
2 0
2 1
1 3
6 5
5 7
9 8
0 5
3 6
5 3
9 2
4 0
7 2
2 1
*/
/*
10 8 4 3
0 4
0 1
2 0
2 1
1 3
6 5
5 7
9 8
0 5
3 6
5 3
9 2
4 0
7 2
8 1
*/
