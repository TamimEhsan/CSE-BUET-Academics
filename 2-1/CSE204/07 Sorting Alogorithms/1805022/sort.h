#include<bits/stdc++.h>

using namespace std;

// Using global array for greated heap value
const int N = 10000005;
int tempL[N],tempR[N];


void mergeSort(int values[],int left,int right);
void quickSort(int arr[], int low, int high);

/**
* Calls the sorting function based on params
* @params values    The container to be sorted
* @params n         Size of the data
* @params algo      The type of algorithm with which the
                    data is to be sorted
*/
void _sort(int values[],int n,int algo){
    if( algo == 1 )
        mergeSort(values,0,n-1);
    else
        quickSort(values,0,n-1);
}

/**
* Merges two sorted partition created by Merge Sort
* @params values    The container of data
* @params left      The starting index of data of the first half
* @params mid       The index of partition of two half
* @params right     The ending index of the second half
*/
void merge(int values[],int left,int mid,int right){

    int numL = mid-left+1;
    int numR = right - mid;

    for(int i=0;i<numL;i++){
        tempL[i] = values[left+i];
    }
    for(int i=0;i<numR;i++){
        tempR[i] = values[mid+1+i];
    }

    int itL = 0,itR = 0,pos = left;
    while( itL < numL or itR < numR ){
        if( itL == numL ){
            values[pos++] = tempR[itR++];
        }else if( itR == numR ){
            values[pos++] = tempL[itL++];
        }else{
            if( tempL[itL]<=tempR[itR] ){
                values[pos++] = tempL[itL++];
            }else{
                values[pos++] = tempR[itR++];
            }
        }
    }
}

/**
* Recursive function of Merge Sort to sort two half of data seperately
* @params values    The container of data
* @params left      The starting index of data of the first half
* @params right     The ending index of the second half
*/
void mergeSort(int values[],int left,int right){
    if( left >= right ) return;
    int mid = (left+right)/2;
    mergeSort(values,left,mid);
    mergeSort(values,mid+1,right);
    merge(values,left,mid,right);
}

/**
* Finds the partition point of between two index w
* @params values    The container of data
* @params left      The starting index of data of the first half
* @params right     The ending index of the second half
* returns           The index with all small left values and greater right values
*/
int getPartition(int values[],int left,int right){
    //int rnd = my_rand(left,right);
    //swap(values[rnd],values[right]);
    int pivot = values[right];
    int it = left-1;
    for(int j=left;j<=right-1;j++){
        if( values[j]<pivot ){
            it++;
            swap( values[it],values[j] );
        }
    }
    swap(values[it+1],values[right]);
    return it+1;
}

/**
* Recursive function of Quick Sort to sort two half of data seperately
* @params values    The container of data
* @params left      The starting index of data of the first half
* @params right     The ending index of the second half
*/
void quickSort(int values[],int left,int right){
    if( left>=right ) return;
    int partition = getPartition(values,left,right); // partition the array into two part
    if(left<partition-1)
        quickSort(values,left,partition-1);
    if(partition+1<right)
        quickSort(values,partition+1,right);
}

