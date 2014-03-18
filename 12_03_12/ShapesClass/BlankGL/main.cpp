

#include <iostream>
#include <glut.h>
#include "square.h"


using namespace std;


/* GLfloat arrays to specify colors */ 
static GLfloat white[]   = {1.0, 1.0, 1.0, 1.0};
static GLfloat off_white[]= {0.8, 0.8, 0.8, 1.0};
static GLfloat gray[]    = {0.5, 0.5, 0.5, 1.0};
static GLfloat orange[]  = {1.0, 0.5, 0.0, 0.5};
static GLfloat red[]     = {1.0, 0.0, 0.0, 1.0};
static GLfloat green[]   = {0.0, 1.0, 0.0, 1.0};
static GLfloat blue[]    = {0.0, 0.0, 1.0, 1.0};
static GLfloat yellow[]  = {1.0, 1.0, 0.0, 1.0}; 
static GLfloat magenta[] = {1.0, 0.0, 1.0, 1.0}; 
static GLfloat cyan[]    = {0.0, 1.0, 1.0, 1.0}; 
static GLfloat cyan_dull[]= {0.0, 0.4, 0.4, 1.0};

static GLfloat changeColor[]    = {0.0, 1.0, 1.0, 1.0}; 


void writeMessage();
void init();
void reshape(int, int);
void display();
void keyboard(unsigned char, int, int);

//position of light
static GLfloat light_one[] = {0.5,    0.0, 30.0, 5.0};
// position of viewer 
static GLdouble viewer[] = {0.0, -2.0, 20.0}; 

square s(4, cyan);


int moveCounter = 0;

void display()
{
   /*start boiler*/
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); 
   //set camera direction and position
   gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   //draw light source
   glLightfv(GL_LIGHT0, GL_POSITION, light_one);
   /*end boiler*/


   //dummy triangle
   //glBegin(GL_QUADS);
   //    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	  // glVertex3f(-2,2,0);
	  // glVertex3f(2,2,0);
   //    glVertex3f(2,-2,0);
	  // glVertex3f(-2,-2,0);
   //glEnd();
    

	/*moveCounter++;
	if (moveCounter < 100)
	{
		s.move(0.1, 0.1);
	}*/

   GLfloat increment = 0.005;

   if (moveCounter > 1000)
   {

	   moveCounter = 0;
   }
   
   if (moveCounter > 660)
   {
	   changeColor[1] += increment;
	   changeColor[2] = 0;
	   changeColor[0] = 0;
   }
   else if (moveCounter > 330)
   {
	   changeColor[1] = 0;
	   changeColor[2] += increment;
	   changeColor[0] = 0;
   }
   else if (moveCounter > 0)
   {
	   changeColor[1] = 0;
	   changeColor[2] = 0;
	   changeColor[0] += increment;
   }
   moveCounter++;

   s.setColor(changeColor);
   
    s.draw();
	glutPostRedisplay();

   /*start boiler*/
   glFlush();
   glutSwapBuffers();
   /*end boiler*/
}


void keyboard(unsigned char key, int x, int y)
{
   //user interaction here
	switch(key)
	{
	case 'o':
		s.hide();
		break;
	
	case 'p':
		s.show();
		break;

	case 'w':
		s.move(0.1, 0.1);
		break;
	case 'a':
		break;
	case 's':
		s.move(0, -0.1);
		break;
	case 'd':
		break;
	case 'r':
		changeColor[0] = 1;
		changeColor[1] = 0;
		changeColor[2] = 0;
		break;
	case 'g':
		changeColor[0] = 0;
		changeColor[1] = 1;
		changeColor[2] = 0;
		break;
	}

	//s.setColor(changeColor);

	
	glutPostRedisplay();
}


//output in initial console
void writeMessage()
{
   //any control instructions go here
   cout << "BlankGL Template Project" << endl;
}

//allows for resizing
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 2.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
}


void init() 
{
   writeMessage(); 
   //"Background" color = white
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      /* GL_FILL, GL_LINE to show wireframe */
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1280, 700); 
   glutInitWindowPosition(50, 50);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}