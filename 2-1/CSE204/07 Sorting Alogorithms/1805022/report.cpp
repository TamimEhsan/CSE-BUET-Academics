#include<bits/stdc++.h>
#include "generateValues.h"
#include "sort.h"
using namespace std;


int values1[N],values2[N];

int main(){

    // loop through values of 10,100,1000... until 10^6
    for(int n = 10;n<=100000;n*=10){

        int order=3;
        long double time_of_merge_sort = 0;
        long double time_of_quick_sort = 0;

        // Take 10 time and find the average as the time taken
        int j=0;
        for(j=0;j<10;j++){
            generateArray(values1,n,order);
            for(int i=0;i<n;i++) values2[i] = values1[i];

            // Sort using Merge Sort and calculation of time taken
            auto start = chrono::high_resolution_clock::now();
            _sort(values1,n,1);
            auto end = chrono::high_resolution_clock::now();
            long double time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            time_of_merge_sort+=time_taken;

            // Sort using Quick Sort and calculation of time taken
            start = chrono::high_resolution_clock::now();
            _sort(values2,n,2);
            end = chrono::high_resolution_clock::now();
            time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            time_of_quick_sort+=time_taken;

            cout<<"#";
        }
        cout<<endl;
        time_of_merge_sort = (long double)time_of_merge_sort/j;
        time_of_quick_sort = (long double)time_of_quick_sort/j;

        cout << "Time taken by program  for n = "<< n <<" is: "<<endl
            << fixed<<  setprecision(6)
            <<"Merge Sort: "<<time_of_merge_sort<<" milliseconds"<<endl
            <<"Quick Sort: "<<time_of_quick_sort<<" milliseconds"<<endl
            << endl;

    }
}

