#include <iostream>
#include <glut.h>


using namespace std;

#define PI 3.14159265
static int step = 90;

/* position of light source */
static GLfloat lpos[] = {-2.5, 2.5, 2.5, 1.0};

/* position of viewer */
static GLdouble viewer[] = {2.0, 3.0, 10.0}; 

/* vectors to specify material properties */ 
static GLfloat high[]  = {100.0}; /* for shininess */
static GLfloat medium[]  = {50.0}; /* for shininess */
static GLfloat none[]    = {0.0, 0.0, 0.0, 1.0};
static GLfloat white[]   = {1.0, 1.0, 1.0, 1.0};
static GLfloat gray[]    = {0.5, 0.5, 0.5, 1.0};
static GLfloat orange[]  = {1.0, 0.5, 0.0, 0.5};
static GLfloat red[]     = {1.0, 0.0, 0.0, 1.0};
static GLfloat green[]   = {0.0, 1.0, 0.0, 1.0};
static GLfloat blue[]    = {0.0, 0.0, 1.0, 1.0};
static GLfloat yellow[]  = {1.0, 1.0, 0.0, 1.0}; 
static GLfloat magenta[] = {1.0, 0.0, 1.0, 1.0}; 
static GLfloat cyan[]    = {0.0, 1.0, 1.0, 1.0}; 
static GLfloat cyan_dull[]= {0.0, 0.4, 0.4, 1.0}; 

/* vectors to specify cube */ 
static GLfloat vdata[8][3] = 
 { 
   {-1.0, 0.0,-1.0},  /* 0 */
   { 1.0, 0.0,-1.0},  /* 1 */
   { 1.0, 2.0,-1.0},  /* 2 */
   {-1.0, 2.0,-1.0},  /* 3 */
   {-1.0, 0.0, 1.0},  /* 4 */
   { 1.0, 0.0, 1.0},  /* 5 */
   { 1.0, 2.0, 1.0},  /* 6 */
   {-1.0, 2.0, 1.0}   /* 7 */
 };

static GLuint fdata[6][4] =
 {
   {1,0,3,2},  /* back   */ 
   {0,4,7,3},  /* left   */
   {5,1,2,6},  /* right  */ 
   {4,5,6,7},  /* front  */
   {0,1,5,4},  /* bottom */
   {2,3,7,6}   /* top    */
 };

/* normal vectors for the six faces */
static GLfloat normaldata[6][3] = 
 {
   { 0.0, 0.0,-1.0},  /* back   */ 
   {-1.0, 0.0, 0.0},  /* left   */
   { 1.0, 0.0, 0.0},  /* right  */
   { 0.0, 0.0, 1.0},  /* front  */
   { 0.0,-1.0, 0.0},  /* bottom */
   { 0.0, 1.0, 0.0}   /* top    */
 };


void writemessage()
{
   printf("\n\
   bcd.cpp by Joe Baldwin\n\
   uses double buffering for smooth animation\n\n\
   a, A, b, B, c, C ---------- change light source position\n\
   x, X, y, Y, z, Z ---------- change viewer position\n\
   o, O ---------------------- open/close top\n\
   w ------------------------- toggle between fill and wire-frame\n\
   ESC ----------------------- exit\n\
   \n");
}

float getXnormal(float x1, float y1, float x2, float y2)
{
 float xtemp;
 float ytemp;
 ytemp = y2 - y1;
 xtemp = x2 - x1;
 float unit;
 bool negative = false;
 unit = sqrt((ytemp * ytemp) + (xtemp*xtemp));
 
 if (ytemp<0 && xtemp <0) negative= false;
 if (ytemp<0 && xtemp > 0) negative = true;
 if (ytemp>0 && xtemp <0) negative = true;
 if (ytemp>0 && xtemp > 0) negative = false;

 if (ytemp <0) ytemp = ytemp * -1;
 if (xtemp <0) xtemp = xtemp * -1;

 if (negative == false) xtemp = xtemp * -1;
  
  ytemp = ytemp / unit; 
 return ytemp;
}

float getYnormal(float x1, float y1, float x2, float y2)
{
 float xtemp;
 float ytemp;
 ytemp = y2 - y1;
 xtemp = x2 - x1;
 float unit;
  bool negative = false;
 unit = sqrt((ytemp * ytemp) + (xtemp*xtemp));
 
 if (ytemp<0 && xtemp <0) negative= false;
 if (ytemp<0 && xtemp > 0) negative = true;
 if (ytemp>0 && xtemp <0) negative = true;
 if (ytemp>0 && xtemp > 0) negative = false;

 if (ytemp <0) ytemp = ytemp * -1;
 if (xtemp <0) xtemp = xtemp * -1;
 if (negative == false) xtemp = xtemp * -1;
   

 xtemp = xtemp / unit; 
 return xtemp;
}

void init(void) 
{
   writemessage(); 

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      /* initially GL_FILL mode, later GL_LINE to show wireframe */

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
      /* enable two-sided lighting to properly show interior of cube */

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}


void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 2.0, 20.0);

   glMatrixMode(GL_MODELVIEW);
}



void drawB()
{ 
   //***********FRONT FACE OF LETTER B**************************

   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
   glVertex3f(0.75, 3.0, 0.0);   
   glVertex3f(0.0, 3.0,0.0);
      glVertex3f( 0.0, 0.0,0.0);
      glVertex3f( 0.75, 0.0, 0.0);
   glEnd();
 
   glBegin(GL_POLYGON);
      glVertex3f(1.10, 1.5, 0.0);
      glVertex3f(1.8, 1.7, 0.0);
	  glVertex3f(1.9, 1.9, 0.0);
	  glVertex3f(2.0, 2.25, 0.0);
	  glVertex3f(1.9, 2.6, 0.0);
	  glVertex3f(1.8, 2.8, 0.0);
	  glVertex3f(1.1, 3.0, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.10, 0.0, 0.0);
      glVertex3f(1.8, 0.2, 0.0);
      glVertex3f(1.9, 0.4, 0.0);
      glVertex3f(2.0, 0.75, 0.0);
      glVertex3f(1.9, 1.1, 0.0);
      glVertex3f(1.8, 1.3, 0.0);
      glVertex3f(1.1, 1.5, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.0, 2.0, 0.0);   
      glVertex3f(0.75, 2.0, 0.0);
      glVertex3f(0.75, 1.0, 0.0);
	  glVertex3f(1.0, 1.0, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.75, 2.5, 0.0);
	  glVertex3f(1.0, 2.5, 0.0);
	  glVertex3f(1.0, 3.0, 0.0);
	  glVertex3f(0.75, 3.0, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.5, 0.0);   
      glVertex3f(0.75, 0.5, 0.0);
      glVertex3f(0.75, 0.0, 0.0);
	  glVertex3f(1.0, 0.0, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.1, 3.0, 0.0);  
      glVertex3f(1.0, 3.0, 0.0);
      glVertex3f(1.0, 2.5, 0.0);
	  glVertex3f(1.1, 2.25, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.1, 2.25, 0.0);   
      glVertex3f(1.0, 2.0, 0.0);
      glVertex3f(1.0, 1.0, 0.0);
	  glVertex3f(1.1, 0.75, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.5, 0.0);
      glVertex3f(1.0, 0.0, 0.0);
      glVertex3f(1.1, 0.0, 0.0);
	  glVertex3f(1.1, 0.75,0.0);
   glEnd();
  //************BACK FACE OF LETTER B ************************
 
   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.0, 3.0,-1.0);
      glVertex3f(0.75, 3.0, -1.0);
      glVertex3f( 0.75, 0.0, -1.0);
      glVertex3f( 0.0, 0.0,-1.0);
   glEnd();
  
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 3.0, -1.0);
      glVertex3f(1.8, 2.8, -1.0);
      glVertex3f(1.9, 2.6, -1.0);
      glVertex3f(2.0, 2.25, -1.0);
	  glVertex3f(1.9, 1.9, -1.0);
	  glVertex3f(1.8, 1.7, -1.0);
	  glVertex3f(1.10, 1.5, -1.0);
   glEnd();
   
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 1.5, -1.0);
      glVertex3f(1.8, 1.3, -1.0);
      glVertex3f(1.9, 1.1, -1.0);
	  glVertex3f(2.0, 0.75, -1.0);
      glVertex3f(1.9, 0.4, -1.0);
	  glVertex3f(1.8, 0.2, -1.0);
	  glVertex3f(1.10, 0.0, -1.0);
     glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.75, 3.0, -1.0);
      glVertex3f(1.0, 3.0, -1.0);
      glVertex3f(1.0, 2.5, -1.0);
      glVertex3f(0.75, 2.5, -1.0);
   glEnd();

  glBegin(GL_POLYGON);
      glVertex3f(0.75, 2.0, -1.0);
      glVertex3f(1.0, 2.0, -1.0);
      glVertex3f(1.0, 1.0, -1.0);
      glVertex3f(0.75, 1.0, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.75, 0.5, -1.0);
      glVertex3f(1.0, 0.5, -1.0);
      glVertex3f(1.0, 0.0, -1.0);
      glVertex3f(0.75, 0.0, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.0, 3.0, -1.0);
      glVertex3f(1.1, 3.0, -1.0);
      glVertex3f(1.1, 2.25, -1.0);
      glVertex3f(1.0, 2.5, -1.0);
   glEnd();
 
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 2.0, -1.0);
      glVertex3f(1.1, 2.25, -1.0);
      glVertex3f(1.1, 0.75, -1.0);
      glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.0, -1.0);
      glVertex3f(1.0, 0.5, -1.0);
      glVertex3f(1.1, 0.75, -1.0);
      glVertex3f(1.1, 0.0, -1.0);
   glEnd();

   
   // *********SPINE*************************
   
   //Connect top spine
   glNormal3f( 0.0, 1.0, 0.0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 3.0, -1.0);  
      glVertex3f(0.0, 3.0,-1.0);
      glVertex3f( 0.0, 3.0,0.0);
	  glVertex3f( 0.75, 3.0, 0.0);
    glEnd();
    
	//Connect back spine
    glNormal3f( -1.0, 0.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(0.0, 3.0, 0.0);
	  glVertex3f(0.0, 3.0,-1.0);
      glVertex3f( 0.0, 0.0,-1.0);
	  glVertex3f( 0.0, 0.0, 0.0);
    glEnd();
    
	//connect bottom spine
	glNormal3f( 0.0, -1.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(0.0, 0.0,-1.0);
      glVertex3f(0.75, 0.0, -1.0); 
	  glVertex3f( 0.75, 0.0, -1.0);
	  glVertex3f( 0.0, 0.0,-1.0);
    glEnd();


   // *****************TOP BUMP***************************
    
   //Connect Bump 1ST
    glNormal3f(getXnormal(1.8, 2.8, 1.1, 3.0), getYnormal(1.8,2.8,1.1,3.0), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.8, 2.8, -1.0);
      glVertex3f(1.1, 3.0,-1.0);
      glVertex3f( 1.1, 3.0,0.0);
	  glVertex3f( 1.8, 2.8, 0.0);
    glEnd();
    //Connect Bump 2ND
	glNormal3f(getXnormal(1.9,2.6,1.8,2.8), getYnormal(1.9,2.6,1.8,2.8),0);
	glBegin(GL_POLYGON);
	  glVertex3f(1.9, 2.6, -1.0);
	  glVertex3f(1.8, 2.8, -1.0);
	  glVertex3f(1.8, 2.8, 0.0);
	  glVertex3f(1.9, 2.6, 0.0);
     glEnd();
	//Connect Bump 3RD
	glNormal3f(getXnormal(2.0, 2.25,1.9, 2.6), getYnormal(2.0,2.25,1.9, 2.6),0);
	 glBegin(GL_POLYGON);
       glVertex3f(2.0, 2.25, -1.0);  
	   glVertex3f(1.9, 2.6, -1.0);
       glVertex3f(1.9, 2.6, 0.0);
	   glVertex3f(2.0, 2.25, 0.0);
     glEnd();
   //connect bump 4TH
	 glNormal3f(getXnormal(1.9, 1.9, 2.0, 2.25), getYnormal(1.9,1.9,2.0, 2.25),0);
	 glBegin(GL_POLYGON);
        glVertex3f(1.9, 1.9, -1.0);   
	    glVertex3f(2.0, 2.25, -1.0);
	    glVertex3f(2.0, 2.25, 0.0);
		glVertex3f(1.9, 1.9, 0.0);
	 glEnd();
   //connect bump 5TH
	  glNormal3f(getXnormal(1.8,1.7,1.9, 1.9), getYnormal(1.8,1.7,1.9, 1.9),0);
      glBegin(GL_POLYGON);
       glVertex3f(1.8, 1.7, -1.0);
	   glVertex3f(1.9, 1.9, -1.0);
	   glVertex3f(1.9, 1.9, 0.0);
	   glVertex3f(1.8, 1.7, 0.0);
	  glEnd();
   //CONNECT BUMP 6TH   
	  glNormal3f(getXnormal(1.10,1.5,1.8, 1.7), getYnormal(1.10, 1.5,1.8, 1.7), 0);
	  glBegin(GL_POLYGON);
	   glVertex3f(1.10, 1.5, -1.0); 
	   glVertex3f(1.8, 1.7, -1.0);
	   glVertex3f(1.8, 1.7, 0.0);
	   glVertex3f(1.10, 1.5, 0.0);
	  glEnd();
   
   //****************BOTTOM BUMP************************

  
    //CONNECT BUMP 1ST 
    glNormal3f(getXnormal(1.8, 1.3, 1.1, 1.5), getYnormal(1.8, 1.3, 1.1, 1.5), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.8, 1.3, -1.0);  
	  glVertex3f(1.1, 1.5, -1.0);
      glVertex3f(1.1, 1.5, 0.0);
	  glVertex3f(1.8, 1.3, 0.0);
	glEnd();
  
    //CONNECT BUMP 2ND 
	glNormal3f(getXnormal(1.9, 1.1,1.8, 1.3), getYnormal(1.9, 1.1,1.8, 1.3), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.9, 1.1, -1.0);
      glVertex3f(1.8, 1.3, -1.0);
  	  glVertex3f(1.8, 1.3, 0.0);
	  glVertex3f(1.9, 1.1, 0.0);	  
    glEnd();
 
    //CONNECT BUMP 3RD
	glNormal3f(getXnormal(2.0, 0.75,1.9, 1.1), getYnormal(2.0, 0.75,1.9, 1.1), 0);
    glBegin(GL_POLYGON);
      glVertex3f(2.0, 0.75, -1.0);    
	  glVertex3f(1.9, 1.1, -1.0);
      glVertex3f(1.9, 1.1, 0.0);
      glVertex3f(2.0, 0.75, 0.0);	  
    glEnd();

    //CONNECT BUMP 4TH
	glNormal3f(getXnormal(1.9, 0.4,2.0, 0.75), getYnormal(1.9, 0.4,2.0, 0.75), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.9, 0.4, -1.0);
      glVertex3f(2.0, 0.75, -1.0);  
      glVertex3f(2.0, 0.75, 0.0);	
      glVertex3f(1.9, 0.4, 0.0);
	glEnd();

    //CONNECT BUMP 5TH
	glNormal3f(getXnormal(1.8, 0.2,1.9, 0.4), getYnormal(1.8, 0.2,1.9, 0.4), 0);
    glBegin(GL_POLYGON);
  	  glVertex3f(1.8, 0.2, -1.0);
      glVertex3f(1.9, 0.4, -1.0);
	  glVertex3f(1.9, 0.4, 0.0);
	  glVertex3f(1.8, 0.2, 0.0);
    glEnd();
  
    //CONNECT BUMP 6TH 
	glNormal3f(getXnormal(1.1, 0.0,1.8, 0.2), getYnormal(1.1, 0.0,1.8, 0.2), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.1, 0.0, -1.0);
      glVertex3f(1.8, 0.2, -1.0);
	  glVertex3f(1.8, 0.2, 0.0);
	  glVertex3f(1.1, 0.0, 0.0); 
    glEnd();
  
  //////////////////////////////////////////////////////////////

  //************above top "hole"*****************************
 
   
   //connect top of top "hole"
   glNormal3f( 0.0, 1.0, 0.0);  
      glBegin(GL_POLYGON);
      glVertex3f(0.75, 3.0, -1.0);      
      glVertex3f(0.75, 3.0, 0.0);   
      glVertex3f(1.1, 3.0, 0.0);
      glVertex3f(1.1, 3.0, -1.0);
	glEnd();
   //***************************INSIDE TOP HOLE************************
   

   
	//connect top of top hole
	glNormal3f( 0.0, -1.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(1.0, 2.5, 0.0);  
	  glVertex3f(0.75, 2.5, 0.0);
      glVertex3f(0.75, 2.5, -1.0);
	  glVertex3f(1.0, 2.5, -1.0);
   glEnd();

   //connect back of top hole
   glNormal3f( 1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 2.5, -1.0);   
      glVertex3f(0.75, 2.5, 0.0);
      glVertex3f(0.75, 2.0, 0.0);
	  glVertex3f(0.75, 2.0, -1.0);
   glEnd();
   
   //connect bottom of top hole
   glNormal3f( 0.0, 1.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 2.0, 0.0);
      glVertex3f(1.0, 2.0, 0.0);
      glVertex3f(1.0, 2.0, -1.0);
      glVertex3f(0.75, 2.0, -1.0);
   glEnd();

   //connect top diagonal of top hole
   glNormal3f(getXnormal(1.0,2.5,-1.1,2.25), getYnormal(1.0, 2.5, -1.1, 2.25), 0);
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 2.25, 0.0);   
      glVertex3f(1.0, 2.5, 0.0);
      glVertex3f(1.0, 2.5, -1.0);
	  glVertex3f(1.1, 2.25, -1.0);
   glEnd();

   //connect BOTTOM diagonal of top hole
   glNormal3f(getXnormal(1.0,2.0,-1.1,2.25), getYnormal(1.0,2.0,-1.1, 2.25), 0);
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 2.0, 0.0);   
      glVertex3f(1.1, 2.25, 0.0);
      glVertex3f(1.1, 2.25, -1.0);
	  glVertex3f(1.0, 2.0, -1.0);
   glEnd();


  
   //*****************INSIDE BOTTOM HOLE
   
	//connect top of bottom hole
	glNormal3f( 0.0, -1.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(1.0, 1.0, 0.0);  
	  glVertex3f(0.75, 1.0, 0.0);
      glVertex3f(0.75, 1.0, -1.0);
	  glVertex3f(1.0, 1.0, -1.0);
   glEnd();

   //connect back of bottom hole
   glNormal3f( 1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 1.0, -1.0);      
      glVertex3f(0.75, 1.0, 0.0);   
      glVertex3f(0.75, 0.5, 0.0);
      glVertex3f(0.75, 0.5, -1.0);
	  
   glEnd();
   
   //connect bottom of bottom hole
   glNormal3f( 0.0, 1.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 0.5, 0.0);
      glVertex3f(1.0, 0.5, 0.0);
      glVertex3f(1.0, 0.5, -1.0);
      glVertex3f(0.75, 0.5, -1.0);
   glEnd();

   //connect top diagonal of bottom hole
   glNormal3f(getXnormal(1.0,1.0,-1.1,0.75), getYnormal(1.0,1.0,-1.1,0.75), 0);
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 0.75, 0.0);   
      glVertex3f(1.0, 1.0, 0.0);
      glVertex3f(1.0, 1.0, -1.0);
	  glVertex3f(1.1, 0.75, -1.0);
   glEnd();

   //connect BOTTOM diagonal of bottom hole
   glNormal3f(getXnormal(1.0,0.5,-1.1,0.75), getYnormal(1.0,0.5,-1.1,0.75), 0);
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.5, 0.0);   
      glVertex3f(1.1, 0.75, 0.0);
      glVertex3f(1.1, 0.75, -1.0);
	  glVertex3f(1.0, 0.5, -1.0);
   glEnd();


}

void drawC()
{
   	
   float angle = ((float)step/180) * PI;
   //Y =  2.0 + 2.0 * sin(angle);
   //Z = -1.0 + 2.0 * cos(angle);
   //float Y =2.0 * sin(angle);
   //float Z =2.0 * cos(angle);
   
   //normalY = cos(angle);
   //normalZ = -sin(angle);

   //glNormal3f(0, normalY, normalZ);
   /*
   glBegin(GL_QUADS);
     glVertex3f( 1.0,   Y,   Z);
     glVertex3f( 1.0, 2.0,-1.0);
     glVertex3f(-1.0, 2.0,-1.0);
     glVertex3f(-1.0,   Y,   Z);
   glEnd();
   */
  float x1, y1;
  x1 = 0.15;
  y1 = 2.6;
  
  //FRONT FACE OF LETTER C
  //***************** MIDDLE *********************************
   glNormal3f( -cos(angle), 0, sin(angle));  
   glBegin(GL_POLYGON);
      glVertex3f(0.0 * sin(angle),  0.75, 0.0);
	  glVertex3f(0.15 * sin(angle) , 0.4,  0.15 * cos(angle));
	  glVertex3f(0.6 * sin(angle),    1.25, 0.6  * cos(angle));
	  glVertex3f(0.6 * sin(angle),    1.75, 0.6  * cos(angle));
	  glVertex3f(0.15 * sin(angle),  2.6,  0.15 * cos(angle));
	  glVertex3f(0.0 * sin(angle), 2.25, 0.0 );
   glEnd();
   
    //********************** 2ND SECTION ABOVE*************** 
   glBegin(GL_POLYGON);
      glVertex3f(0.4 * sin(angle), 2.85, 0.4 * cos(angle) );   
      glVertex3f(0.15 * sin(angle), 2.6, 0.15 * cos(angle)  );
      glVertex3f(0.6 * sin(angle), 1.75, 0.6 * cos(angle) );
	  glVertex3f(0.7 * sin(angle), 1.9,  0.7 * cos(angle) );
   glEnd();
   
    //********************** 2ND SECTION BELOW*************** 
   glBegin(GL_POLYGON);
      glVertex3f(0.15 * sin(angle), 0.4, 0.15 * cos(angle));   
      glVertex3f(0.4 * sin(angle), 0.15, 0.4 * cos(angle));   
      glVertex3f(0.7 * sin(angle), 1.1,  0.7 * cos(angle));
	  glVertex3f(0.6 * sin(angle), 1.25, 0.6 * cos(angle));
   glEnd();
    
   //*********************************4TH SECTION ABOVE
   glBegin(GL_POLYGON);
      glVertex3f(0.8 * sin(angle), 2.0, 0.8 * cos(angle));      
      glVertex3f(0.7 * sin(angle), 3.0, 0.7 * cos(angle));      
      glVertex3f(0.4 * sin(angle), 2.85, 0.4 * cos(angle));
	  glVertex3f(0.7 * sin(angle), 1.9, 0.7 * cos(angle));
   glEnd();
    
   //*********************************4TH SECTION BELOW
   glBegin(GL_POLYGON);
      glVertex3f(0.7 * sin(angle), 0.0, 0.7 * cos(angle));      
      glVertex3f(0.8 * sin(angle), 1.0, 0.8 * cos(angle));   
      glVertex3f(0.7 * sin(angle), 1.1, 0.7 * cos(angle));
	  glVertex3f(0.4 * sin(angle), 0.15, 0.4 * cos(angle));
   glEnd();
   
    //************************6TH SECTION ABOVE***********
   float Cx[] = {1.4, 1.2, 1.3,  1.6, 1.9, 1.4,  1.4,  2.0,  2.0 };
   float Cy[] = {3.0, 2.0, 1.95, 2.8, 2.5, 1.85, 1.65, 1.65, 2.0 };
   glBegin(GL_POLYGON);
     glVertex3f(Cx[0] * sin(angle), Cy[0], Cx[0] * cos(angle));   	       
     glVertex3f(Cx[1] * sin(angle), Cy[1], Cx[1] * cos(angle));            
     glVertex3f(Cx[2] * sin(angle), Cy[2], Cx[2] * cos(angle));   
	 glVertex3f(Cx[3] * sin(angle), Cy[3], Cx[3] * cos(angle));   
   glEnd();

   //****************************6TH SECTION BELOW
   //////////////////////////////////////////////////////////
   glBegin(GL_POLYGON);
      glVertex3f(1.2 * sin(angle), 1.0, 1.2 * cos(angle));            
      glVertex3f(1.4 * sin(angle), 0.0, 1.4 * cos(angle));   	     
   	  glVertex3f(1.6 * sin(angle), 0.2, 1.6 * cos(angle));   
	  glVertex3f(1.3 * sin(angle), 1.05, 1.3 * cos(angle));   
   glEnd();

     //***************************TOP***********************
   glBegin(GL_POLYGON);
      glVertex3f(0.7  * sin(angle), 3.0, 0.7  * cos(angle));   	  
      glVertex3f(0.8  * sin(angle), 2.0, 0.8  * cos(angle));         
      glVertex3f(1.2  * sin(angle), 2.0, 1.2  * cos(angle));   
	  glVertex3f(1.4  * sin(angle), 3.0, 1.4  * cos(angle));   
   glEnd();

    //***********************7Th SECTION ABOVE
   glBegin(GL_POLYGON);
     glVertex3f(Cx[3] * sin(angle), Cy[3], Cx[3] * cos(angle));   	      
     glVertex3f(Cx[2] * sin(angle), Cy[2], Cx[2] * cos(angle));               
     glVertex3f(Cx[5] * sin(angle), Cy[5], Cx[5] * cos(angle));   
     glVertex3f(Cx[4] * sin(angle), Cy[4], Cx[4] * cos(angle));   
   glEnd();
   
   //***********************7Th SECTION BELOW
   glBegin(GL_POLYGON);
      glVertex3f(1.4 * sin(angle), 1.15, 1.4 * cos(angle));   	     
      glVertex3f(1.3 * sin(angle), 1.05, 1.3 * cos(angle));               
   	  glVertex3f(1.6 * sin(angle), 0.2, 1.6 * cos(angle));   
	  glVertex3f(1.9 * sin(angle), 0.5, 1.9 * cos(angle));   
   glEnd();
 
    //************************TOP END**********************
   glBegin(GL_POLYGON);
      glVertex3f(Cx[4] * sin(angle), Cy[4], Cx[4] * cos(angle));   	  
      glVertex3f(Cx[5] * sin(angle), Cy[5], Cx[5] * cos(angle));         
      glVertex3f(Cx[6] * sin(angle), Cy[6], Cx[6] * cos(angle));   
	  glVertex3f(Cx[7] * sin(angle), Cy[7], Cx[7] * cos(angle));   
	  glVertex3f(Cx[8] * sin(angle), Cy[8], Cx[8] * cos(angle));   
   glEnd();

   //************************BOTTOM END**********************
   glBegin(GL_POLYGON);
      glVertex3f(2.0 * sin(angle), 0.65, 2.0 * cos(angle));   
      glVertex3f(2.0 * sin(angle), 1.35, 2.0 * cos(angle));   
      glVertex3f(1.4 * sin(angle), 1.35, 1.4 * cos(angle));   
      glVertex3f(1.4 * sin(angle),  1.15, 1.4 * cos(angle));         
      glVertex3f(1.9 * sin(angle),  0.5, 1.9 * cos(angle));   	  
   glEnd();

   
   //************************BOTTOM********************
   glBegin(GL_POLYGON);
      glVertex3f(0.8 * sin(angle), 1.0, 0.8 * cos(angle)); 
      glVertex3f(0.7 * sin(angle), 0.0, 0.7 * cos(angle));   	     
   	  glVertex3f(1.4 * sin(angle), 0.0, 1.4 * cos(angle));   
	  glVertex3f(1.2 * sin(angle), 1.0, 1.2 * cos(angle));   
   glEnd();
   
  
   //***************BACK FACE OF LETTER C***************************** 
   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0, 2.25, -1.0);
      glVertex3f(0.15, 2.6, -1.0);
      glVertex3f(0.6, 1.75, -1.0);
      glVertex3f(0.6, 1.25, -1.0);
	  glVertex3f(0.15, 0.4, -1.0);
	  glVertex3f(0.0, 0.75, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.7, 1.9, -1.0);
	  glVertex3f(0.6, 1.75, -1.0);
	  glVertex3f(x1, y1, -1.0);
	  glVertex3f(0.4, 2.85, -1.0);   
   glEnd();

   glBegin(GL_POLYGON);
     glVertex3f(0.4, 0.15, -1.0);      
     glVertex3f(0.15, 0.4, -1.0);   
     glVertex3f(0.6, 1.25, -1.0);
	 glVertex3f(0.7, 1.1, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.7, 3.0, -1.0);      
      glVertex3f(0.8, 2.0, -1.0);   
      glVertex3f(0.7, 1.9, -1.0);
	  glVertex3f(0.4, 2.85, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.8, 1.0, -1.0);      
      glVertex3f(0.7, 0.0, -1.0);      
      glVertex3f(0.4, 0.15, -1.0);
	  glVertex3f(0.7, 1.1, -1.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(Cx[1], Cy[1], -1.0);            
      glVertex3f(Cx[0], Cy[0], -1.0);   	  
      glVertex3f(Cx[3], Cy[3], -1.0);   
	  glVertex3f(Cx[2], Cy[2], -1.0);   
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.4, 0.0, -1.0);   	  
      glVertex3f(1.2, 1.0, -1.0);         
      glVertex3f(1.3, 1.05, -1.0);   
	  glVertex3f(1.6, 0.2, -1.0);   
   glEnd();

   glBegin(GL_POLYGON);
     glVertex3f(0.8, 2.0, -1.0);              
     glVertex3f(0.7, 3.0, -1.0);   	    
     glVertex3f(1.4, 3.0, -1.0);   
	 glVertex3f(1.2, 2.0, -1.0);   
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(Cx[2], Cy[2], -1.0);            
      glVertex3f(Cx[3], Cy[3], -1.0);   	  
      glVertex3f(Cx[4], Cy[4], -1.0);   
	  glVertex3f(Cx[5], Cy[5], -1.0);   
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.3, 1.05, -1.0);            
      glVertex3f(1.4, 1.15, -1.0);   	  
      glVertex3f(1.9, 0.5, -1.0);   
	  glVertex3f(1.6, 0.2, -1.0);   
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(Cx[8], Cy[8], -1.0);   
	  glVertex3f(Cx[7], Cy[7], -1.0);   
	  glVertex3f(Cx[6], Cy[6], -1.0);   
	  glVertex3f(Cx[5], Cy[5], -1.0);         
	  glVertex3f(Cx[4], Cy[4], -1.0);   	  
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(1.9,  0.5, -1.0);   	  
	  glVertex3f(1.4,  1.15,-1.0);         
	  glVertex3f(1.4, 1.35, -1.0);   
	  glVertex3f(2.0, 1.35, -1.0);   
	  glVertex3f(2.0, 0.65, -1.0);   
   glEnd();
   
   glBegin(GL_POLYGON);
      glVertex3f(0.7, 0.0, -1.0);   	     
      glVertex3f(0.8, 1.0, -1.0); 
      glVertex3f(1.2, 1.0, -1.0);   
	  glVertex3f(1.4, 0.0, -1.0);   
   glEnd();

   //**********************OUTSIDE
   //Starting with Face On Front of C, Moving Counter Clockwise
   //Front 1
    //connect bottom
   glNormal3f( 0.0, -1.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(2.0, 1.65 ,0.0);   	  
      glVertex3f(1.4, 1.65, 0.0);         
      glVertex3f(1.4,1.65, -1.0);   
	  glVertex3f(2.0,1.65, -1.0);   
   glEnd();
   
   
   glNormal3f( 1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(2.0, 2.0, 0.0);            
      glVertex3f(2.0, 1.65 ,0.0);   	  
      glVertex3f(2.0, 1.65, -1.0);   
	  glVertex3f(2.0, 2.0, -1.0);   
   glEnd();

   //Front 2
   glNormal3f(getXnormal(1.9, 2.5, 2.0, 2.0), getYnormal(1.9, 2.5, 2.0, 2.0), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.9, 2.5 ,0.0);   	     
      glVertex3f(2.0, 2.0, 0.0);            
      glVertex3f(2.0, 2.0, -1.0);   
	  glVertex3f(1.9, 2.5, -1.0);   
   glEnd();
   
   //Front 3
   glNormal3f(getXnormal(1.6, 2.8, 1.9, 2.5), getYnormal(1.6, 2.8, 1.9, 2.5), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.6, 2.8, 0.0);               
      glVertex3f(1.9, 2.5 ,0.0);   	     
      glVertex3f(1.9, 2.5, -1.0);   
	  glVertex3f(1.6, 2.8, -1.0);   
   glEnd();
   
   //Front 4
   glNormal3f(getXnormal(1.4, 3.0, 1.6, 2.8), getYnormal(1.4, 3.0, 1.6, 2.8), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.4, 3.0,  0.0);   	     
      glVertex3f(1.6, 2.8,  0.0);            
      glVertex3f(1.6, 2.8, -1.0);   
	  glVertex3f(1.4, 3.0, -1.0);   
   glEnd();

   //Front 5  -- TOP
   glNormal3f( 0.0, 1.0, 0.0);  
   glBegin(GL_POLYGON);
     glVertex3f(0.7, 3.0, -1.0);  
     glVertex3f(0.7, 3.0, 0.0);
	 glVertex3f(1.4, 3.0, 0.0);
	 glVertex3f(1.4, 3.0, -1.0);
   glEnd();

   //Front 6
   glNormal3f(-(getXnormal(0.4, 2.85, 0.7, 3.0)), -(getYnormal(0.4, 2.85, 0.7, 3.0)), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.4, 2.85, -1.0);   
      glVertex3f(0.4, 2.85,0.0);         
      glVertex3f(0.7, 3.0, 0.0);
      glVertex3f(0.7, 3.0,-1.0);      
   glEnd();

   //Front 7
   glNormal3f(- getXnormal(0.4, 2.85, 0.15, 2.6), - getYnormal(0.4, 2.85, 0.15, 2.6), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.15, 2.6, -1.0);   
      glVertex3f(0.15, 2.6, 0.0);
	  glVertex3f(0.4, 2.85, 0.0);   
	  glVertex3f(0.4, 2.85, -1.0);
   glEnd();

   //Front 7.5
   glNormal3f(- getXnormal(0.0, 2.25, 0.15, 2.6), - getYnormal(0.0, 2.25, 0.15, 2.6), 0);
   glBegin(GL_POLYGON);
      glVertex3f(0.0, 2.25, -1.0);   
      glVertex3f(0.0, 2.25, 0.0);
      glVertex3f(0.15, 2.6, 0.0);
	  glVertex3f(0.15, 2.6, -1.0);
   glEnd();

 
   //Front 8 - Back
   glNormal3f(-1.0, 0.0, 0.0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.0, 0.75, -1.0);   
      glVertex3f(0.0, 0.75, 0.0);
      glVertex3f(0.0, 2.25, 0.0);
	  glVertex3f(0.0, 2.25, -1.0);
   glEnd();
  
   //Front 9 
   glNormal3f(- getXnormal(0.0, 0.75, 0.15, 0.4), - getYnormal(0.0, 0.75, 0.15, 0.4), 0);   
  glBegin(GL_POLYGON);
      glVertex3f(0.0, 0.75, 0.0);   
      glVertex3f(0.0, 0.75, -1.0);   
      glVertex3f(0.15, 0.4, -1.0);
	  glVertex3f(0.15, 0.4, 0.0);
   glEnd();
   
   //Front 10
   glNormal3f(- getXnormal(0.4, 0.15, 0.15, 0.4),- getYnormal(0.4, 0.15, 0.15, 0.4), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.15,-1.0);      
      glVertex3f(0.4, 0.15, 0.0);   
      glVertex3f(0.15, 0.4, 0.0);
	  glVertex3f(0.15, 0.4, -1.0);
   glEnd();
   
   //Front 11
   glNormal3f(- getXnormal(0.4, 0.15, 0.7, 0.0), - getYnormal(0.4, 0.15, 0.7, 0.0), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.4, 0.15, 0.0);      
      glVertex3f(0.4, 0.15,-1.0);      
      glVertex3f(0.7, 0.0, -1.0);
      glVertex3f(0.7, 0.0, 0.0);
   glEnd();

   //Front 12 - Bottom
   glNormal3f(getXnormal(1.4, 0.0, 0.7, 0.0), getYnormal(1.4, 0.0, 0.7, 0.0), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.4, 0.0,-1.0);         
      glVertex3f(1.4, 0.0, 0.0);      
      glVertex3f(0.7, 0.0, 0.0);
	  glVertex3f(0.7, 0.0, -1.0);
   glEnd();

    //Front 14
   glNormal3f(getXnormal(2.0, 0.65, 1.9, 0.5), getYnormal(2.0, 0.65, 1.9, 0.5), 0);   
    glBegin(GL_POLYGON);
      glVertex3f(2.0, 0.65, -1.0);               
      glVertex3f(2.0, 0.65,0.0);   	     
      glVertex3f(1.9, 0.5, 0.0);   
	  glVertex3f(1.9,0.5, -1.0);   
   glEnd();
 
    //Front 15
   glNormal3f(getXnormal(1.6, 0.2, 1.9, 0.5), getYnormal(1.6, 0.2, 1.9, 0.5), 0);   
    glBegin(GL_POLYGON);
      glVertex3f(1.6,0.2, 0.0);   	       
	  glVertex3f(1.6,0.2, -1.0);               
      glVertex3f(1.9,0.5, -1.0);   
	  glVertex3f(1.9, 0.5, 0.0);   
   glEnd();
   
    //Front 16 - 
  glNormal3f(getXnormal(1.6, 0.2, 1.4, 0.0), getYnormal(1.6, 0.2, 1.4, 0.0), 0);   
    glBegin(GL_POLYGON);
      glVertex3f(1.6,0.2, -1.0);               
      glVertex3f(1.6,0.2, 0.0);   	     
      glVertex3f(1.4,0.0, 0.0);   
	  glVertex3f(1.4,0.0, -1.0);   
   glEnd();
   
   //Front 13 - end
   glNormal3f(1.0,0.0, 0.0);   
   glBegin(GL_POLYGON);
      glVertex3f(2.0, 1.35, -1.0);               
      glVertex3f(2.0,1.35 ,0.0);   	     
      glVertex3f(2.0, 0.65, 0.0);   
	  glVertex3f(2.0,0.65, -1.0);   
   glEnd();
 
     //connect top
   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.4, 1.35, -1.0);               
      glVertex3f(1.4,1.35 ,0.0);   	     
      glVertex3f(2.0, 1.35, 0.0);   
	  glVertex3f(2.0,1.35, -1.0);   
   glEnd();
 

   
   //******************************INSIDE************************
   // Starting with face on the inside of the top half of the C on the right.
   //  Inside - Back
   glNormal3f( 1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.6, 1.75, -1.0);   
      glVertex3f(0.6, 1.75, 0.0);
      glVertex3f(0.6, 1.25, 0.0);
	  glVertex3f(0.6, 1.25, -1.0);
   glEnd();
   
   //connect Top - inside
   glNormal3f( -1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.4,1.65, 0.0);            
      glVertex3f(1.4,1.85 ,0.0);   	  
      glVertex3f(1.4,1.85, -1.0);   
	  glVertex3f(1.4,1.65, -1.0);   
   glEnd();
   
   //connect 2nd inside
   glNormal3f(- getXnormal(1.4, 1.85, 1.3, 1.95),- getYnormal(1.4, 1.85, 1.3, 1.95), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.4, 1.85 ,0.0);   	     
      glVertex3f(1.3, 1.95, 0.0);            
      glVertex3f(1.3, 1.95, -1.0);   
	  glVertex3f(1.4, 1.85, -1.0);   
   glEnd();
   
   //connect 3rd inside
   glNormal3f(- getXnormal(1.3, 1.95, 1.2, 2.0),- getYnormal(1.3, 1.95, 1.2, 2.0), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.3, 1.95 ,0.0);   	     
      glVertex3f(1.2, 2.0, 0.0);            
      glVertex3f(1.2, 2.0, -1.0);   
	  glVertex3f(1.3, 1.95, -1.0);   
   glEnd();
   
   //connect 4th inside - Top
   glNormal3f( 0.0, -1.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.2, 2.0, 0.0);               
      glVertex3f(0.8, 2.0 ,0.0);   	     
      glVertex3f(0.8, 2.0, -1.0);   
	  glVertex3f(1.2, 2.0, -1.0);   
   glEnd();

   //connect 5th inside
   glNormal3f(getXnormal(0.8, 2.0, 0.7, 1.9), getYnormal(0.8, 2.0, 0.7, 1.9), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.8, 2.0 ,0.0);   	        
      glVertex3f(0.7, 1.9, 0.0);               
      glVertex3f(0.7, 1.9, -1.0);   
	  glVertex3f(0.8, 2.0, -1.0);   
   glEnd();
   
   //connect 6th inside
   glNormal3f(getXnormal(0.7, 1.9, 0.6, 1.75), getYnormal(0.7, 1.9, 0.6, 1.75), 0);   
   glBegin(GL_POLYGON);
     glVertex3f(0.7, 1.9, 0.0);                  
     glVertex3f(0.6, 1.75 ,0.0);   	              
     glVertex3f(0.6, 1.75, -1.0);   
     glVertex3f(0.7, 1.9, -1.0);   
   glEnd();

   //connect 8th inside
   glNormal3f(getXnormal(0.7, 1.1, 0.6, 1.25), getYnormal(0.7, 1.1, 0.6, 1.25), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.7, 1.1, 0.0);   
      glVertex3f(0.7, 1.1, -1.0);   
      glVertex3f(0.6, 1.25, -1.0);
	  glVertex3f(0.6, 1.25, 0.0);
   glEnd();

   //connect 9th inside
   glNormal3f(getXnormal(0.7, 1.1, 0.8, 1.0), getYnormal(0.7, 1.1, 0.8, 1.0), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.7, 1.1, -1.0);   
      glVertex3f(0.7, 1.1, 0.0);
      glVertex3f(0.8, 1.0, 0.0);
	  glVertex3f(0.8, 1.0, -1.0);
   glEnd();

   //connect 10th inside - Bottom
   glNormal3f(0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
     glVertex3f(1.2, 1.0, 0.0);   
     glVertex3f(1.2, 1.0, -1.0);   
     glVertex3f(0.8, 1.0, -1.0);
	 glVertex3f(0.8, 1.0, 0.0);
   glEnd();
   
   //connect 11th inside
   glNormal3f(- getXnormal(1.2, 1.0, 1.3, 1.05),- getYnormal(1.2, 1.0, 1.3, 1.05), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.2, 1.0, -1.0);   
      glVertex3f(1.2, 1.0, 0.0);
      glVertex3f(1.3, 1.05, 0.0);
	  glVertex3f(1.3, 1.05, -1.0);
   glEnd();

   //connect 12th inside
   glNormal3f(- getXnormal(1.4, 1.15, 1.3, 1.05),- getYnormal(1.4, 1.15, 1.3, 1.05), 0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.4, 1.15, 0.0);   
      glVertex3f(1.4, 1.15, -1.0);   
      glVertex3f(1.3, 1.05, -1.0);
	  glVertex3f(1.3, 1.05, 0.0);
   glEnd();

   //connect 13th inside - end
   glNormal3f(-1.0, 0.0, 0.0);   
   glBegin(GL_POLYGON);
      glVertex3f(1.4, 1.15, -1.0);   
      glVertex3f(1.4, 1.15, 0.0);
      glVertex3f(1.4, 1.35, 0.0);
	  glVertex3f(1.4, 1.35, -1.0);
   glEnd();

      
   

  

}

void drawD()
{ 
   // *********SPINE*************************
   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
   glVertex3f(0.75, 3.0, 0.0);   
   glVertex3f(0.0, 3.0,0.0);
      glVertex3f( 0.0, 0.0,0.0);
      glVertex3f( 0.75, 0.0, 0.0);
   glEnd();

   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.0, 3.0,-1.0);
      glVertex3f(0.75, 3.0, -1.0);
      glVertex3f( 0.75, 0.0, -1.0);
      glVertex3f( 0.0, 0.0,-1.0);
   glEnd();
   
   //Connect top spine
   glNormal3f( 0.0, 1.0, 0.0);   
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 3.0, -1.0);  
      glVertex3f(0.0, 3.0,-1.0);
      glVertex3f( 0.0, 3.0,0.0);
	  glVertex3f( 0.75, 3.0, 0.0);
    glEnd();
    
	//Connect back spine
    glNormal3f( -1.0, 0.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(0.0, 3.0, 0.0);
	  glVertex3f(0.0, 3.0,-1.0);
      glVertex3f( 0.0, 0.0,-1.0);
	  glVertex3f( 0.0, 0.0, 0.0);
    glEnd();
    
	//connect bottom spine
	glNormal3f( 0.0, -1.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(0.0, 0.0,-1.0);
      glVertex3f(0.75, 0.0, -1.0); 
	  glVertex3f( 0.75, 0.0, -1.0);
	  glVertex3f( 0.0, 0.0,-1.0);
    glEnd();


   // *****************TOP BUMP***************************
   glNormal3f( 0.0, 0.0, 1.0);  
   
   glBegin(GL_POLYGON);
      glVertex3f(1.10, 0.0, 0.0);
      glVertex3f(1.8, 0.2, 0.0);
      glVertex3f(1.9, 0.4, 0.0);
      glVertex3f(2.0, 0.75, 0.0);
      glVertex3f(2.0, 2.25, 0.0);
	  glVertex3f(1.9, 2.6, 0.0);
	  glVertex3f(1.8, 2.8, 0.0);
	  glVertex3f(1.1, 3.0, 0.0);
   glEnd();
   
   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 3.0, -1.0);
      glVertex3f(1.8, 2.8, -1.0);
	  glVertex3f(1.9, 2.6, -1.0);
	  glVertex3f(2.0, 2.25, -1.0);
	  glVertex3f(2.0, 0.75, -1.0);
	  glVertex3f(1.9, 0.4, -1.0);
	  glVertex3f(1.8, 0.2, -1.0);
	  glVertex3f(1.10, 0.0, -1.0);
	  glEnd();
   
    
   //Connect Bump 1ST
    glNormal3f(getXnormal(1.8, 2.8, 1.1, 3.0), getYnormal(1.8,2.8,1.1,3.0), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.8, 2.8, -1.0);
      glVertex3f(1.1, 3.0,-1.0);
      glVertex3f( 1.1, 3.0,0.0);
	  glVertex3f( 1.8, 2.8, 0.0);
    glEnd();
    //Connect Bump 2ND
	glNormal3f(getXnormal(1.9,2.6,1.8,2.8), getYnormal(1.9,2.6,1.8,2.8),0);
	glBegin(GL_POLYGON);
	  glVertex3f(1.9, 2.6, -1.0);
	  glVertex3f(1.8, 2.8, -1.0);
	  glVertex3f(1.8, 2.8, 0.0);
	  glVertex3f(1.9, 2.6, 0.0);
     glEnd();
	//Connect Bump 3RD
	glNormal3f(getXnormal(2.0, 2.25,1.9, 2.6), getYnormal(2.0,2.25,1.9, 2.6),0);
	 glBegin(GL_POLYGON);
       glVertex3f(2.0, 2.25, -1.0);  
	   glVertex3f(1.9, 2.6, -1.0);
       glVertex3f(1.9, 2.6, 0.0);
	   glVertex3f(2.0, 2.25, 0.0);
     glEnd();
  
    //CONNECT BUMP 4TH
	glNormal3f(getXnormal(1.9, 0.4,2.0, 0.75), getYnormal(1.9, 0.4,2.0, 0.75), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.9, 0.4, -1.0);
      glVertex3f(2.0, 0.75, -1.0);  
      glVertex3f(2.0, 0.75, 0.0);	
      glVertex3f(1.9, 0.4, 0.0);
	glEnd();

    //CONNECT BUMP 5TH
	glNormal3f(getXnormal(1.8, 0.2,1.9, 0.4), getYnormal(1.8, 0.2,1.9, 0.4), 0);
    glBegin(GL_POLYGON);
  	  glVertex3f(1.8, 0.2, -1.0);
      glVertex3f(1.9, 0.4, -1.0);
	  glVertex3f(1.9, 0.4, 0.0);
	  glVertex3f(1.8, 0.2, 0.0);
    glEnd();
  
    //CONNECT BUMP 6TH 
	glNormal3f(getXnormal(1.1, 0.0,1.8, 0.2), getYnormal(1.1, 0.0,1.8, 0.2), 0);
    glBegin(GL_POLYGON);
      glVertex3f(1.1, 0.0, -1.0);
      glVertex3f(1.8, 0.2, -1.0);
	  glVertex3f(1.8, 0.2, 0.0);
	  glVertex3f(1.1, 0.0, 0.0); 
    glEnd();
  
	//CONNECT BUMP FRONT
	glNormal3f(1.0,0.0, 0.0);
    glBegin(GL_POLYGON);
      glVertex3f(2.0, 0.75, -1.0);
      glVertex3f(2.0, 2.25, -1.0);
	  glVertex3f(2.0, 2.25, 0.0);
	  glVertex3f(2.0, 0.75, 0.0); 
    glEnd();
  
  //////////////////////////////////////////////////////////////
  //**********CONNECT FRONT OF HOLE
   glNormal3f( -1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 2.25, -1);
	  glVertex3f(1.1, 0.75, -1);
	  glVertex3f(1.1, 0.75, 0.0);
	  glVertex3f(1.1, 2.25, 0.0);
   glEnd();


  //************above top "hole"*****************************
   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 2.5, 0.0);
	  glVertex3f(1.0, 2.5, 0.0);
	  glVertex3f(1.0, 3.0, 0.0);
	  glVertex3f(0.75, 3.0, 0.0);
   glEnd();

   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 3.0, -1.0);
      glVertex3f(1.0, 3.0, -1.0);
      glVertex3f(1.0, 2.5, -1.0);
      glVertex3f(0.75, 2.5, -1.0);
   glEnd();
   
   //connect top of top "hole"
   glNormal3f( 0.0, 1.0, 0.0);  
      glBegin(GL_POLYGON);
      glVertex3f(0.75, 3.0, -1.0);      
      glVertex3f(0.75, 3.0, 0.0);   
      glVertex3f(1.1, 3.0, 0.0);
      glVertex3f(1.1, 3.0, -1.0);
	glEnd();
   //***************************INSIDE TOP HOLE************************
   

   
	//connect top of top hole
	glNormal3f( 0.0, -1.0, 0.0);  
	glBegin(GL_POLYGON);
      glVertex3f(1.0, 2.5, 0.0);  
	  glVertex3f(0.75, 2.5, 0.0);
      glVertex3f(0.75, 2.5, -1.0);
	  glVertex3f(1.0, 2.5, -1.0);
   glEnd();

   //connect top diagonal of top hole
   glNormal3f(getXnormal(1.0,2.5,-1.1,2.25), getYnormal(1.0, 2.5, -1.1, 2.25), 0);
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 2.25, 0.0);   
      glVertex3f(1.0, 2.5, 0.0);
      glVertex3f(1.0, 2.5, -1.0);
	  glVertex3f(1.1, 2.25, -1.0);
   glEnd();


  
   //*******************below bottom hole*****************************
   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.5, 0.0);   
      glVertex3f(0.75, 0.5, 0.0);
      glVertex3f(0.75, 0.0, 0.0);
	  glVertex3f(1.0, 0.0, 0.0);
   glEnd();
   
   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 0.5, -1.0);
      glVertex3f(1.0, 0.5, -1.0);
      glVertex3f(1.0, 0.0, -1.0);
      glVertex3f(0.75, 0.0, -1.0);
   glEnd();
 
   //*********************top of top hole*****************************   
   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.1, 3.0, 0.0);  
      glVertex3f(1.0, 3.0, 0.0);
      glVertex3f(1.0, 2.5, 0.0);
	  glVertex3f(1.1, 2.25, 0.0);
   glEnd();

   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 3.0, -1.0);
      glVertex3f(1.1, 3.0, -1.0);
      glVertex3f(1.1, 2.25, -1.0);
      glVertex3f(1.0, 2.5, -1.0);
   glEnd();
 
   //*********bottom of bottom hole****************************   
   glNormal3f( 0.0, 0.0, 1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.5, 0.0);
      glVertex3f(1.0, 0.0, 0.0);
      glVertex3f(1.1, 0.0, 0.0);
	  glVertex3f(1.1, 0.75, 0.0);
   glEnd();

   glNormal3f( 0.0, 0.0, -1.0);  
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.0, -1.0);
      glVertex3f(1.0, 0.5, -1.0);
      glVertex3f(1.1, 0.75, -1.0);
      glVertex3f(1.1, 0.0, -1.0);
   glEnd();
   //*****************INSIDE BOTTOM HOLE
   

   //connect back of bottom hole
   glNormal3f( 1.0, 0.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 2.5, -1.0);      
      glVertex3f(0.75, 2.5, 0.0);   
      glVertex3f(0.75, 0.5, 0.0);
      glVertex3f(0.75, 0.5, -1.0);
	  
   glEnd();
   
   //connect bottom of bottom hole
   glNormal3f( 0.0, 1.0, 0.0);  
   glBegin(GL_POLYGON);
      glVertex3f(0.75, 0.5, 0.0);
      glVertex3f(1.0, 0.5, 0.0);
      glVertex3f(1.0, 0.5, -1.0);
      glVertex3f(0.75, 0.5, -1.0);
   glEnd();
   
   //connect BOTTOM diagonal of bottom hole
   glNormal3f(getXnormal(1.0,0.5,-1.1,0.75), getYnormal(1.0,0.5,-1.1,0.75), 0);
   glBegin(GL_POLYGON);
      glVertex3f(1.0, 0.5, 0.0);   
      glVertex3f(1.1, 0.75, 0.0);
      glVertex3f(1.1, 0.75, -1.0);
	  glVertex3f(1.0, 0.5, -1.0);
   glEnd();


}

void display(void)
{
   static int i;
   static double angle, Y, Z, normalY, normalZ;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   /* initialize (modelview) matrix */
   glLoadIdentity(); 
   
   /*  - viewer position is set first by gluLookat
    *  - then light0 position is set and all objects are drawn
    *  - the order is important (there are exceptions, more later) */

   /* update viewer position */
   gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

   /* update light source position */
   glLightfv(GL_LIGHT0, GL_POSITION, lpos);

   /* draw sphere to show light source */
   glMaterialfv(GL_FRONT, GL_EMISSION, white); 
   glPushMatrix();
     glTranslatef(lpos[0],lpos[1],lpos[2]);
     glutSolidSphere(0.1, 10, 8);
   glPopMatrix();

   /* remaining objects do not emit light */
   glMaterialfv(GL_FRONT, GL_EMISSION, none);

   /* draw a tabletop */

   /* note: need to set BACK material properties of the table since
    * BACK becomes visible when viewer position goes down */
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high);
   glNormal3f( 0.0, 1.0, 0.0); 
   int color = 0;
   for (int k = 0;  k< 11 ; k++)
   {
    for (int j = 0; j <11; j++)
	{
	 if (color % 2 == 0)	
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
     if (color % 2 ==1)		
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
     glBegin(GL_POLYGON);
	  glVertex3f(-4.0 + k , 0.0, -5.0 + j );
      glVertex3f(-5.0 + k , 0.0,-5.0 + j );
      glVertex3f( -5.0 + k , 0.0,-4.0 + j );
	  glVertex3f( -4.0 + k , 0.0, -4.0 + j );
	 glEnd();
     color ++;

	}
   }
/*

   glBegin(GL_POLYGON);
      glVertex3f(-3.0, 0.0,-3.0);
      glVertex3f(-3.0, 0.0, 3.0);
      glVertex3f( 3.0, 0.0, 3.0);
      glVertex3f( 3.0, 0.0,-3.0);
   glEnd();
*/
   /* specify both FRONT AND BACK material properties for faces
    * of cube, since BACK is visible when top opens! */
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
   glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
   glMaterialfv(GL_FRONT, GL_SPECULAR, medium);
   glMaterialfv(GL_BACK, GL_SPECULAR, medium);
   glMaterialfv(GL_FRONT, GL_SHININESS, high);
   glMaterialfv(GL_BACK, GL_SHININESS, medium);
   float fl = 0.1;
   glPushMatrix();
     glTranslatef(-2.1,0,0);
	 glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
   glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
     drawB();
   glPopMatrix();
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
   glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
   glPushMatrix();
      glTranslatef(0.0,0.1,0.0);
      drawC();
   glPopMatrix();
   glPushMatrix();
     glTranslatef(2.1,0,0);	 
	 glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
     glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
     drawD();
   glPopMatrix();
   glFlush();
   glutSwapBuffers();

}
 



/* exit program with "esc" key 
 * light source position controlled by "a", "A", "b", "B", "c", "C"
 * viewer position controlled by "x", "X", "y", "Y", "z", "Z"
 * "o" and "O" opens/closes the top
 * "w" to toggle between filled and wire-frame rendering */
void keyboard(unsigned char key, int x, int y)
{
   static int filled=1;

   switch (key) {
      case 27:
         exit(0);
         break; 

      /* open and close the top */
      case 'o':
         if (step < 90) step = step + 4;
		 //step = step +2;
         glutPostRedisplay();
         break;
      case 'O':
         if (step > -45) step = step - 4;
		 //step = step -2;
         glutPostRedisplay();
         break;

      /* "w" for switching between GL_FILL and GL_LINE */
      case 'w':
         if (filled) {
           filled = 0;
           glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         }
         else {
           filled = 1;
           glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         }; 
         glutPostRedisplay();
         break;

      /* control lpos */
      case 'a':                
         lpos[0] = lpos[0] + 0.2;
         glutPostRedisplay();
         break;
      case 'A':                 
         lpos[0] = lpos[0] - 0.2;
         glutPostRedisplay();
         break;
      case 'b':                
         lpos[1] = lpos[1] + 0.2;
         glutPostRedisplay();
         break;
      case 'B':                 
         lpos[1] = lpos[1] - 0.2;
         glutPostRedisplay();
         break;
      case 'c':                
         lpos[2] = lpos[2] + 0.2;
         glutPostRedisplay();
         break;
      case 'C':                 
         lpos[2] = lpos[2] - 0.2;
         glutPostRedisplay();
         break;
       // Preset Camera Positions
	  //***********************************************
	  case '1':                
         viewer[0] = -5;
		 viewer[1] = 3;
		 viewer[2] = 7;
		  //cpos[0] = cpos[0] + 0.2;
         glutPostRedisplay();
         break;
      case '2':       
          viewer[0] = 1;
		  viewer[1] = 1.5;
		  viewer[2] = 10;
         //cpos[0] = cpos[0] - 0.2;
         glutPostRedisplay();
         break;
      case '3':        
		  viewer[0] = 10;
		  viewer[1] = 3;
		  viewer[2] = 7;
         //cpos[1] = cpos[1] + 0.2;
         glutPostRedisplay();
         break;
      case '4':        
		  viewer[0] = -10;
		  viewer[1] = 1;
		  viewer[2] = 1.5;
         //cpos[1] = cpos[1] - 0.2;
         glutPostRedisplay();
         break;
      case '5':        
		  viewer[0] = 1;
		  viewer[1] = 10;
		  viewer[2] = 10;
         //cpos[2] = cpos[2] + 0.2;
         glutPostRedisplay();
         break;
      case '6':        
		  viewer[0] = 12;
		  viewer[1] = 3;
		  viewer[2] = -10;
         //cpos[2] = cpos[2] - 0.2;
         glutPostRedisplay();
         break;
       //****************************************************
      /* control viewer position */
      case 'x':                
         viewer[0] = viewer[0] + 0.2;
         glutPostRedisplay();
         break;
      case 'X':                 
         viewer[0] = viewer[0] - 0.2;
         glutPostRedisplay();
         break;
      case 'y':                
         viewer[1] = viewer[1] + 0.2;
         glutPostRedisplay();
         break;
      case 'Y':                 
         viewer[1] = viewer[1] - 0.2;
         glutPostRedisplay();
         break;
      case 'z':                
         viewer[2] = viewer[2] + 0.2;
         glutPostRedisplay();
         break;
      case 'Z':                 
         viewer[2] = viewer[2] - 0.2;
         glutPostRedisplay();
         break;

      default:
         break;
   }
}

   
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 800); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}



