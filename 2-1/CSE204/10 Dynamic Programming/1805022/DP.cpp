#include<bits/stdc++.h>
using namespace std;

#define M 1000'000'007



int main(){
    ifstream cin; cin.open ("qv.txt");
    int n,s;
    cin>>n>>s;
    int faces[n];
    for(int i=0;i<n;i++){
        cin>>faces[i];
        faces[i] = min(faces[i],s);
    }
    if( s == 0 or n == 0 ){
        cout<<0<<endl;
        return 0;
    }
    int cumulativeDP[s+5];
    int cumulativeDP_Next[s+5];
	for(int i=0;i<=s;i++) cumulativeDP[i] = 1;

	for (int i = 1; i <= n; i++){
        memset(cumulativeDP_Next, 0, sizeof(cumulativeDP_Next));
        for (int j = 1; j <= s; j++){
            if( j-faces[i-1]-1<0 ) cumulativeDP_Next[j] = cumulativeDP[j-1];
            else cumulativeDP_Next[j] = ( cumulativeDP[j-1] - cumulativeDP[j-faces[i-1]-1]+ M )%M;
        }
        cumulativeDP[0] = cumulativeDP_Next[0];
        for(int j=1;j<=s;j++) cumulativeDP[j] = (cumulativeDP_Next[j]+cumulativeDP[j-1])%M;
	}

    cout<<(cumulativeDP[s]-cumulativeDP[s-1]+M)%M<<endl;

}




