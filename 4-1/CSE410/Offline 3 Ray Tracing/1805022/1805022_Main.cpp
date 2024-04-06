#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <iostream>
#include "string"
#include<bits/stdc++.h>
using namespace std;
#include "1805022_Header.h"
#include "1805022_bitmap_image.hpp"

#define pi (2*acos(0.0))


// Global variables
vector <Object*> objects;
vector <NormalLight*> lights;
vector <SpotLight*> spotlights;
bitmap_image image;
double windowWidth, windowHeight;
bool enableTexture = false;

// Global variables for camera
struct Point eye;   // position of the eye
struct Point l;     // look/forward direction
struct Point r;     // right direction
struct Point u;     // up direction
double angleRotationZ = 0.0;


// Global variables for drawing
double nearDistance, farDistance;
int fieldOfVisionX;
int fieldOfVisionY;
int aspectRatio;
int recursionLevel;
int pixels;

int cellSize;
double ambientCoefficient,diffuseCoefficient,reflectionCoefficient;
int numberOfObjects;
int numberOfNormalLightSources;
int numberOfSpotLightSources;

// Debugs
Ray rays[1000][1000];
double ROT_ANG = pi/180;


void rotate3D(Point &vec,Point &axis,double ang){
	// vec = vec*cos(ang)+(vec*axis)*sin(ang);
	vec = vec*cos(ang)+(axis^vec)*sin(ang);
}

/* Draw axes: X in Red, Y in Green and Z in Blue */
void drawAxes() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(2,0,0);   // Red
        // X axis
        glVertex3f(0,0,1);
        glVertex3f(100,0,1);

        glColor3f(0,2,0);   // Green
        // Y axis
        glVertex3f(0,0,1);
        glVertex3f(0,100,1);

        glColor3f(0,0,2);   // Blue
        // Z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();
}
/*
void drawGrid()
{
	int i;
	
    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-50;i<=50;i++){

            //if(i==0)    continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*cellSize, -cellSize*50, 0);
            glVertex3f(i*cellSize,  cellSize*50, 0);

            //lines parallel to X-axis
            glVertex3f(-cellSize*50, i*cellSize, 0);
            glVertex3f( cellSize*50, i*cellSize, 0);

            glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			}glEnd();
        }
    }glEnd();
	
}
*/
// draw checkerboard
void drawGrid() {
    return;
    /*int i,j;
    Object *obj;
    Point basePoint = {-50.0*cellSize,-50.0*cellSize,0};
   
    obj = new Floor(basePoint,cellSize);
    
    objects.push_back(obj);*/
    /*for(i=-50;i<50;i++){
        for(j=-50;j<50;j++){
            if((i+j)%2==0){
                glColor3f(1,1,1);
            }else{
                glColor3f(0,0,0);
            }
            glBegin(GL_QUADS);{
                glVertex3f(i*cellSize,j*cellSize,0);
                glVertex3f(i*cellSize,(j+1)*cellSize,0);
                glVertex3f((i+1)*cellSize,(j+1)*cellSize,0);
                glVertex3f((i+1)*cellSize,j*cellSize,0);
            }glEnd();
        }
    }*/
}

Point a,b,c;
Ray ray;
void drawAll() {
   for(auto obj:objects) obj->draw();
   for(auto obj:lights) obj->draw();
   for(auto obj:spotlights) obj->draw();

}


void debugz(){

   
    return;
     // double planeDistance = (double) (windowHeight/2.0) / tan((fieldOfVisionY/2.0) * (pi/180.0));   
    Point topLeft = eye + l*nearDistance - r*(pixels/2.0) + u*(pixels/2.0);

    double dx = (double) (windowWidth/pixels*1.0);
    double dy = (double) (windowHeight/pixels*1.0);

    topLeft = topLeft + r*dx/2.0 - u*dy/2.0;

    Point middle = eye + l*nearDistance;

   
    //cout<<ret<<endl;
   // cout<<"top left "<<topLeft<<endl;

    for(int i=50;i<100;i++){
        for(int j=500;j<550;j++){
            double x = i-(pixels/2.0);
            double y = j-(pixels/2.0);
            Point currentPixel = middle + r*x*dx - u*y*dy;
            //cout<<"current Pixel " <<currentPixel<<endl;
            Point dir = (currentPixel-eye);
            dir.normalize();
            Ray ray(eye, dir);
            
            Point p = eye + dir*100;
            if( i%10 == 0 and j%10 == 0 ){
                glPushMatrix();{
                    glTranslatef(p.x, p.y, p.z);
                    glColor3f(1, 0, 0);
                    glutSolidSphere(1, 20, 20);
                }glPopMatrix();
            }

            



        }
    }

   
}

/*  Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
void display() {
    float cx = 1, cy = 1;
  //  glTranslatef(-cx, -cy, 0);
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);             // To operate on Model-View matrix
    glLoadIdentity();                       // Reset the model-view matrix
   
    // default arguments of gluLookAt
    // gluLookAt(0,0,0, 0,0,-100, 0,1,0);

    // control viewing (or camera)
    gluLookAt(eye.x,eye.y,eye.z,
              eye.x+l.x,eye.y+l.y,eye.z+l.z,
              u.x,u.y,u.z);
    glMatrixMode(GL_MODELVIEW);

    //glRotatef(angleRotationZ, 0,0 , 1);
    // draw


    drawAxes();
    drawGrid();
    drawAll();
    debugz();
   // cout<<"l: "<<l<<endl;
    glutSwapBuffers();  // Render now
}


void loadData(){
    ifstream fin("scene.txt");
    fin>>nearDistance>>farDistance;
    fin>>fieldOfVisionY>>aspectRatio;

    fin>>recursionLevel;
    fin>>pixels;

    Object *obj;
    obj = new Floor();


    fin >> *((Floor *)obj);
    objects.push_back(obj);

    fin>>numberOfObjects;


    for(int i=0;i<numberOfObjects;i++){
        string type;
        fin>>type;
        Object *obj;
        if( type == "sphere" ) {
            obj = new Sphere();
			fin >> *((Sphere *)obj);
          //  cout<<*((Sphere *)obj)<<endl;
        }else if( type == "pyramid" ) {
            obj = new Pyramid();
			fin >> *((Pyramid *)obj);
          //  cout<<*((Pyramid *)obj)<<endl;
        }else if( type == "cube" ){
            obj = new Cube();
			fin >> *((Cube *)obj);
          //  cout<<*((Cube *)obj)<<endl;
            
        }else{
            cout<<"Invalid object type"<<endl;
        }
        objects.push_back(obj);
        
    }
    fin>>numberOfNormalLightSources;
    for(int i=0;i<numberOfNormalLightSources;i++){
        NormalLight nls;
        fin>>nls;
        lights.push_back(new NormalLight(nls));
    }
    fin>>numberOfSpotLightSources;
    for(int i=0;i<numberOfSpotLightSources;i++){
        SpotLight sls;
        fin>>sls;
        spotlights.push_back(new SpotLight(sls));
    }
}


void capture() {

    // double planeDistance = (double) (windowHeight/2.0) / tan((fieldOfVisionY/2.0) * (pi/180.0));   
    //Point topLeft = eye + l*nearDistance - r*(pixels/2.0) + u*(pixels/2.0);

    double dx = (double) (windowWidth/pixels*1.0);
    double dy = (double) (windowHeight/pixels*1.0);

    // topLeft = topLeft + r*dx/2.0 - u*dy/2.0;

    Point middle = eye + l*nearDistance;
    // cout<<"middle "<<middle<<endl;
    // cout<<"dx "<<dx<<" dy "<<dy<<endl;
    int total = pixels*pixels;
    int percentages[10] = {10,20,30,40,50,60,70,80,90,100};
    for(int i=0;i<10;i++){
        percentages[i] = (total*i*10)/100;
    }
    int cnt = 0;
    //cout<<ret<<endl;
   // cout<<"top left "<<topLeft<<endl;
    // for(int i=50;i<100;i++){
    //     for(int j=500;j<550;j++){
     for(int i=0;i<pixels;i++){
        for(int j=0;j<pixels;j++){
            cnt++;
            for(int k=0;k<10;k++){
                if( cnt == percentages[k] ){
                    cout<<k*10<<"% done"<<endl;
                }
            }


            double x = i-(pixels/2.0);
            double y = j-(pixels/2.0);
            Point currentPixel = middle + r*x*dx - u*y*dy;
            //cout<<"current Pixel " <<currentPixel<<endl;
            Point dir = (currentPixel-eye);
            dir.normalize();
            Ray ray(eye, dir);
            
            Point p = eye + dir*100;
            //cout<<"p "<<p<<endl;

            Color color = captureColor(ray, recursionLevel);
            image.set_pixel(i, j, color.r*255.0, color.g*255.0, color.b*255.0);
            
        }
    }

    image.save_image("out.bmp");
    cout<<"Image saved to out.bmp"<<endl;
    
}

/* Initialize OpenGL Graphics */
void initGL() {

    eye = {0,-160,60};
    l = {0,1,0};
    r = {1,0,0};
    u = {0,0,1};

    loadData();
    image = bitmap_image(pixels, pixels);

    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black and opaque
    //glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fieldOfVisionY,aspectRatio,nearDistance,farDistance);

    fieldOfVisionX = aspectRatio*fieldOfVisionY;
    windowHeight = 2*nearDistance*tan((fieldOfVisionY/2.0) * (pi/180.0));
    windowWidth = 2*nearDistance*tan((fieldOfVisionX/2.0) * (pi/180.0));  


}


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeListener(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
   
   // gluPerspective(80,	1,	1,	1000.0);
   gluPerspective(fieldOfVisionY,aspectRatio,nearDistance,farDistance);

}

/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y) {
    double v = 0.1;
    double rate = 0.1;
    //Point oldEye = eye;
   

    double s;
    //float v = 0.1;
    switch (key) {
    case ' ' :
        // printf("pos: %f %f %f\n",eye.x,eye.y,eye.z);
        // printf("l: %f %f %f\n",l.x,l.y,l.z);
        // printf("r: %f %f %f\n",r.x,r.y,r.z);
        // printf("u: %f %f %f\n",u.x,u.y,u.z);
        // printf("angle: %f\n",angleRotationZ);

        break;
    case 'd':
        rotate3D(r,u,ROT_ANG);
		rotate3D(l,u,ROT_ANG);
        break;
    case 'a':
        rotate3D(r,u,-ROT_ANG);
		rotate3D(l,u,-ROT_ANG);
        //angleRotationZ += 5.0f;
        break;
    case 'w':
        eye.z += v;
        break;
    case 's':
        eye.z -= v;
        break;
    // Control eye (location of the eye)
    // control eye.x
    case '0':
        capture();
        break;
    case '1':
            r = r*cos(rate) + l*sin(rate);
            l = l*cos(rate)-r*sin(rate);
			break;

    case '2':
        r = r*cos(-rate) + l*sin(-rate);
        l = l*cos(-rate)-r*sin(-rate);
        break;

    case '3':
        l = l*cos(rate)+u*sin(rate);
        u = u*cos(rate)-l*sin(rate);
        break;

    case '4':
        l = l*cos(-rate)+u*sin(-rate);
        u = u*cos(-rate)-l*sin(-rate);
        break;

    case '5':
        u = u*cos(rate)+r*sin(rate);
        r = r*cos(rate)-u*sin(rate);
        break;

    case '6':
        u = u*cos(-rate)+r*sin(-rate);
        r = r*cos(-rate)-u*sin(-rate);
        
        break;

    // Control center (location where the eye is looking at)
    // control centerx
   /* case 'z':
        centerx += v;
        break;
    case 'x':
        centerx -= v;
        break;
    // control centery
    case 'e':
        centery += v;
        break;
    case 'r':
        centery -= v;
        break;
    // control centerz
    case 't':
        centerz += v;
        break;
    case 'y':
        centerz -= v;
        break;
*/
    // Control what is shown
  
   
    case ',':
        
        break;
    case '.':
       
        break;
    // Control exit
    case 27:    // ESC key
        exit(0);    // Exit window
        break;
    }

    //look = look - eye + oldEye;
   


    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Callback handler for special-key event */
void specialKeyListener(int key, int x,int y)
{
	switch(key){
		case GLUT_KEY_UP:		//down arrow key
			eye=eye+l*3;
			break;
		case GLUT_KEY_DOWN:		// up arrow key
			eye=eye-l*3;
			break;

		case GLUT_KEY_RIGHT:
			eye=eye+r*3;
			break;
		case GLUT_KEY_LEFT :
			eye=eye-r*3;
			break;

		case GLUT_KEY_PAGE_UP:
		    eye=eye+u*3;
			break;
		case GLUT_KEY_PAGE_DOWN:
            eye=eye-u*3;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
	glutPostRedisplay();
}




/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {


    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitWindowSize(840, 840);               // Set the window's initial width & height
    glutInitWindowPosition(0, 0);             // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("Magic Cube by Tamim U w U");      // Create a window with the given title
    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);           // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);         // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);        // Register callback handler for special-key event
    initGL();                                   // Our own OpenGL initialization
    glutMainLoop();                             // Enter the event-processing loop
    return 0;
}
