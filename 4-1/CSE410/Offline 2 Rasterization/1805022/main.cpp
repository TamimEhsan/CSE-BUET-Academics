#include<bits/stdc++.h>
using namespace std;
#include "headers.h"
#include "bitmap_image.hpp"

int main(){


    /*
        stage 1
    */
    ifstream fin("scene.txt");
    ofstream fout("stage1.txt");
    
    Point eye, look, up;
    double fovY, aspectRatio, near, far;
    fin>>eye>>look>>up;
    fin>>fovY>>aspectRatio>>near>>far;

    stack<Matrix> s;
    Matrix I;
    I.identity();
    s.push(I);

    string command;
    while(fin>>command){
        if( command == "triangle" ){
            Triangle t;
            fin>>t;
            t = s.top()*t;
            fout<<t;
            fout<<endl;
        } else if( command == "translate" ){
            Point p;
            fin>>p;
            Matrix m;
            m.translate(p);
            s.top() = s.top()*m;
        } else if( command == "scale" ){
            Point p;
            fin>>p;
            Matrix m;
            m.scale(p);
            s.top() = s.top()*m;
        } else if( command == "rotate" ){
            Point p;
            double theta;
            fin>>theta>>p;
            theta = theta*PI/180.0;
            Matrix m;
            m.rotate(p, theta);
            s.top() = s.top()*m;
        } else if( command == "push" ){
            s.push(s.top());
        } else if( command == "pop" ){
            s.pop();
        } else if( command == "end" ){
            break;
        }
    }
   
    /*
        stage 2
    */
    fin.close();
    fout.close();
    fin.open("stage1.txt");
    fout.open("stage2.txt");

    Point l,r,u;
    l = look - eye;
    l.normalize();
    r = l^up;
    r.normalize();
    u = r^l;
    u.normalize();
    Matrix T;
    Point eyei;
    eyei = eye*-1;
    T.translate(eyei);
    Matrix R;
    R.identity();
    R.matrix[0][0] = r.x; R.matrix[0][1] = r.y; R.matrix[0][2] = r.z;
    R.matrix[1][0] = u.x; R.matrix[1][1] = u.y; R.matrix[1][2] = u.z;
    R.matrix[2][0] = -l.x; R.matrix[2][1] = -l.y; R.matrix[2][2] = -l.z;

    Matrix V = R*T;

    Triangle triangle;
    while(fin>>triangle){
        triangle = V*triangle;
        fout<<triangle<<endl;
    }

    fin.close();
    fout.close();
    /*
        stage 3
    */
    fin.open("stage2.txt");
    fout.open("stage3.txt");

    double fovX = fovY*aspectRatio;
    double t = near*tan(fovY*PI/360.0);
    double r2 = near*tan(fovX*PI/360.0);

    Matrix P;
    P.matrix[0][0] = near/r2;
    P.matrix[1][1] = near/t;
    P.matrix[2][2] = -(far+near)/(far-near);
    P.matrix[2][3] = -(2.0*far*near)/(far-near);
    P.matrix[3][2] = -1.0; 

   
    while(fin>>triangle){
        triangle = P*triangle;
        fout<<triangle<<endl;
    }

    fin.close();
    fout.close();

    /*
        stage 4: Clipping and Scan Conversion using Z-Buffer
    */

    fin.open("stage3.txt");
    fout.open("z_buffer.txt");
    ifstream fin2("config.txt");
    int screen_width, screen_height;
    fin2>>screen_width>>screen_height;
    double box_left=-1, box_right=1, box_bottom=-1, box_top=1;
    double Z_min=-1, Z_max=1;
    double dx = (box_right-box_left)/screen_width;
    double dy = (box_top-box_bottom)/screen_height;
    double Top_Y = box_top - dy/2.0;
    double Left_X = box_left + dx/2.0;


    // initialize z-buffer and frame buffer

    vector< vector<double> > z_buffer(screen_height, vector<double>(screen_width, Z_max));
    for(int i=0; i<screen_height; i++){
        for(int j=0; j<screen_width; j++){
            z_buffer[i][j] = Z_max;
        }
    }

    bitmap_image image(screen_width, screen_height);
    image.set_all_channels(0, 0, 0);


    while(fin>>triangle){

        triangle.sort();
        triangle.recolor();
        // clipping
        double min_y = triangle.a.y;
        double max_y = triangle.b.y;

        //cout<<"y range "<<min_y<<" "<<max_y<<endl;
       
        min_y = max(min_y, box_bottom);
        max_y = min(max_y, box_top);

        // scan conversion

        //cout<<"y range "<<min_y<<" "<<max_y<<endl;
        for(double y=min_y; y<=max_y; y+=dy){
           
            // compute min_x and max_x for this row
            double min_x = 0;
            double max_x = -1;
            double min_z = 0;
            double max_z = -1;


            if( triangle.b.y != triangle.a.y and triangle.a.y != triangle.c.y ){
                min_x = triangle.a.x + (triangle.b.x-triangle.a.x)*(y-triangle.a.y)/(triangle.b.y-triangle.a.y);
                max_x = triangle.a.x + (triangle.c.x-triangle.a.x)*(y-triangle.a.y)/(triangle.c.y-triangle.a.y);

                min_z = triangle.a.z + (triangle.b.z-triangle.a.z)*(y-triangle.a.y)/(triangle.b.y-triangle.a.y);
                max_z = triangle.a.z + (triangle.c.z-triangle.a.z)*(y-triangle.a.y)/(triangle.c.y-triangle.a.y);

                if( min_x > max_x ) {
                    swap(min_x, max_x);
                    swap(min_z, max_z);
                }
            }

            min_x = max(min_x, box_left);
            max_x = min(max_x, box_right);
            //cout<<min_x<<" "<<max_x<<endl;

            for(double x=min_x; x<=max_x; x+=dx){
                if( max_x == min_x ) continue;

                int i = (Top_Y-y)/dy;
                int j = (x-Left_X)/dx;
                
                double z = min_z + (max_z-min_z)*(x-min_x)/(max_x-min_x);
                if( z < z_buffer[i][j] and z>Z_min ){
                    z_buffer[i][j] = z;
                    image.set_pixel(j, i, triangle.color.r, triangle.color.g , triangle.color.b);
                }
                
            }
        }


        min_y = triangle.b.y;
        max_y = triangle.c.y;

        //cout<<"y range "<<min_y<<" "<<max_y<<endl;
       
        min_y = max(min_y, box_bottom);
        max_y = min(max_y, box_top);

       // cout<<"y range "<<min_y<<" "<<max_y<<endl;

        // scan conversion
        for(double y=min_y; y<=max_y; y+=dy){
           
            // compute min_x and max_x for this row
            double min_x = 0;
            double max_x = -1;
            double min_z = 0;
            double max_z = -1;


            if( triangle.b.y != triangle.c.y and triangle.a.y != triangle.c.y ){
                min_x = triangle.c.x + (triangle.b.x-triangle.c.x)*(y-triangle.c.y)/(triangle.b.y-triangle.c.y);
                max_x = triangle.a.x + (triangle.c.x-triangle.a.x)*(y-triangle.a.y)/(triangle.c.y-triangle.a.y);

                min_z = triangle.c.z + (triangle.b.z-triangle.c.z)*(y-triangle.c.y)/(triangle.b.y-triangle.c.y);
                max_z = triangle.a.z + (triangle.c.z-triangle.a.z)*(y-triangle.a.y)/(triangle.c.y-triangle.a.y);

                if( min_x > max_x ) {
                    swap(min_x, max_x);
                    swap(min_z, max_z);
                }
            }
            min_x = max(min_x, box_left);
            max_x = min(max_x, box_right);
            // cout<<"x range "<<min_x<<" "<<max_x<<endl;

            for(double x=min_x; x<=max_x; x+=dx){
                if( max_x == min_x ) continue;
                
                int i = (Top_Y-y)/dy;
                int j = (x-Left_X)/dx;
                
                double z = min_z + (max_z-min_z)*(x-min_x)/(max_x-min_x);
                if( z < z_buffer[i][j] and z>Z_min ){
                    z_buffer[i][j] = z;
                    image.set_pixel(j, i, triangle.color.r, triangle.color.g , triangle.color.b);
                }
                
            }
        }

    }

    image.save_image("out.bmp");

    for(int i=0; i<screen_height; i++){
        for(int j=0; j<screen_width; j++){
            if (z_buffer[i][j] < Z_max) {
                fout << setprecision(6) << fixed << z_buffer[i][j] << "\t";
            }
        }
        fout<<endl;
    }


    fin.close();
    fin2.close();
    fout.close();
    
    z_buffer.clear();
    z_buffer.shrink_to_fit();
    
    return 0;


}
