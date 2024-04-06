#include<bits/stdc++.h>

using namespace std;

int main(){
    int N = 3;
    int arra[N] = {3,1,2};


    int i, key, j;
    for (i = 1; i < N; i++)
    {
        key = arra[i];
        j = i - 1;
        while1:
        if( j<0 ) goto endWhile1;
        if( arra[j]<=key ) goto endWhile1;
        arra[j + 1] = arra[j];
        j = j - 1;
        goto while1;
        endWhile1:
        arra[j + 1] = key;
    }
    for(int i=0;i<N;i++) cout<<arra[i]<<" ";
    cout<<endl;
    int q;
    cin>>q;
    while(q--){

        int a;
        cin>>a;
        int lo = 0,hi = N,mid;
        while2:
            ;
        if( lo>hi ) goto endWhile2;

        mid = (lo+hi)>>1;

        if( arra[mid]!=a ) goto endIf1;

        cout<<"Found in position ";
        cout<<mid<<endl;
        goto label;

        endIf1:

        if( arra[mid]<a ) goto endIf2;

        hi = mid-1;
       goto while2;

        endIf2:

        lo = mid+1;
        goto while2;


        endWhile2:

        cout<<"Not found T - T"<<endl;
        label:
        ;
    }
}
