#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <time.h>
#include <GL/glut.h>
using namespace std;

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;

double angle_second;
double angle_minute;
double angle_hour;
int second = 0;
int minute = 0;
int hour = 0;
int old_t = 0;

struct point
{
	double x,y,z;
};


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[segments+1];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}





void drawHands(){
	GLfloat x, y;
	
    // second line
    
	glColor3f(1, 0.0, 0.0);	//grey
	glLineWidth(2);
	glBegin(GL_LINES);
		x = 60.0f * sin(angle_second);
		y = 60.0f * cos(angle_second);
		glVertex2f(0.0f, 0.0f); 
		glVertex2f(x,y); 
		//printf("%f %f",x,y);
	glEnd();
	
	
	
    // minute line
	glColor3f(1.0, 1.0, 1.0);	//grey
	glLineWidth(3);

    glBegin(GL_LINES);
   
        x = 50.0f * sin(angle_minute);
        y = 50.0f * cos(angle_minute);
        glVertex2f(0.0f, 0.0f); 
        glVertex2f(x,y); 
       // printf("%f %f",x,y);
    glEnd();

     // hour line
	glColor3f(1.0, 1.0, 1.0);	//grey
	glLineWidth(4);
    glBegin(GL_LINES);
    
        x = 40.0f * sin(angle_hour);
        y = 40.0f * cos(angle_hour);
        glVertex2f(0.0f, 0.0f); 
        glVertex2f(x,y); 
        //printf("%f %f",x,y);
    glEnd();
	glLineWidth(1);

}

void drawClock(){

	for(int i=0;i<60;i++){
		glBegin(GL_LINES);
		double x1,y1,x2,y2;
        x1 = 80.0f * cos( (pi/30.0) *i);
        y1 = 80.0f * sin((pi/30.0)*i);

		if( i%5 == 0 ){
			x2 = 70.0f * cos((pi/30.0)*i);
        	y2 = 70.0f * sin((pi/30.0)*i);
		}else{
			x2 = 75.0f * cos((pi/30.0)*i);
       		y2 = 75.0f * sin((pi/30.0)*i);
		}

        glVertex2f(x1, y1); 
        glVertex2f(x2,y2); 
        //printf("%f %f",x,y);
    glEnd();
	}

	drawCircle(85,100);

}




void drawPendulum(){

	double timePassed = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	double theta = (pi/4.0)*cos(pi*timePassed+0); // omega = 2* pi / T ; T = 2
	double x1,y1,x2,y2,cx,cy,r;
	

	glBegin(GL_LINES);

		cx = 0;
		cy = -85;

        x1 = 0 + cx;
        y1 = 0 + cy;
		
		x2 = -70.0f * sin(theta) + cx;
        y2 = -70.0f * cos(theta) + cy;
		

        glVertex2f(x1, y1); 
        glVertex2f(x2,y2); 
        //printf("%f %f",x,y);
    glEnd();


	glBegin(GL_POLYGON);    // All vertices form a single polygon
        glColor3f(1.0f,0.5f,0.0f);  // Orange
		cx = x2;
		cy = y2;

        r = 10;
        for (float theta = 0; theta < 360; theta += 10) {
            float x = cx + r * cos(theta/180*M_PI);
            float y = cy + r * sin(theta/180*M_PI);
            glVertex2f(x,y);
        }
    glEnd();

}
void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();
    drawHands();
	drawClock();
	drawPendulum();
    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	int t = glutGet(GLUT_ELAPSED_TIME);
	float dt = (t-old_t) / 1000.0;
	if( dt>=1.00 ){
		//angle+=1.0f/60*60; // for debug
		angle_second=(2*pi/60)*second; 
		angle_minute=(2*pi/60)*minute; 
		angle_hour= (0.5* pi / 180.0) * (60*hour+minute); //0.523599*hour;

		 
		old_t = t;
		// printf("%f\n",dt);
		second++;
		if( second >= 60 ){
			second = 0;
			minute++;
		}
		if( minute >= 60 ){
			minute = 0;
			hour++;
		}
	}
	
	

	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){

	// time
	time_t now;
	time(&now);
	struct tm *local = localtime(&now);
	hour = local->tm_hour%12;
	minute = local->tm_min%60;
	second = local->tm_sec%60;

	printf("%d",hour);

	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle_second=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
