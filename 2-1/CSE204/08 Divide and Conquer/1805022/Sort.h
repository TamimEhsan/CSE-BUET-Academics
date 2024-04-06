/**
* This sort.h contains function which is used for merge sort
*/

#include<bits/stdc++.h>
using namespace std;



/**
* Merge step of two recursively sorted segment of array in merge sort
*
* @relatesalso  sort.h/mergeSort
* @tparam T     The type of data that needs to be sorted
* @param values The container of the data of type T
* @param left   The left boundary of the first segment
* @param mid    The partition index of the two segment
* @param right  The right boundary of the second segment
* @param comp   The comparision function which determines the order of values
*/
template <typename T>
void merge(T values[],int left,int mid,int right, bool (*comp)(T&,T&)){
    int numL = mid-left+1;
    int numR = right - mid;
    T tempL[numL+5],tempR[numR+5];
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
            if( comp(tempL[itL],tempR[itR]) ){
                values[pos++] = tempL[itL++];
            }else{
                values[pos++] = tempR[itR++];
            }
        }
    }
}

/**
* Recursive function which divides and sorts the container in two segment
* and sorts them independently and later combines them in merge
*
* @tparam T     The type of data that needs to be sorted
* @param values The container of the data of type T
* @param left   The left boundary of the first segment
* @param right  The right boundary of the second segment
* @param comp   The comparision function which determines the order of values
*/
template <typename T>
void mergeSort(T values[],int left,int right,bool (*comp)(T&,T&)){
    if( left >= right ) return;
    int mid = (left+right)/2;
    mergeSort(values,left,mid,comp);
    mergeSort(values,mid+1,right,comp);
    merge(values,left,mid,right,comp);
}
