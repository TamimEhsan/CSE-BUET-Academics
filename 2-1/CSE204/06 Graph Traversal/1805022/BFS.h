#include<iostream>
#include<queue>
#include <fstream>

using namespace std;

class BFS{
    // Fields
    int cityCount;
    vector<vector<int>> adj;
    vector<bool> isVisited; // Visited state of each node
    vector<int> gems;
    vector<int> friends;
    // Methods
    int bfs(int start);
public:
    BFS(vector<vector<int>> _adj,vector<int>_gems,vector<int> _friends);
    void start();
};

/**
* Constructor
* params _adj Adjacency list of graph
* params _gems Number of gems located in each city
* params _friends The starting position of each collectors
*/
BFS::BFS(vector<vector<int>> _adj,vector<int>_gems,vector<int> _friends){

    adj = _adj;
    gems = _gems;
    friends = _friends;

    int cityCount = adj.size();

    isVisited.resize(cityCount,false);
}

/**
* Starting point of BFS graph traversal for each collector
*/
void BFS::start(){

    int totalGem = 0;
    int totalGemCollected = 0;
    int gemsCollected[friends.size()];

    for(int gem:gems)
        totalGem+=gem;

    for(int i=0;i<friends.size();i++){
        int gem = bfs(friends[i]);
        gemsCollected[i] = gem;
        totalGemCollected+=gem;
    }
    ofstream fout;
    fout.open ("example.txt");

    fout<<(totalGem == totalGemCollected?"Mission Accomplished":"Mission Impossible")<<endl;
    fout<<totalGemCollected<<" out of "<<totalGem<<" pieces are collected"<<endl;

    for(int i=0;i<friends.size();i++){
        fout<<i<<" collected "<<gemsCollected[i]<<" pieces"<<endl;
    }
    fout.close();
}

/**
* BFS graph traversal for a specific starting point
* params start The starting location of traversal
* return gem_collected The number of gems collected for this walk
*/
int BFS::bfs(int start){

    int gem_collected = 0;
    queue<int> q;

    if(isVisited[start])
        return 0;

    isVisited[start] = true;
    q.push(start);

    while(!q.empty()){

        int u = q.front();

        q.pop();
        gem_collected+=gems[u];
        gems[u] = 0;

        for(int v:adj[u]){
            if( !isVisited[v] ){
                q.push(v);
                isVisited[v] = true;
            }
        }
    }

    return gem_collected;
}
