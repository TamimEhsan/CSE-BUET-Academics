#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r){return uniform_int_distribution<int>(l,r) (rng);}


// Hash function 
struct hashFunction{
    size_t operator()( const pii &x  ) const {
        return x.first*17+x.second;
    }
};

vector<int> process(string s){
    vector<int> vv;
    bool ss = false;
    int val = 0;
    for(auto c:s){
        if( c>='0' and c<='9' ){
             val = val*10 +c-'0';
             ss = true;
        }
        else if( ss ){
            vv.push_back(val);
            val = 0;
            ss = false;
        }
    }
    if( ss ) vv.push_back(val);
    return vv;
}

int n;
int nodes,backtrackNodes;
vector<vector<int>> board;
vector<vector<int>> puzzle;
vector<vector<int>> constraints;
vector<vector<set<int>>> domain;
set<pii> emptyCells;
//unordered_set<pii,hashFunction> emptyCells;
//vector<vector<unordered_set<int>>> domain;

// add a variable called mxForward size


vector<pii> getEmptyCells(){
    vector<pii> emptyCells;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if( board[i][j] == 0 )
                emptyCells.push_back({i,j});
    return emptyCells;
}

vector<int> getRemaningValues(int x,int y){
    vector<int> remainingValues;
    int taken[n+1] = {0};
    for(int i=0;i<n;i++){
        taken[ board[x][i] ] = 1;
        taken[ board[i][y] ] = 1;
    }
    for(int i=1;i<=n;i++)
        if( !taken[i] )
            remainingValues.push_back( i );
    return remainingValues;

}



vector<pii> removeValueFromDomain(int x,int y,int val){
    vector<pii> cells;
    for(int i=0;i<n;i++){
        if( board[i][y] != 0 or i == x or domain[i][y].count(val) == 0 ) continue;
        cells.push_back({i,y});
        domain[i][y].erase( domain[i][y].find(val));
    }
    for(int i=0;i<n;i++){
        if( board[x][i] != 0 or i == y or domain[x][i].count(val) == 0 ) continue;
        cells.push_back({x,i});
        domain[x][i].erase( domain[x][i].find(val));
    }
    return cells;
}

void restoreValueToDomain(vector<pii> &cells,int val){
    for(auto [x,y]:cells)
        domain[x][y].insert(val);
}

bool checkConsistency(int x,int y,int val){
    for(int i=0;i<n;i++){
        if( i == y or board[x][i]!=0 ) continue;
       // auto remainingValues = getRemaningValues(x,i);
        if( domain[x][i].size() == 1 and *domain[x][i].begin() == val ) return false;
    }
    for(int i=0;i<n;i++){
        if( i == x or board[i][y]!=0 ) continue;
       // auto remainingValues = getRemaningValues(i,y);
        if( domain[i][y].size() == 1 and *domain[i][y].begin() == val ) return false;
    }
    return true;
}


void decreaseConstraints(int x,int y){
    for(int i=0;i<n;i++){
        if( i!=x and board[i][y] == 0 ) constraints[i][y]--;
        if( i!=y and board[x][i] == 0 ) constraints[x][i]--;
    }
}

void increaseConstraints(int x,int y){
    for(int i=0;i<n;i++){
        if( i!=x and board[i][y] == 0 ) constraints[i][y]++;
        if( i!=y and board[x][i] == 0 ) constraints[x][i]++;
    }
}

inline int getVAH1(int x,int y){
    return domain[x][y].size();
}


int calculateVAH2(int x,int y){
    int dependent = 0;
    for(int i=0;i<n;i++){
        if( i!=x and board[i][y] == 0 ) dependent++;
        if( i!=y and board[x][i] == 0 ) dependent++;
    }
    //assert(dependent>=2);
    return dependent;
}
inline int getVAH2(int x,int y){
   // return calculateVAH2(x,y);
    return constraints[x][y];
}

inline double getVAH4(int x,int y){
    int v1 = getVAH1(x,y);
    int v2 = getVAH2(x,y);
    if( v2 == 0 ) return 100000000;
    return (double) v1/v2;
}

pii getPositionByVAH1(){
    pii chose = {-1,-1};
    int mn = -1;
    for(auto [x,y]:emptyCells){
        int vah1 = getVAH1(x,y);
        if( mn == -1 or vah1<mn ){
            mn = vah1;
            chose = {x,y};
        }
    }
    return chose;
}

pii getPositionByVAH2(){
    pii chose = {-1,-1};
    int mx = -1;
    for(auto [x,y]:emptyCells){
        int vah2 = getVAH2(x,y);
        if( mx == -1 or vah2>mx ){
            mx = vah2;
            chose = {x,y};
        }
    }
    return chose;
}

pii getPositionByVAH3(){
    pii chose = {-1,-1};
    int vah1mn = -1;
    int vah2mx = -1;
    for(auto [x,y]:emptyCells){
        int vah1 = getVAH1(x,y);
        int vah2 = getVAH2(x,y);
        if( vah1mn == -1 or ( vah1<vah1mn ) or ( vah1 == vah1mn and vah2 > vah2mx ) ){
            vah1mn = vah1;
            vah2mx = vah2;
            chose = {x,y};
        }
    }
    return chose;
}

pii getPositionByVAH4(){
    pii chose = {-1,-1};
    double mx = -1;
    bool chosen = false;
    for(auto [x,y]:emptyCells){
        double vah4 = getVAH4(x,y);
        if( !chosen or vah4<mx ){
            mx = vah4;
            chosen = true;
            chose = {x,y};
        }
    }
    return chose;
}

pii getPositionByVAH5(){
    int pos = my_rand(0,emptyCells.size()-1);
    int it=0;
    for(auto p:emptyCells){
        if( it == pos ) return p;
        it++;
    }
    return *emptyCells.begin();
}

void getLeastConstrainedValue(int x,int y,vector<pii> &dom){
    for(auto &d:dom){
        int cnt = 0;
        int val = d.second;
        for(int i=0;i<n;i++){
            if( i == y or board[x][i]!=0 ) continue;

            if( domain[x][i].count(val) == 1 ) cnt++;;
        }
        for(int i=0;i<n;i++){
            if( i == x or board[i][y]!=0 ) continue;

            if( domain[i][y].count(val) == 1  ) cnt++;
        }
        d.first = cnt;
    }
}

bool backtrackWithoutForwardChecking(pii (*heuristic) ()){
    nodes++;

    if( emptyCells.size() == 0 ) return true;
    auto [px,py] = heuristic();


    vector<pii> dom;
    for(auto val:domain[px][py]) dom.push_back({0,val});
    if( dom.size() == 0 ){
        backtrackNodes++;
        return false;
    }
    decreaseConstraints(px,py);
    getLeastConstrainedValue(px,py,dom);
    sort(dom.begin(),dom.end());
    emptyCells.erase( emptyCells.find({px,py}) );
    for(auto [lsv,posibleValue]:dom){
        auto removedCells = removeValueFromDomain(px,py,posibleValue);
        board[px][py] = posibleValue;

        bool ret = backtrackWithoutForwardChecking(heuristic);
        if( ret ) return true;
        restoreValueToDomain(removedCells,posibleValue);
    }
    board[px][py] = 0;
    emptyCells.insert( {px,py} );
    increaseConstraints(px,py);

    return false;

}





bool backtrackWithForwardChecking(pii (*heuristic) ()){
    nodes++;

    if( emptyCells.size() == 0 ) return true;

    auto [px,py] = heuristic();


    vector<pii> dom;
    for(auto val:domain[px][py]) dom.push_back({0,val});
    decreaseConstraints(px,py);
    getLeastConstrainedValue(px,py,dom);
    sort(dom.begin(),dom.end());
    emptyCells.erase( emptyCells.find({px,py}) );
    for(auto [lsv,posibleValue]:dom){

        if( !checkConsistency(px,py,posibleValue) ) {
            backtrackNodes++;
            continue;
        }
        auto removedCells = removeValueFromDomain(px,py,posibleValue);
        board[px][py] = posibleValue;

        bool ret = backtrackWithForwardChecking(heuristic);
        if( ret ) return true;
        restoreValueToDomain(removedCells,posibleValue);

    }
    board[px][py] = 0;
    emptyCells.insert( {px,py} );
    increaseConstraints(px,py);

    return false;

}




void recalculateDomain(){
    emptyCells.clear();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            domain[i][j].clear();
            if( board[i][j] != 0 ) domain[i][j].insert( board[i][j] );
            else{
                emptyCells.insert({i,j});
                constraints[i][j] = calculateVAH2(i,j);
                auto rem = getRemaningValues(i,j);
                //cout<<"val::"<<i<<" "<<j<<endl;
                for(auto r:rem) {
                    domain[i][j].insert(r);
                    //cout<<r<<" ";
                }
               // cout<<endl;
            }
        }
    }
}
void initBoard(){
    nodes = 0;
    backtrackNodes = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            board[i][j] = puzzle[i][j];
        }
    recalculateDomain();
}

bool startCall(int algorithmChose,int heuristicChose){
    initBoard();
    if( algorithmChose == 1 ){
        if( heuristicChose == 1 ){
           return backtrackWithoutForwardChecking(getPositionByVAH1);
        } else if( heuristicChose == 2 ){
           return backtrackWithoutForwardChecking(getPositionByVAH2);
        }else if( heuristicChose == 3 ){
           return backtrackWithoutForwardChecking(getPositionByVAH3);
        }else if( heuristicChose == 4 ){
           return backtrackWithoutForwardChecking(getPositionByVAH4);
        }else if( heuristicChose == 5 ){
           return backtrackWithoutForwardChecking(getPositionByVAH5);
        }
    }else{
        if( heuristicChose == 1 ){
           return backtrackWithForwardChecking(getPositionByVAH1);
        } else if( heuristicChose == 2 ){
           return backtrackWithForwardChecking(getPositionByVAH2);
        }else if( heuristicChose == 3 ){
           return backtrackWithForwardChecking(getPositionByVAH3);
        }else if( heuristicChose == 4 ){
           return backtrackWithForwardChecking(getPositionByVAH4);
        }else if( heuristicChose == 5 ){
           return backtrackWithForwardChecking(getPositionByVAH5);
        }
    }
    return false;
}


int main(){
    ifstream cin("d-10-07.txt");
    // ifstream cin("input.in");
    int algo = 2;
    int vah = 4;

	string s;
    getline(cin,s);
    auto retv = process(s);
    if( retv.size()>=1 ) n = retv[0];
    board.resize(n);
    puzzle.resize(n);
    domain.resize(n);
    constraints.resize(n);

    for(int i=0;i<n;i++){
        board[i].resize(n);
        puzzle[i].resize(n);
        domain[i].resize(n);
        constraints[i].resize(n);
    }
    int i = 0;
    while(getline(cin,s)){
        auto ret = process(s);
        if( ret.size()!=n or i>=n ) continue;
        for(int j=0;j<n;j++)
            puzzle[i][j] = ret[j];
        i++;
	}
    cout<<"started"<<endl;
    auto start = chrono::high_resolution_clock::now();
    bool ret = startCall(algo   ,vah  );
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout<<"time taken for \nalgorithm "<<" with heuristic "<<" is "<< duration.count() <<" milliseconds"<<endl;

    cout<<endl<<nodes<<" "<<backtrackNodes<<endl;;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}
