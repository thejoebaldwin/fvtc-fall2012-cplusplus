

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
const int squareLength = 100;
square allSquares[squareLength];

void writeMessage();
void init();
void reshape(int, int);
void display();
void keyboard(unsigned char, int, int);

//position of light
static GLfloat light_one[] = {0.5,    0.0, 30.0, 5.0};
// position of viewer 
static GLdouble viewer[] = {0.0, -2.0, 20.0}; 

//variables for tracking mouse movement
bool leftMouseDown = false;
bool isMovingLeft = false;
int last_x_pos = 0.0;
int current_x_pos = 0.0;

//instantiate a new square
square s(4, cyan);
//counter
int moveCounter = 0;

//do all rendering here, "should" only call .draw on objects
void draw()
{
	if (leftMouseDown == true)
	{
		s.setColor(red);
	}
	else
	{
		s.setColor(green);
	}



	//move object according to mouse flags (should be in mouse movement function)
	/*if (isMovingLeft && leftMouseDown)
	{
		s.move(-0.01f, 0);
	}
	else if (leftMouseDown)
	{
		s.move(0.01f, 0);
	}*/


	//loop through squares array and draw
	for (int i = 0; i < squareLength; i++)
	{
		allSquares[i].draw();

	}

	//draw the square s
	//s.draw();

	//force update (only if we changed something, should have this in mouse or keyboard functions
	glutPostRedisplay();
}

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
   
   for (int i = 0; i < squareLength; i++)
   {
	   allSquares[i].move();

   }


    draw();

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




void initialize()
{
	//create all of our shapes
	GLfloat tempColor[4] = {0, 0, 0, 1};
	for (int i = 0; i < squareLength; i++)
	{
		//set random location
		allSquares[i].move(rand() % 10, rand() % 10);
		//set color
		allSquares[i].setColor(tempColor);
		//new random color
		tempColor[0] = (rand() % 10) /(float) 10;
		tempColor[1] = (rand() % 10) / (float) 10;
		tempColor[2] =  (rand() % 10) /(float) 10;
		//set negative or positive value
		int multiplier = 1;
		if (rand() % 2 == 0) multiplier = -1;
        //set new random velocity
		allSquares[i]._velocity_x = ((rand() % 100) /(float) 10000) * multiplier;
		if (rand() % 2 == 0) multiplier = -1;
		allSquares[i]._velocity_y = ((rand() % 100) / (float) 10000) * multiplier;
		//debug random
		//cout <<"random:" <<  (rand() % 100) / (float) 1000<< endl;
		//set boundaries of square for collisions
		allSquares[i].setLimits(10, -10, -15, 15);
		//set different z values so we dont get overlap
        allSquares[i].z = i / (float) 100;
	}

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
   initialize();
}



//fires on mouse move when button is down. 
void mouseMove(int x, int y)
{
	cout << "x:" << x << "||y:" << y << endl;
	if (leftMouseDown)
	{
		if (last_x_pos > x )
		{
			//isMovingLeft = true;
			s.move(-0.1f, 0);
		}
		else if (last_x_pos < x)
		{
			s.move(0.1f, 0);
		}
		//s.move((last_x_pos - x) / 10.0f, 0);
		last_x_pos = x;
	}
}


//fires on mouse click
void mouseClick(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	{
		//cout << "left button clicked at " << x << "," << y << endl;
		leftMouseDown = false;
    	isMovingLeft = false;
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
	{
		//cout << "right button clicked at " << x << "," << y << endl;
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		leftMouseDown = true;
		cout << "last_x_pos:" << last_x_pos << "||x:" << x << endl;
	}
}


//main, set the environment
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1280, 700); 
   glutInitWindowPosition(50, 50);
   glutCreateWindow(argv[0]);
   init();
   //pass display delegate
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouseClick); 
   glutMotionFunc(mouseMove);
   glutMainLoop();
   return 0;
}