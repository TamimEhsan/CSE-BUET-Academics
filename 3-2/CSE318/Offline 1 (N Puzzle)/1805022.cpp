#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define ll long long
#define aa first
#define bb second
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
#define pie acos(-1)
#define MOD 1000000007

#define ld long double
#define eps 1e-9
#define endl '\n'

int k,n;
map<vector<int>,int> id;
int idCount = 2;


vector<int> d,g,p;


vector<int> start,endd;
vector<int> rowPos,colPos;
vector<vector<int>> states;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
pair<int,int> getCoord(int node){
    int r = node/k;
    int c =node%k;
    return {r,c};
}
int getLinear(int x,int y){
    return x*k+y;
}

int calculateManhattan(vector<int> &node){
    int manhattan = 0;
    for(int i=0;i<node.size();i++){
        auto [r,c] = getCoord(i);
        int val = node[i];
        if( val == 0 ) continue;
        manhattan += abs( r-rowPos[val] ) + abs( c-colPos[val] );
    }
    return manhattan;
}
int calculateHamming(vector<int> &node){
    int hamming = 0;
    for(int i=0;i<node.size()-1;i++){
        if( node[i]!=endd[i] )
            hamming++;
    }
    return hamming;
}
int expanded,explored;

void clean(){
    expanded = explored = 0 ;
    idCount = 2;
    d.clear(); p.clear(); id.clear(); states.clear();
    d.push_back(0);d.push_back(0);d.push_back(-1);
    p.push_back(-1);p.push_back(-1);p.push_back(-1);
    id[start] = 1;
    id[endd] = 2;

    states.push_back(start);
    states.push_back(start);
    states.push_back(endd);
}

void astar(int (*heuristic) (vector<int>&)) {
   // function<int(vector<vector<int>>)> heuristic = func;
    clean();
    d[1] = 0;

    priority_queue< pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,1});
    while (!pq.empty()) {

        int v = pq.top().second;

        explored++;
        if( v == 2 ){
            return;
        }
        pq.pop();
        int zero;
        for(int i=0;i< states[v].size();i++ ){
            if( states[v][i] == 0 ) zero = i;
        }
        auto [ux,uy] = getCoord(zero);
        for (int edge=0;edge<4;edge++) {
            int vx = ux+dx[edge];
            int vy = uy+dy[edge];
            if( vx<0 or vy<0 or vx>=k or vy>=k ) continue;
            int nextPos = getLinear(vx,vy);
            vector<int> nextState = states[v];
            swap(nextState[zero],nextState[nextPos]);
            if( id.count(nextState) == 0 ){
                id[nextState] = ++idCount;
                states.push_back(nextState);
                d.push_back(-1);
                p.push_back(-1);

            }
            int to = id[nextState];
            if (d[to] == -1 or  d[v] + 1 < d[to]) {
                d[to] = d[v] + 1;
                p[to] = v;
                pq.push({d[to]+heuristic(nextState), to});
                expanded++;
            }
        }
    }

}


void printPath(int node,int &step){
    if( node!=1 ) printPath(p[node],step);
    cout<<endl;
    cout<<step++<<"============="<<node<<endl;
    for(int i=0;i<n;i++){
        if( states[node][i] == 0 )
            cout<<"* ";
        else
            cout<<states[node][i]<<" ";
        if( (i+1)%k == 0 ) cout<<endl;
    }


}


bool isSolvable(int zeroPos){
     auto [x,y] = getCoord(zeroPos);
    int inversion = 0;
    for(int i=0;i<n;i++){
        if( start[i] == 0 ) continue;
        for(int j=0;j<i;j++){
            if( start[j] == 0 ) continue;
            if( start[j]>start[i] ) inversion++;
        }
    }
    if( k%2 == 0 and inversion%2 == x%2 ){
        return false;
    }else if( k%2 == 1 and inversion%2 == 1 ){
        return false;
    }
    return true;
}


void init(){
    int val = 1;
    rowPos.resize(n+1);
    colPos.resize(n+1);
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            endd.push_back(val);
            rowPos[val] = i;
            colPos[val] = j;
            val++;
        }
    }
    endd[endd.size()-1] = 0;
    rowPos[0] = k-1;
    colPos[0] = k-1;

}
int processNumber(string val){
    int num = 0;
    for(auto c:val){
        int d = c-'0';
        num = num*10 + d;
    }
    return num;
}
int main(){

   // FASTIO;
    cin>>k;
    n = k*k;
    init();
    int zeroPos = 0;
    for(int i=0;i<n;i++){
        string val;
        cin>>val;
        int num = 0;
        if( val == "*" ) zeroPos = i;
        else num = processNumber(val);
        start.push_back(num);
    }

    if( !isSolvable(zeroPos) ){
        cout<<"This puzzle is not solvable.\n";
        return 0;
    }

    astar(calculateHamming);
    cout<<"\nHamming "<<endl;
    cout<<"expanded "<<expanded<<endl;
    cout<<"explored "<<explored<<endl;
    astar(calculateManhattan);
    cout<<"\nManhattan "<<endl;
    cout<<"expanded "<<expanded<<endl;
    cout<<"explored "<<explored<<endl;
    int step = 1;
    printPath(2,step);

}


/*
3
* 1 3 4 2 5 7 8 6
3
0 2 3 1 4 5 8 7 6
4
1 2 8 11 9 3 6 14 4 7 12 10 5 15 13 0
4
2 3 4 0
1 5 7 8
9 6 10 12
13 14 11 15

3
0 3 2
1 4 5
8 7 6

4
1 9 2 3
5 12 11 10
13 6 0 8
7 14 15 4

4
2 3 0 8 15 12 6 7 13 1 4 9 14 11 10 5
*/



// https://acm.timus.ru/problem.aspx?space=1&num=1599


//  268522JW
