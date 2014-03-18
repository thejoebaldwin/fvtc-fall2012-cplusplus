

#include <iostream>
#include <glut.h>

#include "rectangle.h"
#include <string>


using namespace std;

#define BUFSIZE 512
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
const int squareLength = 10;
square* allSquares[squareLength];

static int ww = 1280;
static int wh = 700;


GLuint texture_id[6];

GLint square1, square2 = -1;



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
void draw(GLenum mode)
{
	if (leftMouseDown == true)
	{
		s.setColor(red);
	}
	else
	{
		s.setColor(green);
	}


	  glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
   glEnable ( GL_TEXTURE_2D );

	//loop through squares array and draw
	for (int i = 0; i < squareLength; i++)
	{
		if (mode == GL_SELECT) glLoadName(allSquares[i]->getName());
		allSquares[i]->draw();
	}

	 glDisable ( GL_TEXTURE_2D );	

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
	   allSquares[i]->move();
	   allSquares[i]->rotate();
   }


    draw(GL_RENDER);

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






void load_texture ( char *file_name, int width, int height, int depth,
                    GLenum colour_type, GLenum filter_type )
{
   
   //Learned how to load textures from:
   //   http://home.clara.net/paulyg/prog3.htm
	
   GLubyte *bitmap ;
   FILE *file;
   if ((file = fopen(file_name, "rb"))==NULL )
   {
      cout<<"File Not Found : "<<file_name<<endl;
      exit   ( 1 );
   }

   bitmap = (GLubyte *) malloc ( width * height * depth * ( sizeof(GLubyte)) );

   if (bitmap == NULL)
   {
    cout<<"Cannot allocate memory for texture"<<endl;
    fclose ( file);
    exit   ( 1 );
   }
   fread  ( bitmap , width * height * depth, 1 , file );
   fclose ( file);
   //  Set Filtering type
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type );
   //  Set Texture Evironment
   glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   //  Build Mipmaps
   //GL_RGBA 
  gluBuild2DMipmaps ( GL_TEXTURE_2D, colour_type, width, height,
                        colour_type, GL_UNSIGNED_BYTE, bitmap );
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap);
   //  Free up the array
   free ( bitmap );
}


void initialize()
{
	//create all of our shapes
	GLfloat tempColor[4] = {0, 0, 0, 1};


	  glEnable ( GL_TEXTURE_2D );
   glGenTextures (6, texture_id); 
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
    //bug shell texture
   glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
   load_texture ( "tex2.bmp", 256, 256, 3, GL_RGB, GL_LINEAR );
  


	for (int i = 0; i < squareLength; i++)
	{
		

		/*if (i % 2 == 0)
		{*/
			allSquares[i] = new square;
		//}
		/*else
		{
			allSquares[i] = new rectangle;
		}*/

		allSquares[i]->move(rand() % 10, rand() % 10);
		//set color
		allSquares[i]->setColor(tempColor);
		//new random color
		tempColor[0] = (rand() % 10) /(float) 10;
		tempColor[1] = (rand() % 10) / (float) 10;
		tempColor[2] =  (rand() % 10) /(float) 10;
		//set negative or positive value
		
		
	
		allSquares[i]->setLimits(10, -10, -15, 15);
		//set different z values so we dont get overlap
        allSquares[i]->z = i / (float) 100;
		allSquares[i]->setName((GLint) i);
		
		cout << *allSquares[i] << endl;
		

	}

}

void init() 
{
   writeMessage(); 
   //"Background" color = white
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   /* GL_FILL, GL_LINE to show wireframe */
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   
  

   initialize();
}



void gotClicked(int index, int button)
{
	
	
	if (button == GLUT_LEFT_BUTTON)
	{
		GLfloat newColor[4] = {1, 0, 0, 1};
		allSquares[index]->setColor(newColor);
		allSquares[index]->grow();
	}
	
	//toggle rotation
	if (button == GLUT_RIGHT_BUTTON)
	{
		allSquares[index]->isRotating = !allSquares[index]->isRotating;
	}
	
	if (square1 == -1)
	{
		square1 = allSquares[index]->getName();
	}
	else if (square2 == -1)
	{
		square2 = allSquares[index]->getName();
		
		for (int i = 0; i < squareLength; i++)
		{
			if (allSquares[i]->getName() == square1)
			{
				//*allSquares[i] = *allSquares[i] + *allSquares[index];
				//allSquares[index]->hide();
			}
		}

		square1 = -1;
		square2 = -1;

	}

}

void processHits (GLuint hits, GLuint buffer[], int button)
{
 GLuint *ptr =(GLuint *) buffer;
 
 GLuint names = *ptr;
 ptr++;
 ptr++;
 ptr++;
  //loop through hits if you want to process ALL objects that were selected
 //for (int i=0; i < hits; i++) 
  //{
 if (names < squareLength)
 {
	 for (int j = 0; j < names; j++)
	 {
		cout<< "Selected Name:" << *ptr << endl;
    	for (int k = 0; k < squareLength; k++)
	    {
			//if true then object received a mouse click (others might have also)
			if (allSquares[k]->getName() == *ptr)
			{
				//this object was click on
				gotClicked(k, button);
			}
		}
   	  ptr++;
	 }
 }
 //}
}

void selectionDetection(int button, int state, int x, int y)
{
 GLuint selectBuf[ BUFSIZE ] ;
 GLint viewport[4];
 if (state !=GLUT_DOWN)
	 return;
 glGetIntegerv(GL_VIEWPORT, viewport);
 glSelectBuffer(BUFSIZE, selectBuf);
 (void) glRenderMode(GL_SELECT);
 glInitNames();
 glPushName(0);
 glMatrixMode(GL_PROJECTION);
 glPushMatrix();
   glLoadIdentity();
   gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);
   gluPerspective(45.0, (GLfloat) ww/(GLfloat) wh, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW); 
   glPushMatrix();
     draw(GL_SELECT);
   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glFlush();
 glMatrixMode(GL_MODELVIEW); 
 processHits( glRenderMode(GL_RENDER),selectBuf, button);
}




//fires on mouse move when button is down. 
void mouseMove(int x, int y)
{
	//cout << "x:" << x << "||y:" << y << endl;
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

	selectionDetection(button, state, x, y);


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
		//cout << "last_x_pos:" << last_x_pos << "||x:" << x << endl;
	}
}


//main, set the environment
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   //glutInitWindowSize(1280, 700); 
   glutInitWindowSize(ww, wh); 
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