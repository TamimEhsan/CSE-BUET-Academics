#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class Object;
struct Color;
struct Ray;
Color captureColor(Ray ray,int level);


extern vector <Object*> objects;
extern bool enableTexture;


static unsigned long long int g_seed = 1;
inline int my_random(){
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}


/*
A color structure
*/
struct Color{
    double r,g,b;
    Color(){
        r = 0;
        g = 0;
        b = 0;
    }

    Color(double r,double g,double b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
    Color operator*(double c){
        return Color(r*c, g*c, b*c);
    }
    Color operator+(Color c){
        return Color(r+c.r, g+c.g, b+c.b);
    }
    void set(){
        r = my_random();
        g = my_random();
        b = my_random();
    }

    void cutoff(){
        if( r<0 ) r = 0;
        if( g<0 ) g = 0;
        if( b<0 ) b = 0;
        if( r>1 ) r = 1;
        if( g>1 ) g = 1;
        if( b>1 ) b = 1;
    }

    friend istream& operator>>(istream& is, Color& color){
        is >> color.r >> color.g >> color.b;
        return is;
    }

    friend ostream& operator<<(ostream& os, Color& color){
        os << fixed << setprecision(7);
        os << color.r << " " << color.g << " " << color.b << endl;
        return os;
    }
};


/*
A coeeficient structure
*/

struct Coefficients{
    double ambient, diffuse, specular, reflection;
    int shine;
    friend istream& operator>>(istream& is, Coefficients& coeff){
        is >> coeff.ambient >> coeff.diffuse >> coeff.specular >> coeff.reflection >> coeff.shine;
        return is;
    }

    friend ostream& operator<<(ostream& os, Coefficients& coeff){
        os << fixed << setprecision(7);
        os << coeff.ambient << " " << coeff.diffuse << " " << coeff.specular << " " << coeff.reflection << " " << coeff.shine << endl;
        return os;
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
    double operator*(Point p){
        return (x*p.x + y*p.y + z*p.z);
    }

    // cross product
    Point operator^(Point p){
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
A Ray class
*/

struct Ray{
    Point start, dir;

    // constructor

    Ray(){
        start = Point(0,0,0);
        dir = Point(0,0,0);
    }

    Ray(Point start, Point dir){
        this->start = start;
        this->dir = dir;
    }


    void normalize(){
        dir.normalize();
    }

    

    friend ostream& operator<<(ostream& os, Ray& ray){
        os << fixed << setprecision(7);
        os << "start: " << ray.start << endl;
        os << "dir: " << ray.dir << endl;
        return os;
    }
};

/*
A Normal Light class
*/

struct NormalLight{
    Point light_pos;
    double falloff;

    void draw(){
        // draw solid sphere   
       
        glPushMatrix();{
            glColor3f(1, 1, 1);
            glTranslatef(light_pos.x, light_pos.y, light_pos.z);
            glutSolidSphere(10, 30, 20);
        }glPopMatrix();

    }

     friend istream& operator>>(istream& is, NormalLight& nlight){
        is >> nlight.light_pos >> nlight.falloff;
        return is;
    }

    friend ofstream& operator<<(ofstream& os, NormalLight& nlight){
        os << fixed << setprecision(7);
        os << "Normal light" << endl;
        os << "position: " << nlight.light_pos << endl;
        os << "falloff: " << nlight.falloff << endl;
        return os;
    }
};


/*
A Spot light class
*/

struct SpotLight{
    Point light_pos;
    double falloff;
    Point look;
    double cutoff;


    void draw(){
        // draw cone 
        double height = 50;
        double radius = height*tan(cutoff*acos(-1)/180.0);

        // rotate 

        glPushMatrix();{
            glColor3f(1, 1, 1);
             glTranslatef(light_pos.x, light_pos.y + height, light_pos.z);
            // //glRotatef(90, 1, 0, 0);
            // rotate to look
            Point up(0,0,1);
            Point dir = look - light_pos;
            dir.normalize();
            Point axis = up^dir;
            axis.normalize();
            double angle = acos(up*dir);
            glRotatef(angle*180.0/acos(-1), axis.x, axis.y, axis.z);
            glRotatef(180,0,1,0);
            
            glutSolidCone(radius, height, 30, 20);
        }glPopMatrix();

        // draw sphere
        // glPushMatrix();{
        //     glColor3f(1, 0, 1);
        //     glTranslatef(light_pos.x, light_pos.y, light_pos.z);
        //     glutSolidSphere(10, 30, 20);
        // }glPopMatrix();


        
    }

    friend istream& operator>>(istream& is, SpotLight& slight){
        Point inp;
        is >> slight.light_pos >> slight.falloff >> inp >> slight.cutoff;
        slight.look = inp - slight.light_pos;
        slight.look.normalize();
        return is;
    }

    friend ofstream& operator<<(ofstream& os, SpotLight& slight){
        os << fixed << setprecision(7);
        os << "spotlight" << endl;
        os << "position: " << slight.light_pos << endl;
        os << "falloff: " << slight.falloff << endl;
        os << "direction: " << slight.look << endl;
        os << "cutoff: " << slight.cutoff << endl;
        return os;
    }
   
};

extern vector <NormalLight*> lights;
extern vector <SpotLight*> spotlights;

/*
A base class for all objects

*/

class Object{
public:
    //vector3D referemce_point;
    double height, width, length;
    Color color;
    Coefficients coEfficients;
    

    virtual void draw(){}

    virtual double firstLevelIntersect(Ray ray, Color &color, int level){
        return -1.0;
    }

    virtual Point getNormal(Point p,Ray ray){
        return Point(0,0,0);
    }


    virtual Color getColorAtPoint(Point p){
        return color;
    }

    double getTriangleArea(Point a,Point b,Point c){
        Point ab = b-a;
        Point ac = c-a;
        Point n = ab^ac;
        return n.length()/2.0;
    }

    bool pointInsideTriangle(Point a,Point b,Point c,Point q){
        double area = getTriangleArea(a,b,c);
        double alpha = getTriangleArea(q,b,c)/area;
        double beta = getTriangleArea(a,q,c)/area;
        double gamma = getTriangleArea(a,b,q)/area;
        if( alpha+beta+gamma > 1.0000001 ) return false;
        return true;
    }

    double rayTriangleIntersection(Point a, Point b, Point c, Ray ray){

       //cout<<"dhukse"<<endl;

        //cout<<a<<" "<<b<<" "<<c<<endl;
       // cout<<"ray dir "<<ray.dir<<endl;
        Point ab = b-a;
        Point ac = c-a;
        Point n = ab^ac;
        n.normalize();
        double d = n*a;
        //cout<<"n: "<<n<<endl;
        int ret = n*ray.dir;
        //cout<<"is parallel: "<<ret<<endl;
        if( n*ray.dir == 0 ) return -1.0; // parallel
      
        double t = ( d - n*ray.start ) / (ray.dir*n);
        Point q = ray.start + ray.dir*t;
       
        if( pointInsideTriangle(a,b,c,q) ) return t;
        
        return -1.0;
    }

    double intersect(Ray ray, Color &color, int level){

        double t = firstLevelIntersect(ray, color, level);
        
        if( t<0 ) return -1.0;
        Point q = ray.start + ray.dir*t;
        Color intersectionPointColor = getColorAtPoint(q);
        color= intersectionPointColor;
        

        color = intersectionPointColor*coEfficients.ambient;
        
        Color ambientColor = intersectionPointColor*coEfficients.ambient;
        double lambert = 0;
        double phong = 0;
        for(int i=0;i<lights.size();i++){
            Point light_pos = lights[i]->light_pos;
            double falloff = lights[i]->falloff;
            Point dir = light_pos - q;
            double t = dir.length();
            dir.normalize();
            Ray r(q+dir*0.0001, dir);
            bool blocked = false;
            for(int j=0;j<objects.size();j++){
                double t2 = objects[j]->firstLevelIntersect(r, color, 0);
                if( t2>0 and t2<t ) { blocked = true; break; }
            }
            if( blocked ) continue;
            if( ray.start.z*light_pos.z < 0 ) continue;
            double distance = t;
            double scalingFactor = exp(-falloff*distance*distance);
            Point toSource = light_pos - q;
            toSource.normalize();
            

            lambert += ( toSource*getNormal(q, r) )*scalingFactor;
           // if( lambert<0 ) lambert = 0;
            
            Ray reflectedRay;
            reflectedRay.start = q;
            reflectedRay.dir = ray.dir - getNormal(q, r)*(2*(ray.dir*getNormal(q, r)));
            reflectedRay.dir.normalize();
            reflectedRay.start = reflectedRay.start + reflectedRay.dir*0.0001;
            
            phong += pow( reflectedRay.dir*toSource, coEfficients.shine )*scalingFactor;
            
            
        }

        
        for(int i=0;i<spotlights.size();i++){
            Point light_pos = spotlights[i]->light_pos;
            double falloff = spotlights[i]->falloff;
            Point dir = light_pos - q;
            double t = dir.length();
            dir.normalize();
            Ray r(q+dir*0.0001, dir);
            bool blocked = false;
            for(int j=0;j<objects.size();j++){
                double t2 = objects[j]->firstLevelIntersect(r, color, 0);
                if( t2>0 and t2<t ) { blocked = true; break; }
            }
            if( blocked ) continue;
            if( ray.start.z*light_pos.z < 0 ) continue;
            
            Point toSource = q - light_pos;
            toSource.normalize();
            Point look = spotlights[i]->look;
            look.normalize();
            double angle = acos(look*toSource)*180.0/acos(-1);
            if( angle > spotlights[i]->cutoff ) continue;

            double distance = t;
            double scalingFactor = exp(-falloff*distance*distance);
            toSource = light_pos - q;
            toSource.normalize();
            lambert += ( toSource*getNormal(q, r) )*scalingFactor;

            Ray reflectedRay;
            reflectedRay.start = q;
            reflectedRay.dir = ray.dir - getNormal(q, r)*(2*(ray.dir*getNormal(q, r)));
            reflectedRay.dir.normalize();
            reflectedRay.start = reflectedRay.start + reflectedRay.dir*0.0001;
            
            phong += pow( reflectedRay.dir*toSource, coEfficients.shine )*scalingFactor;

        }
        Color diffuseColor = intersectionPointColor*coEfficients.diffuse*lambert;
        Color specularColor = intersectionPointColor*coEfficients.specular*phong;

            
        color = ambientColor + diffuseColor + specularColor;

        if( level == 0 ){
            return t;
        }

        Ray reflectedRay;
        reflectedRay.start = q;
        reflectedRay.dir = ray.dir - getNormal(q, ray)*(2*(ray.dir*getNormal(q, ray)));
        reflectedRay.dir.normalize();
        reflectedRay.start = reflectedRay.start + reflectedRay.dir*0.0001;
        
        Color reflectedColor = captureColor(reflectedRay, level-1);
        reflectedColor = reflectedColor*coEfficients.reflection;

        color = color + reflectedColor;

        return t;
    }

};


/*
A Spehere class
*/

struct Sphere: public Object{
    Point center;
    double radius;

    void draw(){
        glPushMatrix();{
            glColor3f(color.r, color.g, color.b);
            glTranslatef(center.x, center.y, center.z);
            glutSolidSphere(radius, 30, 20);
        }glPopMatrix();

    }

    Point getNormal(Point p,Ray ray){
        Point ret = p - center;
        ret.normalize();
        if( ret*ray.dir < 0 ) ret = ret*(-1.0);
        return ret;
    }

    double firstLevelIntersect(Ray r, Color &color, int level){
        color = this->color;
        Point start = r.start;
        Point dir = r.dir;
        Point oc = start - center;
        double a = dir*dir;
        double b = 2*(oc*dir);
        double c = oc*oc - radius*radius;
        double d = b*b - 4*a*c;
        if( d<0 ) return -1.0;
        d = sqrt(d);
        double t1 = (-b+d)/(2*a);
        double t2 = (-b-d)/(2*a);
        if( t1<0 && t2<0 ) return -1.0;
        if( t1<0 ) return t2;
        if( t2<0 ) return t1;
        if( t1<t2 ) return t1;
        return t2;
        return -1.0;
    }



    friend istream& operator>>(istream& is, Sphere& sphere){
        is >> sphere.center >> sphere.radius >> sphere.color;
        is >> sphere.coEfficients;
        return is;
    }

    friend ostream& operator<<(ostream& os, Sphere& sphere){
        os << fixed << setprecision(7);
        os << "Sphere" << endl;
        os << "center: " << sphere.center << endl;
        os << "radius: " << sphere.radius << endl;
        os << "color: " << sphere.color << endl;
        os << "coefficients: " << sphere.coEfficients << endl;
        return os;
    }

};


/*
A Pyramid class
*/

struct Pyramid: public Object{
    Point basePoint;
    Point p[5];
    double height, width;

    void draw(){
        
        // base
        glBegin(GL_QUADS);{
            glColor3f(color.r, color.g, color.b);
            for(int i=0;i<4;i++)
                glVertex3f(p[i].x, p[i].y, p[i].z);
        }glEnd();

        // front
        for(int i=0;i<4;i++){
            glBegin(GL_TRIANGLES);{
                glColor3f(color.r, color.g, color.b);
                glVertex3f(p[i].x, p[i].y, p[i].z);
                glVertex3f(p[(i+1)%4].x, p[(i+1)%4].y, p[(i+1)%4].z);
                glVertex3f(p[4].x, p[4].y, p[4].z);
            }glEnd();
        }
    }
    Point getNormal(Point q,Ray ray){

        // base
        if( pointInsideTriangle(p[0],p[1],p[2],q) ) {
            Point n = (p[1]-p[0])^(p[2]-p[0]);
            n.normalize();
            if( n*ray.dir < 0 ) n = n*(-1.0);
            return n;
        }

        // sides
        for(int i=0;i<4;i++){
            if( pointInsideTriangle(p[i], p[(i+1)%4], p[4], q) ){
                Point n = (p[(i+1)%4]-p[i])^(p[4]-p[i]);
                n.normalize();
                if( n*ray.dir < 0 ) n = n*(-1.0);
                return n;
            }
        }

        return Point(0,0,0);
    }

    double firstLevelIntersect(Ray ray, Color &color, int level){
        
        // base
        double tMin = -1;
        double t = rayTriangleIntersection(p[0], p[1], p[2], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 
        t = rayTriangleIntersection(p[0], p[2], p[3], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 

        // sides
        for(int i=0;i<4;i++){
            t = rayTriangleIntersection(p[i], p[(i+1)%4], p[4], ray);
            if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 
        }
        return tMin;
    }

    friend istream& operator>>(istream& is, Pyramid& pyramid){
        is >> pyramid.basePoint;
        is >> pyramid.width >> pyramid.height;
        is >> pyramid.color;
        is >> pyramid.coEfficients;
        
        pyramid.p[0] = pyramid.basePoint;
        pyramid.p[1] = pyramid.basePoint + Point(pyramid.width, 0, 0);
        pyramid.p[2] = pyramid.basePoint + Point(pyramid.width, pyramid.width, 0);
        pyramid.p[3] = pyramid.basePoint + Point(0, pyramid.width, 0);
        pyramid.p[4] = pyramid.basePoint + Point(pyramid.width/2, pyramid.width/2, pyramid.height);

        return is;
    }

    friend ostream& operator<<(ostream& os, Pyramid& pyramid){
        os << fixed << setprecision(7);
        os << "Pyramid" << endl;
        os << "base point: " << pyramid.basePoint << endl;
        os << "width: " << pyramid.width << endl;
        os << "height: " << pyramid.height << endl;
        os << "color: " << pyramid.color << endl;
        os << "coefficients: " << pyramid.coEfficients << endl;
        return os;
    }
};


/*
A Cube class
*/

struct Cube: public Object{
    Point basePoint;
    double side;

    Point bottom[4];
    Point top[4];

    void draw(){
        // draw cube here with bottom left corner at basePoint
        glBegin(GL_QUADS);{
            glColor3f(color.r, color.g, color.b);
            for(int i=0;i<4;i++)
                glVertex3f(top[i].x, top[i].y, top[i].z);
        }glEnd();
      
        // bottom
        glBegin(GL_QUADS);{
            glColor3f(color.r, color.g, color.b);
            for(int i=0;i<4;i++)
                glVertex3f(bottom[i].x, bottom[i].y, bottom[i].z);
        }glEnd();
        
        // top
        

        // sides
        for(int i=0;i<4;i++){
            glBegin(GL_QUADS);{
                glColor3f(color.r, color.g, color.b);
                glVertex3f(bottom[i].x, bottom[i].y, bottom[i].z);
                glVertex3f(bottom[(i+1)%4].x, bottom[(i+1)%4].y, bottom[(i+1)%4].z);
                glVertex3f(top[(i+1)%4].x, top[(i+1)%4].y, top[(i+1)%4].z);
                glVertex3f(top[i].x, top[i].y, top[i].z);
            }glEnd();
        }

        // glPushMatrix();{
        //     glColor3f(color.r, color.g, color.b);
        //     glTranslatef(basePoint.x, basePoint.y, basePoint.z);
        //     glTranslatef(side/2, side/2, side/2);
        //     glutSolidCube(side);
        // }glPopMatrix();

    }

    Point getNormal(Point q, Ray ray){
        if( pointInsideTriangle(top[0],top[1],top[2],q) ){
            Point n = (top[1]-top[0])^(top[2]-top[0]);
            n.normalize();
            if( n*ray.dir < 0 ) n = n*(-1.0);
            return n;
        }
        if( pointInsideTriangle(top[0],top[2],top[3],q) ){
            Point n = (top[2]-top[0])^(top[3]-top[0]);
            n.normalize();
            if( n*ray.dir < 0 ) n = n*(-1.0);
            return n;
        }
        if( pointInsideTriangle(bottom[0],bottom[1],bottom[2],q) ){
            Point n = (bottom[1]-bottom[0])^(bottom[2]-bottom[0]);
            n.normalize();
            if( n*ray.dir < 0 ) n = n*(-1.0);
            return n;
        }
        if( pointInsideTriangle(bottom[0],bottom[2],bottom[3],q) ){
            Point n = (bottom[2]-bottom[0])^(bottom[3]-bottom[0]);
            n.normalize();
            if( n*ray.dir < 0 ) n = n*(-1.0);
            return n;
        }
        for(int i=0;i<4;i++){
            if( pointInsideTriangle(bottom[i],bottom[(i+1)%4],top[(i+1)%4],q) ){
                Point n = (bottom[(i+1)%4]-bottom[i])^(top[(i+1)%4]-bottom[i]);
                n.normalize();
                if( n*ray.dir < 0 ) n = n*(-1.0);
                return n;
            }
            if( pointInsideTriangle(bottom[i],top[(i+1)%4],top[i],q) ){
                Point n = (top[(i+1)%4]-bottom[i])^(top[i]-bottom[i]);
                n.normalize();
                if( n*ray.dir < 0 ) n = n*(-1.0);
                return n;
            }
        }
        return {0,0,0};
    }

    double firstLevelIntersect(Ray ray, Color &color, int level){
        //cout<<"cube intersect"<<endl;
        Point q;
        // top

        double tMin = -1;
        double t = rayTriangleIntersection(top[0], top[1], top[2], ray);
        
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 
        t = rayTriangleIntersection(top[0], top[2], top[3], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 
        
        // bottom
        t = rayTriangleIntersection(bottom[0], bottom[1], bottom[2], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 
        t = rayTriangleIntersection(bottom[0], bottom[2], bottom[3], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t; 

        
        // sides
        for(int i=0;i<4;i++){
            t = rayTriangleIntersection(bottom[i], bottom[(i+1)%4], top[(i+1)%4], ray);
            if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t;
            t = rayTriangleIntersection(bottom[i], top[(i+1)%4], top[i], ray);
            if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t;
        }
        
        return tMin;
    }

    friend istream& operator>>(istream& is, Cube& cube){
        is >> cube.basePoint;
        is >> cube.side;
        is >> cube.color;
        is >> cube.coEfficients;

        cube.bottom[0] = cube.basePoint;
        cube.bottom[1] = cube.basePoint + Point(cube.side, 0, 0);
        cube.bottom[2] = cube.basePoint + Point(cube.side, cube.side, 0);
        cube.bottom[3] = cube.basePoint + Point(0, cube.side, 0);

        cube.top[0] = cube.basePoint + Point(0, 0, cube.side);
        cube.top[1] = cube.basePoint + Point(cube.side, 0, cube.side);
        cube.top[2] = cube.basePoint + Point(cube.side, cube.side, cube.side);
        cube.top[3] = cube.basePoint + Point(0, cube.side, cube.side);

        return is;
    }

    friend ostream& operator<<(ostream& os, Cube& cube){
        os << fixed << setprecision(7);
        os << "Cube" << endl;
        os << "base point: " << cube.basePoint << endl;
        os << "side: " << cube.side << endl;
        os << "color: " << cube.color << endl;
        os << "coefficients: " << cube.coEfficients << endl;
        return os;
    }

};

struct Floor: public Object{
    Point basePoint;
    double side;

    Point p[4];
    

    
    void draw(){
       
        // draw cube here with bottom left corner at basePoint
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                // draw grid
                glBegin(GL_QUADS);{
                    glColor3f( (i+j)%2, (i+j)%2, (i+j)%2);
                    glVertex3f(basePoint.x+i*side, basePoint.y+j*side, basePoint.z);
                    glVertex3f(basePoint.x+i*side, basePoint.y+(j+1)*side, basePoint.z);
                    glVertex3f(basePoint.x+(i+1)*side, basePoint.y+(j+1)*side, basePoint.z);
                    glVertex3f(basePoint.x+(i+1)*side, basePoint.y+j*side, basePoint.z);
                }; glEnd();
            }
        }
    }

    Color getColorAtPoint(Point q){
        int i = (q.x-basePoint.x)/side;
        int j = (q.y-basePoint.y)/side;
        Color white(1,1,1);
        Color black(0,0,0);
        if( (i+j)%2 == 0 ) return black;
        return white;
    }

    Point getNormal(Point q, Ray ray){
        Point n(0,0,1);
        if( n*ray.dir < 0 ) n = n*(-1.0);
        return n;
    }

    double firstLevelIntersect(Ray ray, Color &color, int level){
        Point q;
        // top
        double tMin = -1;
        double t = rayTriangleIntersection(p[0], p[1], p[2], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t;
        t = rayTriangleIntersection(p[0], p[2], p[3], ray);
        if( t>0 and ( tMin == -1 or t<tMin ) ) tMin = t;
        return tMin;
    }


    friend ifstream& operator>>(ifstream& is, Floor& floor){
        
        is >> floor.side;
        is >> floor.coEfficients.ambient >> floor.coEfficients.diffuse  >> floor.coEfficients.reflection ;
        floor.coEfficients.shine = 0;
        floor.basePoint = {-50*floor.side, -50*floor.side, 0};
        floor.p[0] = floor.basePoint;
        floor.p[1] = floor.basePoint + Point(floor.side*100, 0, 0);
        floor.p[2] = floor.basePoint + Point(floor.side*100, floor.side*100, 0);
        floor.p[3] = floor.basePoint + Point(0, floor.side*100, 0);

        return is;
    }

};


extern double farDistance;

Color captureColor(Ray ray,int level){

    Color color;
    double tMin = farDistance;
    bool intersected = false;
    int index = -1;
    for(int k=0;k<objects.size();k++){
        Color color2;
        double t = objects[k]->intersect(ray,color2, level);
        
        if(t<tMin and t>0){
            tMin = t;
            intersected = true;
            index = k;
            color = color2;
        }
    }
    // if(intersected and i%10 == 0 and j%10 == 0) cout<<endl;
    
    color.cutoff();
    return color;
}