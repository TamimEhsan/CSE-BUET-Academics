#include<bits/stdc++.h>
using namespace std;
int main(){
    int plantNumber,friendNumber,cost = 0;
    cin>>plantNumber>>friendNumber;
    int plantCosts[plantNumber],plantsBought[friendNumber]={0};
    for(int i=0;i<plantNumber;i++)
        cin>>plantCosts[i];
    // As gradually the cost of plants will increase
    // So, we will buy the cheapest plants later.
    sort(plantCosts,plantCosts+plantNumber,greater<int>());
    for(int i=0;i<plantNumber;i++){
        int friendd = i%friendNumber;
        cost = cost + (plantsBought[friendd]+1)*plantCosts[i];
        plantsBought[friendd]++;
    }
    cout<<cost<<endl;
}
