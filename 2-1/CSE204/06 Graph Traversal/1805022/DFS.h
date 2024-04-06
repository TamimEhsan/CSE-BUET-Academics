#include <vector>
#include <fstream>
using namespace std;

class DFS{
    //Fields
    int cityCount;
    vector<vector<int>> adj;
    vector<bool> isVisited; // Visited state of each node
    vector<int> gems;
    vector<int> friends;
    //Methods
    int dfs(int u);
public:
    DFS(vector<vector<int>> _adj,vector<int>_gems,vector<int> _friends);
    void start();
};

/**
* Constructor
* params _adj Adjacency list of graph
* params _gems Number of gems located in each city
* params _friends The starting position of each collectors
*/
DFS::DFS(vector<vector<int>> _adj,vector<int>_gems,vector<int> _friends){

    adj = _adj;
    gems = _gems;
    friends = _friends;

    int cityCount = adj.size();
    isVisited.resize(cityCount,false);
}

/**
* Starting point of DFS graph traversal for each collector
*/
void DFS::start(){

    int totalGem = 0;
    int gemsCollected[friends.size()];
    int totalGemCollected = 0;

    for(int gem:gems)
        totalGem+=gem;

    for(int i=0;i<friends.size();i++){
        int gem = dfs(friends[i]);
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
* Recursive function for DFS prefix graph traversal
* params u current position of journey
* returns gem_collected The number of gems collected from the subtree
*/
int DFS::dfs(int u){

    int gem_collected = gems[u];

    gems[u] = 0;
    isVisited[u] = true;

    for(int v:adj[u]){
        if( !isVisited[v] )
            gem_collected+=dfs(v);
    }

    return gem_collected;
}
