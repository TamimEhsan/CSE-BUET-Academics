#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r){return uniform_int_distribution<int>(l,r) (rng);}
int randomfunc(int j){return rand() % j;}
const int N = 1000;
const int M = 20000;

vector<int> cons[N];
set<int> consTemp[N];
vector<int> coursesOfSutdents[M];
vector<int> courses[N];

int color[N];
int studentsPerCourse[N];
int courseSaturation[N];
int courseCount;
int studentCount;


void clearData(){
    for(int i=0;i<courseCount;i++){
        consTemp[i].clear();
        cons[i].clear();
    }
}

void readCRSFile(string filename){
    ifstream infile(filename);

    string line;
    courseCount = 0;
    while( getline(infile,line) ){
        stringstream strm(line);
        int courseId,studentOfThisCourse;
        strm>>courseId>>studentOfThisCourse;
        courseId--;
        studentsPerCourse[courseId] = studentOfThisCourse;
        courseCount++;
    }
    infile.close();
    clearData();
}

void readSTUFile(string filename){
    ifstream infile(filename);
    int id = 0;
    studentCount = 0;
    string line;
    while( getline(infile,line) ){
        stringstream strm(line);
        int val;
        coursesOfSutdents[id].clear();
        while( strm>>val ){
            val--;
            coursesOfSutdents[id].push_back(val);
        }
        for(int i=0;i<coursesOfSutdents[id].size();i++){
            for(int j=i+1;j<coursesOfSutdents[id].size();j++){
                consTemp[ coursesOfSutdents[id][i] ].insert( coursesOfSutdents[id][j] );
                consTemp[ coursesOfSutdents[id][j] ].insert( coursesOfSutdents[id][i] );
            }
        }
        id++;
        studentCount++;
        //cout<<endl;
    }
    for(int i=0;i<courseCount;i++){
        for(auto c:consTemp[i]){
            cons[i].push_back(c);
        }
    }
    infile.close();
}


vector<int> visiteds;
int vis[N];

void swapColor(int color1,int color2){
    for(auto u:visiteds){
        if( color[u] == color1 )
            color[u] = color2;
        else color[u] = color1;
    }
}

void kempeChain(int u,int color1,int color2){
    vis[u] = 1;
    visiteds.push_back(u);
    for(auto v:cons[u]){
        if( vis[v] == 0 and (color[v] == color1 or color[v] == color2) ){
            kempeChain(v,color1,color2);
        }
    }
}

int getPenalty(){
    int penalty = 0;
    for(int i=0;i<studentCount;i++){
        for(int j=0;j<coursesOfSutdents[i].size();j++){
            for(int k=j+1;k<coursesOfSutdents[i].size();k++){
                int c1 = coursesOfSutdents[i][j];
                int c2 = coursesOfSutdents[i][k];
                int dif = abs(color[c1] - color[c2]);
                if( dif<=5 ){
                    penalty+= 1<<(5-dif);
                  //  penalty+= 2*(5-dif);
                }
            }
        }
    }
    return penalty;
}

int currentPenalty;

void startKempeChain(){

    int node1 = my_rand(0,courseCount-1);
    while( cons[node1].size()==0 ){
        node1 = my_rand(0,courseCount-1);
    }
    int node2 = my_rand(0, cons[node1].size()-1 );
    node2 = cons[node1][node2];

    int color1 = color[node1];
    int color2 = color[node2];
    visiteds.clear();
    for(int i=0;i<=courseCount;i++)
        vis[i] = 0;

    kempeChain(node1,color1,color2);


    swapColor(color1,color2);
    int newPenalty = getPenalty();

    if( newPenalty>=currentPenalty ){
        swapColor(color1,color2);
    }else{
        currentPenalty = newPenalty;
    }

}


bool pairSwap(int u,int vv){
    for(auto v:cons[u]){
        if( color[v] == color[vv] ) return false;
    }
    for(auto v:cons[vv]){
        if( color[v] == color[u] ) return false;
    }
    return true;
}

int starPairSwap(){
    int cnt = 0;
    for(int i=1;i<=courseCount;i++){
        for(int j=i+1;j<=courseCount;j++){
            bool ret = pairSwap(i,j);
            if( !ret ) continue;
            cnt++;
            swap( color[i],color[j] );

            int newPenalty = getPenalty();
            if( newPenalty>=currentPenalty ){
                swap( color[i],color[j] );
            }else{
                currentPenalty = newPenalty;
            }

        }
    }
    return cnt;
}


int timeSlot = 0;

bool cmpLargestDegree(int a, int b){
    return cons[a].size()>cons[b].size();
}

bool cmpLargestEnrolment(int a,int b){
    return studentsPerCourse[a]>studentsPerCourse[b];
}

bool cmpDsatur(int a,int b){
    if( courseSaturation[a] != courseSaturation[b] )
        return courseSaturation[a] > courseSaturation[b];
    return cons[a].size()>cons[b].size();
}

void getInitialColoring(int ara[]){
    for(int i=0;i<courseCount;i++){
        int curr = ara[i];
        set<int> adjacentColors;
        for(auto v:cons[curr]){
            if( color[v] != 0 )
                adjacentColors.insert( color[v] );
        }
        int targetColor = adjacentColors.size()+1;
        int it = 1;
        for(auto col:adjacentColors){
            if( col!=it ){
                targetColor = it;
                break;
            }
            it++;
        }
        color[curr] = targetColor;
    }
    //for(int i=0;i<5;i++) cout<<i<<" "<<color[ i ]<<endl;

}

void DSatur(){
    int ara[courseCount];
    for(int i=0;i<courseCount;i++)
        ara[i] = i+1;
    for(int i=0;i<courseCount;i++){
        sort(ara+i,ara+courseCount,cmpDsatur);
        int curr = ara[i];
        set<int> adjacentColors;
        for(auto v:cons[curr]){
            if( color[v] != 0 )
                adjacentColors.insert( color[v] );
            courseSaturation[v]++;
        }
        int targetColor = adjacentColors.size()+1;
        int it = 1;
        for(auto col:adjacentColors){
            if( col!=it ){
                targetColor = it;
                break;
            }
            it++;
        }
        color[curr] = targetColor;

    }
}

void randomized(){
    int ara[courseCount];
    for(int i=0;i<courseCount;i++)
        ara[i] = i+1;
    random_shuffle(ara,ara+courseCount);

    for(int i=0;i<courseCount;i++){
        int curr = ara[i];
        set<int> adjacentColors;
        for(auto v:cons[curr]){
            if( color[v] != 0 )
                adjacentColors.insert( color[v] );
        }
        int targetColor = adjacentColors.size()+1;
        int it = 1;
        for(auto col:adjacentColors){
            if( col!=it ){
                targetColor = it;
                break;
            }
            it++;
        }
        color[curr] = targetColor;
    }
}

void startLargestDegreeInitial(){
    int ara[courseCount];
    for(int i=0;i<courseCount;i++)
        ara[i] = i;
    sort(ara,ara+courseCount,cmpLargestDegree);
    getInitialColoring(ara);
}

void startLargestEnrollmentInitial(){
    int ara[courseCount];
    for(int i=0;i<courseCount;i++)
        ara[i] = i;
    sort(ara,ara+courseCount,cmpLargestEnrolment);
    getInitialColoring(ara);
}

void startRandomizedInitial(){
    int ara[courseCount];
    for(int i=0;i<courseCount;i++)
        ara[i] = i;
    random_shuffle(ara,ara+courseCount,randomfunc);
    getInitialColoring(ara);
}

void startProgram(int algo){
    for(int i=0;i<courseCount;i++) color[i] = 0;
    if( algo == 0 ) startLargestDegreeInitial();
    else if( algo == 1 ) DSatur();
    else if( algo == 2 ) startLargestEnrollmentInitial();
    else if( algo == 3 ) startRandomizedInitial();
    int slot = 0;
    for(int i=0;i<courseCount;i++){
        slot = max(slot, color[i] );
    }
    cout<<slot<<",";
    currentPenalty = getPenalty();
    cout<<(double)currentPenalty/studentCount<<",";
    for(int i=0;i<1000;i++){
        startKempeChain();
    }
    cout<<(double)currentPenalty/studentCount<<",";
    for(int i=0;i<1000;i++){
        i+=starPairSwap();
    }
    cout<<(double)currentPenalty/studentCount<<", ,";
}

int main(){
    srand(unsigned(time(0)));
    string fileNames[] = {"car-f-92","car-s-91","kfu-s-93","tre-s-92","yor-f-83"};
    string fileNamesPrint[] = {"CARF92","CARS91","KFU93","TRE92","YOR83"};
    for(int i=0;i<5;i++){
        string fileName = fileNames[i];

        readCRSFile(fileName+".crs");
        readSTUFile(fileName+".stu");

       // cout<<fileNamesPrint[i]<<",";
        for(int j=0;j<4;j++)
            startProgram(j);
        cout<<endl;

    }
}
