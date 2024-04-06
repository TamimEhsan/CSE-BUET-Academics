// #include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <iostream>


#define pi (2*acos(0.0))



// Global variables






struct Point
{
	Point() {}
	double x,y,z;

	Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}

	// arithemtic operations
	Point operator +(Point b)  {return Point(x+b.x,y+b.y, z+b.z);}
    Point operator -(Point b)  {return Point(x-b.x,y-b.y, z-b.z);}
	Point operator *(double b)  {return Point(x*b,y*b, z*b);}
	Point operator /(double b)  {return Point(x/b,y/b, z/b);}
	Point operator *(Point b)  {return Point(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);}
};

double dot(Point a, Point b) { return a.x * b.x + a.y * b.y + a.z*b.z; }
double length(Point a) { return sqrt(dot(a, a)); }
Point normalize(Point a){ return a/length(a); }


// Global variables
struct Point pos;   // position of the eye
struct Point l;     // look/forward direction
struct Point r;     // right direction
struct Point u;     // up direction
double angleRotationZ = 45.0;
/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black and opaque
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling

    /*pos.x=4;pos.y=4;pos.z=4;

    l.x=-4;l.y=-4;l.z=-4;
    u.x=0;u.y=1;u.z=0;
    r.x=1;r.y=0;r.z=0;*/
    /*
    pos = {4,4,4};
    u = {0,0,1};
    r = {0,1,0};
    l = {-1,0,0};
    */
    pos = {5,0,2};
    l = {-1,0,0};
    r = {0,1,0};
    u = {0,0,1};
    
    

}


/* Draw axes: X in Red, Y in Green and Z in Blue */
void drawAxes() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(2,0,0);   // Red
        // X axis
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);

        glColor3f(0,2,0);   // Green
        // Y axis
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);

        glColor3f(0,0,2);   // Blue
        // Z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
    glEnd();
}

void drawGrid()
{
	int i;
	
    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-18;i<=18;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*0.1, -1.9, 0);
            glVertex3f(i*0.1,  1.9, 0);

            //lines parallel to X-axis
            glVertex3f(-1.9, i*0.1, 0);
            glVertex3f( 1.9, i*0.1, 0);
        }
    }glEnd();
	
}

void drawTriangle()
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);{
		glVertex3f(1,0,0);
		glVertex3f(0,1,0);
		glVertex3f(0,0,1);
	}glEnd();
}
int numSegments = 36;

void drawCylinder_v2(double height, double radius, int segments,bool half) {
    struct Point points[segments+1];

    double offset = 70.5287794*M_PI/180.0;

    for (int i = 0; i < segments+1; i++) {
        double theta;
        theta = -offset/2 +  i * offset / segments;
        if( half ) theta = /*-offset/2 +*/  i * offset / segments;
        points[i].x = radius * cos(theta);
        points[i].y = radius * sin(theta);
    }

    glBegin(GL_QUADS);
        for (int i = 0; i < segments; i++) {
            glVertex3f(points[i].x, points[i].y, height/2);
            glVertex3f(points[i].x, points[i].y, -height/2);
            glVertex3f(points[i+1].x, points[i+1].y, -height/2);
            glVertex3f(points[i+1].x, points[i+1].y, height/2);
        }
    glEnd();
}

void drawSphereQuad(double radius,int segments,bool halfx,bool halfy)
{
   
	struct Point points[segments+1][segments+1];
	int i,j;
	double x,y;
	//generate points
	for(i=0;i<=segments;i++){
		
		for(j=0;j<=segments;j++){
            x = -1 + (double)i/segments*2;
            if( halfx ) x = -1 + (double)i/segments;
		    y = -1 + (double)j/segments*2;
            if( halfy ) y = -1 + (double)j/segments;
			points[i][j].x=x;
			points[i][j].y=y;
			points[i][j].z=1;

            points[i][j] = normalize(points[i][j]);
            points[i][j] = points[i][j]*radius;

		}
	}
	//draw quads using generated points
	for(i=0;i<segments;i++)
	{
		for(j=0;j<segments;j++)
		{
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			}glEnd();
		}
	}
}




double maxTriangleLength = 1.6;
double triangleLength = 1.6;

double maxSphereRadius = maxTriangleLength / sqrt(3.0);
double sphereRadius = 0;
double sphereStep = maxSphereRadius/16.0;




void drawCylinders(){

    glColor3f(1.0f, 1.0f, 0.0f);

    for(int i=0;i<4;i++){

        glPushMatrix();{
            if(  i == 0 or i == 1  ) continue;
            glRotatef(45+i*90,0,1,0);
            glTranslatef(triangleLength/sqrt(2),0,0);
            drawCylinder_v2(triangleLength*sqrt(2),sphereRadius,100,false);
        }glPopMatrix();
        
    }


    //////////////
    // ekhane half kora lagbe
    for(int i=0;i<4;i++){
        // if(  i == 0 or i == 1  ) continue;
        glPushMatrix();{
            glRotatef(90,1,0,0);
            glRotatef(45+i*90,0,1,0);
            glTranslatef(triangleLength/sqrt(2),0,0);
            drawCylinder_v2(triangleLength*sqrt(2),sphereRadius,100,true);
        }glPopMatrix();
        
    }


    ///////////////
    for(int i=0;i<4;i++){
        if(  i == 0 or i == 1  ) continue;
        glPushMatrix();{
            glRotatef(90,0,0,1);
            glRotatef(45+i*90,0,1,0);
            glTranslatef(triangleLength/sqrt(2),0,0);
            drawCylinder_v2(triangleLength*sqrt(2),sphereRadius,100,false);
        }glPopMatrix();

    }

}



void drawSpheres(){

    // for(int i=0;i<4;i++){
        
    //     glPushMatrix();{
    //         glColor3f(0, i%2, (i+1)%2);     // blue / green
    //         glRotatef(90*i,0,1,0);
    //         glTranslatef(0,0,triangleLength);
    //         drawSphereQuad(sphereRadius,100);

    //     }glPopMatrix();

    // }

    glPushMatrix();{
            glColor3f(1, 0, 0);     // top red
            glRotatef(90*0,0,1,0);
            glTranslatef(0,0,triangleLength);
            drawSphereQuad(sphereRadius,100,false,false);

    }glPopMatrix();
    for(int i=0;i<4;i++){
        glPushMatrix();{
            glColor3f(0, i%2, (i+1)%2);     // blue / green
            glRotatef(90*i,0,0,1);
            glRotatef(90,0,1,0);
            glTranslatef(0,0,triangleLength);
            drawSphereQuad(sphereRadius,100,true,false);

    }glPopMatrix();
    }
    // glPushMatrix();{
    //         glColor3f(0, 1, 0);     // blue / green
    //         glRotatef(90*1,0,1,0);
    //         glTranslatef(0,0,triangleLength);
    //         drawSphereQuad(sphereRadius,100,true,false);

    // }glPopMatrix();

    // glPushMatrix();{
    //         glColor3f(0, 0, 1);     // blue / green
    //         glRotatef(90*1,0,0,1);
    //         glRotatef(90*1,0,1,0);
            

    //         glTranslatef(0,0,triangleLength);
    //         drawSphereQuad(sphereRadius,100,true,false);

    // }glPopMatrix();

    // glPushMatrix();{
    //         glColor3f(0, 1, 0);     // blue / green
    //         glRotatef(90*2,0,0,1);
    //         glRotatef(90*1,0,1,0);
            

    //         glTranslatef(0,0,triangleLength);
    //         drawSphereQuad(sphereRadius,100,true,false);

    // }glPopMatrix();

    // glPushMatrix();{
    //         glColor3f(0, 0, 1);     // blue / green
    //         glRotatef(90*3,0,0,1);
    //         glRotatef(90*1,0,1,0);
            

    //         glTranslatef(0,0,triangleLength);
    //         drawSphereQuad(sphereRadius,100,true,false);

    // }glPopMatrix();
    

    // for(int i=0;i<2;i++){
        
    //     glPushMatrix();{
    //         glColor3f(1.0f, 0.0f, 0.0f);     // red
    //         glRotatef(90+180*i,1,0,0);
    //         glTranslatef(0,0,triangleLength);
    //         drawSphereQuad(sphereRadius,100);
    //     }glPopMatrix();

    // }

}


void drawPyramids(){
    double diff = maxTriangleLength - triangleLength;
    diff = diff/3.0;
    for(int i=0;i<4;i++){
        if(  i == 1 or i == 2  ) continue;
        glPushMatrix();{
            glColor3f((i+1)%2, i%2, 1.0f);  // purple / cyan
            glRotatef(90*i,0,1,0);
            glTranslatef(diff,diff,diff);
            glScaled(triangleLength,triangleLength,triangleLength);
            drawTriangle();
        }glPopMatrix();

    }
    
    for(int i=0;i<4;i++){
        if(  i == 1 or i == 2 ) continue;

        glPushMatrix();{
            glColor3f(i%2, (i+1)%2, 1.0f);  // cyan / pruple
            glRotatef(90*i,0,1,0);
            glRotatef(180,1,0,1);
            glTranslatef(diff,diff,diff);
            glScaled(triangleLength,triangleLength,triangleLength);
            drawTriangle();
        }glPopMatrix();

    }

}

void drawAll() {
    drawPyramids(); // done
    drawSpheres();
    drawCylinders();
}

/*  Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
void display() {
    float cx = 1, cy = 1;
  //  glTranslatef(-cx, -cy, 0);
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);             // To operate on Model-View matrix
    glLoadIdentity();                       // Reset the model-view matrix
   
    // default arguments of gluLookAt
    // gluLookAt(0,0,0, 0,0,-100, 0,1,0);

    // control viewing (or camera)
    gluLookAt(pos.x,pos.y,pos.z,
              pos.x+l.x,pos.y+l.y,pos.z+l.z,
              u.x,u.y,u.z);
    // draw
    glRotatef(angleRotationZ, 0,0 , 1);
    
    // drawAxes();
    // drawGrid();
    drawAll();

    glutSwapBuffers();  // Render now
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
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
   // gluPerspective(45.0f, aspect, 0.1f, 100.0f);
   gluPerspective(80,	1,	1,	1000.0);
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
        printf("pos: %f %f %f\n",pos.x,pos.y,pos.z);
        printf("l: %f %f %f\n",l.x,l.y,l.z);
        printf("r: %f %f %f\n",r.x,r.y,r.z);
        printf("u: %f %f %f\n",u.x,u.y,u.z);
        printf("angle: %f\n",angleRotationZ);

        break;
    case 'd':
        angleRotationZ -= 5.0f;
        break;
    case 'a':
        angleRotationZ += 5.0f;
        break;
    case 'w':
        pos.z += v;
        break;
    case 's':
        pos.z -= v;
        break;
    // Control eye (location of the eye)
    // control eye.x
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
        triangleLength-=0.1;
        sphereRadius+=sphereStep;
        if( triangleLength<0 ) {
            triangleLength = 0;
            sphereRadius = maxSphereRadius;
        }
        break;
    case '.':
        triangleLength+=0.1;
        sphereRadius-=sphereStep;
        if( triangleLength>maxTriangleLength ) {
            triangleLength = maxTriangleLength;
            sphereRadius = 0;
        }
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
			pos=pos+l;
			break;
		case GLUT_KEY_DOWN:		// up arrow key
			pos=pos-l;
			break;

		case GLUT_KEY_RIGHT:
			pos=pos+r;
			break;
		case GLUT_KEY_LEFT :
			pos=pos-r;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos=pos+u;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos=pos-u;
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
    glutInitWindowPosition(50, 50);             // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("Magic Cube by Tamim U w U");      // Create a window with the given title
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);           // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);         // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);        // Register callback handler for special-key event
    initGL();                                   // Our own OpenGL initialization
    glutMainLoop();                             // Enter the event-processing loop
    return 0;
}
