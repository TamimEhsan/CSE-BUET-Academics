#include<bits/stdc++.h>
using namespace std;

#define PI 2.0*acos(0.0)

static unsigned long long int g_seed = 1;
inline int random(){
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}


/*
A color structure
*/
struct Color{
    int r,g,b;
    Color(){
        r = 0;
        g = 0;
        b = 0;
    }

    void set(){
        r = random();
        g = random();
        b = random();
    }
};



/*
A point structure
*/

struct Point{
    double x,y,z,n;

    Point(double x, double y, double z, double n){
        this->x = x;
        this->y = y;
        this->z = z;
        this->n = n;
    }

    Point(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
        this->n = 0.1;
    }
    Point(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->n = 1.0;
    }

    Point(const Point &p) : x(p.x), y(p.y), z(p.z), n(p.n) {}

    Point operator+(Point p){
        return Point(x+p.x, y+p.y, z+p.z);
    }

    Point operator-(Point p){
        return Point(x-p.x, y-p.y, z-p.z);
    }

    Point operator*(double c){
        return Point(x*c, y*c, z*c);
    }

    Point operator/(double c){
        return Point(x/c, y/c, z/c);
    }


    // dot product
    double operator*(Point &p){
        return (x*p.x + y*p.y + z*p.z);
    }

    // cross product
    Point operator^(Point &p){
        return Point(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }

    void scaleDown(){
        x /= n;
        y /= n;
        z /= n;
        n = 1.0;
    }

    double length(){
        return sqrt(x*x + y*y + z*z);
    }

    void normalize(){
        double l = length();
        x /= l;
        y /= l;
        z /= l;
    }

    friend ostream& operator<<(ostream& os, Point& p){
        os << fixed << setprecision(7);
        os << p.x << ", " << p.y << ", " << p.z << ": "<< p.n << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Point& p){
        is >> p.x >> p.y >> p.z;
        p.n = 1.0;
        return is;
    }

    friend ofstream& operator<<(ofstream& os, Point& p){
        os << fixed << setprecision(7);
        os << p.x << " " << p.y << " " << p.z << endl;
        return os;
    }
};


/*
A Triangle structure
*/

struct Triangle{
    Point a,b,c;
    Color color;
    
    Triangle(Point a, Point b, Point c){
        this->a = a;
        this->b = b;
        this->c = c;
    }

    Triangle(){
        this->a = Point();
        this->b = Point();
        this->c = Point();
    }

    void sort(){
        if( b.y < a.y ) swap(a,b);
        if( c.y < a.y ) swap(a,c);
        if( c.y < b.y ) swap(b,c);
    }

    void recolor(){
        color.set();
    }

    friend ostream& operator<<(ostream& os, Triangle& t){
        os << t.a << t.b << t.c;
        return os;
    }

    friend istream& operator>>(istream& is, Triangle& t){
        is >> t.a >> t.b >> t.c;
        return is;
    }

    friend ofstream& operator<<(ofstream& os, Triangle& t){
        os << t.a << t.b << t.c;
        return os;
    }
};


/*
A Matrix structure
*/


Point Rodrigues(Point p, Point a, double theta){
    Point res;
    a.normalize();
    res = p*cos(theta) + a*((a*p)*(1-cos(theta))) + (a^p)*sin(theta);
    return res;
}

struct Matrix{

    double matrix[4][4];

    Matrix(){
        memset(matrix, 0, sizeof(matrix));
    }

    Matrix operator*(Matrix m){
        Matrix res;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                for(int k=0; k<4; k++){
                    res.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
                }
            }
        }
        return res;
    }


    Point operator*(Point p){

        double res[4]={0.0};
        double p2[4]={p.x, p.y, p.z, p.n};

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                res[i] += matrix[i][j] * p2[j];
            }
        }
        Point ret(res[0], res[1], res[2],res[3]);
        ret.scaleDown();
        return ret;
    }

    Triangle operator*(Triangle t){

        Triangle ret;
        ret.a = (*this)*t.a;
        ret.b = (*this)*t.b;
        ret.c = (*this)*t.c;
        return ret;
    }

    void identity(){
        memset(matrix, 0, sizeof(matrix));
        for(int i=0; i<4; i++){
            matrix[i][i] = 1;
        }
    }

    void translate(Point p){
        identity();
        matrix[0][3] = p.x;
        matrix[1][3] = p.y;
        matrix[2][3] = p.z;
    }
    

    void scale(Point p){
        identity();
        matrix[0][0] = p.x;
        matrix[1][1] = p.y;
        matrix[2][2] = p.z;
    }

    void rotate(Point a,double theta){
        a.normalize();
        identity();
        Point i(1.0, 0.0, 0.0), j(0.0, 1.0, 0.0), k(0.0, 0.0, 1.0);
       
        Point c1 = Rodrigues(i, a, theta);
        Point c2 = Rodrigues(j, a, theta);
        Point c3 = Rodrigues(k, a, theta);
        matrix[0][0] = c1.x;  matrix[0][1] = c2.x; matrix[0][2] = c3.x;
        matrix[1][0] = c1.y;  matrix[1][1] = c2.y; matrix[1][2] = c3.y;
        matrix[2][0] = c1.z;  matrix[2][1] = c2.z; matrix[2][2] = c3.z;

    }

    friend ostream& operator<<(ostream& os, const Matrix& m){
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                os << m.matrix[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }


};
