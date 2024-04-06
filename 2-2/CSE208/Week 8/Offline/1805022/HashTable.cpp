#include<bits/stdc++.h>
using namespace std;
#define M 1000000007
#define ll long long
#define pii pair<int,int>
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r){return uniform_int_distribution<int>(l,r) (rng);}
int my_randd(int r){return my_rand(0,r);}

const int MAX = 10;
ll mods[4] = {1000000007, 1000000009,7919,1000000021};
ll bases[] = {137,281,31,43,47};



ll hashFucntion(string s,int k){
    ll hash = 0;
    for(ll i = s.size() - 1; i >= 0; i--){
        hash = (hash * bases[k] + s[i]) % mods[k];
    }
    return hash;
}



//const int N = 10007;
//const int N = 20011;
const int N = 50159;
string randoms[N];

void createRandomStrings(){
    int cnt = 0;
    map<string,int> check;
    while(cnt<N){
        string s = "";
        for(int i=0;i<7;i++){
            s+=(char)(my_rand(0,25)+'a');
        }
        if( check[s] == 1 ) continue;
        check[s] = 1;
        randoms[cnt++] = s;
    }
}

int randomInts[1007];
void createRandomIndices(){
    int cnt = 0;
    map<int,int> check;
    while(cnt<1000){
        int rnd = my_rand(0,9999);
        if( check[rnd] == 1 ) continue;
        check[rnd] = 1;
        randomInts[cnt++] = rnd;
    }
}
struct ChainingHash{
    int tableSize;
    int h;
    list<pair<string,int>> hashTable[N];
    int collisions = 0;
    int probes = 0;

    ChainingHash(int sz,int _h){
        tableSize = sz;
        h = _h;
    }
    ChainingHash(){
        ChainingHash(N,0);
    }

    void createHashTable(){
        collisions = 0;
        for(int i=0;i<N;i++){
            hashTable[i].clear();
        }
        for(int i=0;i<10000;i++){
            int hashIndex = hashFucntion(randoms[i],h)%tableSize;
            hashTable[hashIndex].push_back({randoms[i],i+1});
            if(hashTable[hashIndex].size()>1 )collisions++;
          //  cout<<i<<"! ";
        }

    }

    void calculateProbes(){
        probes = 0;
        for(int i=0;i<1000;i++){
            int k = randomInts[i];
            if(k>=10000) cout<<"something went wrong "<<endl;
            int hashIndex = hashFucntion(randoms[k],h)%tableSize;
            bool found = false;
            for(auto it=hashTable[hashIndex].begin();it!=hashTable[hashIndex].end();it++){
                probes++;
                if( it->first == randoms[k] ){
                    found = true;
                    break;
                }

            }
            //cout<<i<<"< ";
            if(!found){
                cout<<"something went wrong"<<endl;
                exit(0);
            }
        }
    }
    void Delete(string k){
        int hashIndex = hashFucntion(k,h)%tableSize;
        for(auto it=hashTable[hashIndex].begin();it!=hashTable[hashIndex].end();it++){
            if( it->first == k ){
                hashTable[hashIndex].erase(it);
                break;
            }
        }
    }
};

struct DoubleHash{
    int tableSize;
    int h;
    pair<string,int> hashTable[N];
    int collisions = 0;
    int probes = 0;
    DoubleHash(int sz,int _h){
        tableSize = sz;
        h = _h;
    }
    DoubleHash(){
        DoubleHash(N,0);
    }
    void createHashTable(){
        collisions = 0;
        for(int i=0;i<N;i++) hashTable[i] = {"",0};
        for(int k=0;k<10000;k++){
            int i=0;
            while( true ){
                int hashIndex = (hashFucntion(randoms[k],h) + i*hashFucntion(randoms[k],2))%tableSize;
                if( hashTable[hashIndex].second == 0 ){
                    hashTable[hashIndex] = {randoms[k],k};
                    break;
                }
                i++;
                collisions++;
                if( i>tableSize ) {
                    cout<<"In loop; terminating"<<endl;
                    exit(0);
                }
            }
            //if( k%1000 == 0 ) cout<<k<<endl;
        }
    }

    void calculateProbbes(){
        probes = 0;
        for(int kk=0;kk<1000;kk++){
            int k = randomInts[kk];
            if(k>=10000) cout<<"somethingwentwrong"<<endl;
            int i=0;
            while( true ){
                int hashIndex = (hashFucntion(randoms[k],h) + i*hashFucntion(randoms[k],2))%tableSize;
                if( hashTable[hashIndex].first == randoms[k] ){
                    break;
                }
                i++;
                probes++;
            }
        }
    }
    void Delete(string k){
        int i=0;
        while( true ){
            int hashIndex = (hashFucntion(k,h) + i*hashFucntion(k,2))%tableSize;
            if( hashTable[hashIndex].first == k ){
                hashTable[hashIndex] = {"",0};
                break;
            }
            i++;
            if( i>tableSize ) {
                break;
            }
        }
    }
};

struct CustomProbing{
    int tableSize;
    int h;
    pair<string,int> hashTable[N];
    int collisions = 0;
    int probes = 0;
    CustomProbing(int sz,int _h){
        tableSize = sz;
        h = _h;
    }
    CustomProbing(){
        CustomProbing(N,0);
    }
    void createHashTable(){
        collisions = 0;
        for(int i=0;i<N;i++) hashTable[i] = {"",0};
        for(int k=0;k<10000;k++){
            int i=0;
            while( true ){
                int hashIndex = (hashFucntion(randoms[k],h) + mods[3]*i*hashFucntion(randoms[k],2) + mods[4]*i*i)%tableSize;
                if( hashTable[hashIndex].second == 0 ){
                    hashTable[hashIndex] = {randoms[k],k};
                    break;
                }
                i++;
                collisions++;
                if( i>tableSize ) {
                    cout<<"In loop; terminating"<<endl;
                    exit(0);
                }
            }
        }
    }

    void calculateProbbes(){
        probes = 0;
        for(int kk=0;kk<1000;kk++){
            int k = randomInts[kk];
            int i=0;
            while( true ){
                int hashIndex = (hashFucntion(randoms[k],h) + mods[3]*i*hashFucntion(randoms[k],2) + mods[4]*i*i)%tableSize;
                if( hashTable[hashIndex].first == randoms[k] ){
                    break;
                }
                i++;
                probes++;
            }
        }
    }
    void Delete(string k){
        int i=0;
        while( true ){
            int hashIndex = (hashFucntion(k,h) + mods[3]*i*hashFucntion(k,2) + mods[4]*i*i)%tableSize;
            if( hashTable[hashIndex].first == k ){
                hashTable[hashIndex] = {"",0};
                break;
            }
            i++;
            if( i>tableSize ) {
                break;
            }
        }
    }
};

int main(){
    Preprocess();

    int tableSize = N;
    cout<<"input the Hash Table size:"<<endl;
    cin>>tableSize;
    while(tableSize<10000){
        cout<<"Table size must be greater than 10000"<<endl;
        cout<<"input the Hash Table size:"<<endl;
        cin>>tableSize;
    }

    createRandomStrings();
    createRandomIndices();

    for(int i=0;i<2;i++){

        ChainingHash chainingHash(tableSize,i);
        DoubleHash doubleHash(tableSize,i);
        CustomProbing customProbing(tableSize,i);

        cout<<endl<<"=====Hash "<<i+1<<"====="<<endl;
        chainingHash.createHashTable();
        doubleHash.createHashTable();
        customProbing.createHashTable();

        cout<<"Hash Table Created\n";
        chainingHash.calculateProbes();
        doubleHash.calculateProbbes();
        customProbing.calculateProbbes();

        cout<<"Chaining Method "<<chainingHash.collisions<<" "<<(chainingHash.probes/1000.0)<<endl;
        cout<<"Double Hashing  "<<doubleHash.collisions<<" "<<(doubleHash.probes/1000.0)<<endl;
        cout<<"Custom Probing  "<<customProbing.collisions<<" "<<(customProbing.probes/1000.0)<<endl;

    }

}
