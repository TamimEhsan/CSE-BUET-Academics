#include<bits/stdc++.h>
#include "generateValues.h"
#include "sort.h"
using namespace std;


// Global container of generated randomized data
int mergeArray[N],quickArray[N];

int main(){

    while(true){
        int n,order;
        cout<<"Input n(0 to quit):"<<endl;
        cin>>n;
        if( n ==0  ){
            return 0;
        } else if( n<0 ){
            cout<<"Error!"<<endl;
            continue;
        }
        cout<<"Input order:\n1 :Ascending order\n2 :Descending order\n3: Random Order"<<endl;
        cin>>order;
        if( order<=0 or order>3 ){
            cout<<"Error!"<<endl;
            continue;
        }

        // Generating the arrays of size n and of the preferred order
        generateArray(mergeArray,n,order);
        for(int i=0;i<n;i++) quickArray[i] = mergeArray[i];


        // Sort using Merge Sort and calculation of time taken
        auto startTimer = chrono::high_resolution_clock::now();
        _sort(mergeArray,n,1);
        auto endTimer = chrono::high_resolution_clock::now();
        long double time_taken_for_merge_sort = chrono::duration_cast<chrono::milliseconds>(endTimer - startTimer).count(); // Calculating time in milliseconds

        cout << "Time taken by Merge Sort is : " << fixed
             << time_taken_for_merge_sort << setprecision(9);
        cout << " milliseconds" << endl;


        // Sort using Merge Sort and calculation of time taken
        startTimer = chrono::high_resolution_clock::now();
        _sort(quickArray,n,2);
        endTimer = chrono::high_resolution_clock::now();
        long double time_taken_for_quick_sort = chrono::duration_cast<chrono::milliseconds>(endTimer - startTimer).count();

        cout << "Time taken by Quick Sort is : " << fixed
             << time_taken_for_quick_sort << setprecision(9);
        cout << " milliseconds" << endl;


        // Printing the after sort state of the arrays
        cout<<"Merge Sort\tQuick Sort\n";
        for(int i=0;i<n;i++) cout<<mergeArray[i]<<"\t\t"<<quickArray[i]<<endl; cout<<endl;
        cout<<"sort status:\n"
            <<(is_sorted(mergeArray,mergeArray+n) == true? "sorted" : "unsorted" )<<"\t\t"
            <<(is_sorted(quickArray,quickArray+n)== true?  "sorted" : "unsorted" )<<endl;

    }
}
