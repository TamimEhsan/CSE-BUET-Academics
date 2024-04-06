#include<bits/stdc++.h>
using namespace std;

/**
* Generating a uniformly distributed random number with a seed
* @params l   The lower limit of the expected random number
* @params r   The upper limit of the expected random number
* @returns    A random number
*/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r){return uniform_int_distribution<int>(l,r) (rng);}

/**
* Creates an randomized array
* @params values[]    Container array for generated values
* @params n           The size of array
*/
void createRandomArray(int values[],int n){
    for(int i=0;i<n;i++) values[i] = my_rand(0,n*100);
}

/**
* Creates a Ascending ordered randomized array
* @params values[]    Container array for generated values
* @params n           The size of array
*/
void createAscendingArray(int values[],int n){
    values[0] = my_rand(0,100);
    for(int i=1;i<n;i++){
        values[i] = my_rand(values[i-1],values[i-1]+100);   // Adding a random value of [0,100]
                                                            //with previous value to generate a new value
    }
}

/**
* Creates a Descending ordered randomized array
* @params values[]    Container array for generated values
* @params n           The size of array
*/
void createDescendingArray(int values[],int n){
    /*values[0] = my_rand(n*100,n*100-100);
    for(int i=1;i<n;i++){
        values[i] = my_rand(values[i-1]-100,values[i-1]);
    }*/
    values[n-1] = my_rand(0,100);
    for(int i=n-2;i>=0;i--){
        values[i] = my_rand(values[i+1],values[i+1]+100);   // Adding a random value of [0,100]
                                                            //with next value to generate a new value
    }
}

/**
* Takes decision based on the order and returns the generated array
* @params values[]    Container array for generated values
* @params n           The size of array
* @params order       The order of generation of value
*/
void generateArray(int values[],int n,int order){
    if( order == 1 ) createAscendingArray(values,n);
    else if(order == 2) createDescendingArray(values,n);
    else createRandomArray(values,n);
}

