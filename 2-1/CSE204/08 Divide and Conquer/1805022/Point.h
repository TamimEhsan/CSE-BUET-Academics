/**
* This Point.h contains the structure of point
* and all related function associated with it
*/


/**
* Struct of a 2D point in Euclidean plane
*/
struct Point{
    int x;      //< The x coordinate of the point
    int y;      //< The y coordinate of the point
    int index;  //< Index of the point in container
};

/**
* Calculates the Euclidean distance between two point A and B
*/
long double calculateDistance(Point &A,Point &B){
    int val = (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
    return sqrt(val);
}

/**
* Compares two point A and B for ascending order along X axis
* @relatesalso  sort.h/merge
* @returns       boolean value representing the order of point A and B
*/
bool compX(Point &A,Point &B){
    if( A.x!=B.x ) return A.x<B.x;
    return A.y<B.y;
}

/**
* Compares two point A and B for ascending order along Y axis
* @relatesalso  sort.h/merge
* @returns      boolean value representing the order of point A and B
*/
bool compY(Point &A,Point &B){
    if(A.y!=B.y) return A.y<B.y;
    return A.x<B.x;
}
