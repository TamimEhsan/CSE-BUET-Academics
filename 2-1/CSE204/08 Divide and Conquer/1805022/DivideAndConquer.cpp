#include<bits/stdc++.h>
#include "Point.h"
#include "Sort.h"
using namespace std;

#define INF 2147483647

/**
* Struct where we will store our two solution best and second best
*/
struct Solution{
    long double distance;   //< The calculated distance of two point
    int index1;             //< Index of the first point
    int index2;             //< Index of the second point
}best,second_best;


/**
* Compares with the current best solution and tries to update
* according to the distance between Point A and Point B
*/
void update(Point &A,Point &B){
    long double distance = calculateDistance(A,B);
    if( A.index>B.index ) swap(A,B);
    if( distance<best.distance ){
        second_best = best;
        best = {distance,A.index,B.index};
    }else if( distance<second_best.distance and distance>best.distance ){
        second_best = {distance,A.index,B.index};
    }
}

/**
* Merge step of the divide and conquer approach where we try to combine the
* solution for points in left and right segment
*
* @relatesalso  findClosestPair
* @param strip  Container of points having y-distance from mid
*               no more than second closest distance
*/
void calculateStripDistance(vector<Point> &strip){
    for(int i=0;i<strip.size();i++)
        for(int j=i+1;j<strip.size() and strip[j].y-strip[i].y<second_best.distance;j++)
            update(strip[i],strip[j]);

}

/**
* Recursive function to find second closest point in a set
* Divides the problem into smaller sub problems and merges them to find the solution
*
* @param points Container of points
* @param left   The left boundary of the current checking segment
* @param right  The right boundary of the current checking segment
*/
void findClosestPair(Point points[],int left,int right){
    if( right<left ) return;
    if( right - left + 1 <=3){
        for(int i=left;i<right;i++){
            for(int j=i+1;j<=right;j++)
                update(points[i],points[j]);
        }
        mergeSort(points,left,right,compY);
        return;
    }

    // Divide the problem into two subproblem
    int mid = (left+right)/2;
    Point m = points[mid];
    findClosestPair(points,left,mid); //< We are considering the points on the mid as the left seg
    findClosestPair(points,mid+1,right);

    // Merge the two segment left and right which was sorted according to y-axis
    merge(points,left,mid,right,compY);

    // Store the points which has y distance smaller that the second closest distance
    vector<Point> strip;
    for(int i=left;i<=right;i++){
        if( abs(points[i].x-m.x)<second_best.distance )
            strip.push_back(points[i]);
    }
    calculateStripDistance(strip);
}


int main(){
    ifstream cin;
    cin.open("input.txt");
    int n;
    cin>>n;
    Point points[n];
    for(int i=0;i<n;i++) {
        cin>>points[i].x>>points[i].y;
        points[i].index = i;
    }
    best = second_best = {INF,-1,-1};
    mergeSort(points,0,n-1,compX);     //< Sorts the container according to x coordinate
    findClosestPair(points,0,n-1);
    cout<<fixed<<setprecision(4)<<second_best.index1<<" "<<second_best.index2<<"\n"<<second_best.distance<<endl;
}


/*
10
-2289 9295
3137 3748
-5033 5679
7729 -432
9262 16
8341 -5462
-4163 3577
1710 -3328
-8676 -3161
5106 3295
*/
/*
5
-9765 2172
-4808 7289
955 -2187
9279 -9856
6332 -2249
*/

