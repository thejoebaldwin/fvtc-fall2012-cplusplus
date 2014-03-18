#include <iostream>
#include <glut.h>


#define PI 3.14159265

using namespace std;



static GLfloat time =0.0;
static float part = 60;
static int subdiv = 60;
static float len = 7.5;
bool transp = false;
static int stepsize = 60;
static GLfloat step[]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
static GLfloat vert[] ={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

struct vek{
     GLfloat x;
	 GLfloat y;
	 GLfloat z;
	 };

GLuint theVase;
GLuint theTable;
static bool bubb = false;
static bool table = true;
static int light = 0;
/* position of light source */
static GLfloat light_one[] = {4,    0.0, 0.0, 1.0};
static GLfloat light_two[] = {0.5,    7.5, 3.0, 1.0};
static GLfloat light_three[]={-3.5, 1.5,    2.0, 1.0};

/* position of viewer */
static GLdouble viewer[] = {2.0, 11.0, 10.0}; 

/* vectors for translucent properties */
static GLfloat red_transparent[] = {1.0, 0.0, 0.0, 0.7};
static GLfloat yellow_transparent[] = {1.0, 1.0, 0.0, 0.7};

/* vectors to specify material properties */ 
static GLfloat high[]  = {100.0}; /* for shininess */
static GLfloat medium[]  = {50.0}; /* for shininess */
static GLfloat none[]    = {0.0, 0.0, 0.0, 1.0};
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

//*********FUNCTION SET_ARRAYS*********************
//Initializes static arrays with Data for "Swirling Spheres"
void set_arrays()
{
  for (float ss = 0; ss < stepsize ; ss++)
  {
  step[(int) ss] = rand() * (360/stepsize);
  }
  for (float st = 0.0; st < stepsize; st++)
  {
  vert[(int) st] = ((st) * ((2.20 + len)/stepsize)) - 2.20;
  }
}
//************FUNCTION WRITEMESSAGE*****************
void writemessage()
{
   printf("\n\
   program2.cpp by Joe Baldwin\n\
   uses double buffering for smooth animation\n\n\
   Extra: Vase is made of 60 rings, each ring has 60 faces.\n\
   Extra: Green and Blue Bullseye 'floor'.\n\
   Extra: Display List used for Vase\n\
   Extra: Display List used for Vase 'floor'.\n\
   Extra: Vase Can be made Transparent.\n\
   Extra: Animated spheres swirl up through the inside of the vase\n\
   a, A, --------------------- Turn Off/On all light sources\n\
   x, X, y, Y, z, Z ---------- change viewer position\n\
   1, 2, 3, 4, 5, 6 ---------- Extra: change to preset viewer positions\n\
   7,8,9 --------------------- Switch between Three Light Sources\n\
   T ------------------------- Extra: Toggle Table on/off \n\
   t ------------------------- Extra: Toggle between Opaque and Transparent\n\
   m, M----------------------- Extra: Turn Off/On 'Swirling Bubbles' Animation\n\
   w ------------------------- toggle between fill and wire-frame\n\
   ESC ----------------------- exit\n\
   \n");
}
//***********FUNCTION RESHAPE***********************
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 2.0, 22.0);
   glMatrixMode(GL_MODELVIEW);
}
//************FUNCTION NORM**************************
//Given 3 points, Function returns a unit normal vector
float *  norm(float * result, float x1,float y1, float z1, float x2, float y2, float z2,
			   float x3, float y3, float z3)
{
 float a[3];
 float b[3];
 a[0] = x1 - x2;
 a[1] = y1 - y2;
 a[2] = z1 - z2;
 b[0] = x1 - x3;
 b[1] = y1 - y3;
 b[2] = z1 - z3;
 result[0] = (a[1] * b[2]) - (a[2]* b[1]);
 result[1] = (a[2] * b[0]) - (a[0] * b[2]);
 result[2] = (a[0] * b[1]) - (a[1] * b[0]);
 float magn = sqrt((result[0] * result[0]) + (result[1] * result[1]) + (result[2]*result[2]));
 result[0] = (result[0] / magn);
 result[1] = (result[1] / magn);
 result[2] = (result[2] / magn);
 return result;
}
//**************FUNCTION ABSOLUTE*********************
//Returns absolute value of f
float absolute (float f)
{
if (f <0.0) f = f * -1.0;
return f;
}
//*************FUNCTION RETURN_RAD*******************
//Function returns corresponding radius of Vase given y value
float return_rad(float y)
{
 float rad;
 float x = len;
 float w = x/subdiv;
 float count = 0.0 - ((4.5 * (w/x))* y);
 float angle1 = ((float)((y/x) * 180)/180) * (2 * PI);
 if ( y > 2 * (x/3.0)) 
 {
   rad =   absolute(cos(angle1)  + 1.5 + count) ;
 }
 else
 {
   rad = absolute(cos(angle1)  + 1.5) ;
 }
 return rad;
}
//***********FUNCTION DRAW_GLOBE*********************
//Draws sphere and translates to given coordinates
void draw_globe(float x, float y, float z)
{
    glPushMatrix();
	    glTranslatef(x, y, z);
	    glutSolidSphere(0.10, 6, 6);
	glPopMatrix();
}
//***********FUNCTION DRAW_SPHERES******************
//Draws sphere at given "height" and angle at step[index]
void draw_spheres(float y, int index)
{
 float rad = return_rad(y) - 0.5 ;
 float angle; 
 angle = ((float) step[index]/360) * (2*PI);
 vek v;
 v.y = y + 1.6;
 v.x = cos(angle) * rad;
 v.z = sin(angle) * rad;
 draw_globe(v.x, v.y, v.z);
}
//************FUNCTION RING***************************
//Draws a "ring" from origin to origin + width. Lower radius is bottom_radius, upper radius is top_radius
//partitions determines the number of faces, inside determines direction vertices are drawn (front/back), change 
// determines if colors blend from yellow to red.
void ring(float bottom_radius,float top_radius, float width, float origin, float partitions, bool inside, bool change)
{ 
   GLfloat angle1;
   GLfloat angle2;
   GLfloat normal_angle;
   GLfloat segment = 360 / (GLfloat) partitions;
   for (int i = 0; i<partitions; i++)
   {
	static GLfloat col[]  = {(float) i, (float) i, 0.0, (float) i}; 
	angle1 = ((segment * i) / 180) * PI;
	angle2 = ((segment * (i+1)) /180) * PI;
	normal_angle =( (angle1 + angle2) / 2.0);
	GLfloat normz[3];
	norm(normz, top_radius * cos(angle2),    origin + (width / 2), top_radius * sin(angle2),
		        bottom_radius * cos(angle2), origin - (width / 2), bottom_radius * sin(angle2),
	            bottom_radius * cos(angle1),    origin - (width / 2), bottom_radius * sin(angle1));
	glNormal3f(normz[0], normz[1], normz[2]);
	if (!inside & change)
	{
     glBegin(GL_POLYGON);
       glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red_transparent);
       glVertex3f(top_radius * cos(angle1),    origin + width,   top_radius * sin(angle1));
       glVertex3f(top_radius * cos(angle2),    origin + width ,  top_radius * sin(angle2));
       glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow_transparent);
       glVertex3f(bottom_radius * cos(angle2), origin,          bottom_radius * sin(angle2));
	   glVertex3f(bottom_radius * cos(angle1), origin,           bottom_radius * sin(angle1));
	 glEnd();
	}
	if (inside && !change)
	{
    glBegin(GL_POLYGON);
      glVertex3f(top_radius * cos(angle2),    origin + width ,  top_radius * sin(angle2));
	  glVertex3f(bottom_radius * cos(angle1), origin,           bottom_radius * sin(angle1));
	  glVertex3f(top_radius * cos(angle1),    origin + width,   top_radius * sin(angle1));
    glEnd();
	
	glBegin(GL_POLYGON);
      glVertex3f(top_radius * cos(angle2),    origin + width, top_radius * sin(angle2));
      glVertex3f(bottom_radius * cos(angle2), origin,          bottom_radius * sin(angle2));
	  glVertex3f(bottom_radius * cos(angle1), origin,         bottom_radius * sin(angle1));
    glEnd();
	}
	if (!inside && !change)
	{
	glNormal3f(-normz[0], -normz[1], -normz[2]);
	glBegin(GL_POLYGON);
     glVertex3f(bottom_radius * cos(angle1), origin,           bottom_radius * sin(angle1));  
	 glVertex3f(top_radius * cos(angle2),    origin + width ,  top_radius * sin(angle2));
	 glVertex3f(top_radius * cos(angle1),    origin + width,   top_radius * sin(angle1));
    glEnd();
	glBegin(GL_POLYGON);
     glVertex3f(bottom_radius * cos(angle2), origin,          bottom_radius * sin(angle2));  
	 glVertex3f(top_radius * cos(angle2),    origin + width, top_radius * sin(angle2));
     glVertex3f(bottom_radius * cos(angle1), origin,         bottom_radius * sin(angle1));
    glEnd();
	}
   }
}
//***********FUNCTION ALL_RINGS****************************
//Draws all the rings that make up the Vase
void all_rings()
{
	GLfloat w, x;
	x = len;
	w = x / subdiv;
	GLfloat angle1 = 0.1;
	GLfloat angle2 = 0.1;
    GLfloat count = 0.0;
    GLfloat count2 = 0.0;
	bool bottom = false;
	bool top = false;
    //Draw inside of the vase
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red_transparent);
	for (GLfloat j = -2.20; j < ((x - (x/3))) ; j = j + w)
    {
	 angle1 = ((GLfloat)((j/x) * 180)/180) * (2 * PI);
     angle2 = ((GLfloat)(((j+w)/x) * 180)/180) * (2 * PI);
     //Start at 0.20 + bottom of the vase
	 if ( j > -2.00)
	 {
      //Draw bottom of the inside of the vase once
      if (!top)
	  {
       ring(absolute(cos(angle1)  + 1.5 + count) - 0.25, 0.0, 0.0 , j+ w , part, true, false);
	   top = true;
	  }
	 if ( j > 2 * (x/3.0)) 
	 {
      ring(absolute(cos(angle1)  + 1.5 + count) - 0.25, absolute(cos(angle2) + 1.5 + (count-(4.5 * (w/x)))) - 0.25, w , j+ w , part, false, false);
	  count = count - (4.5 * (w/x));
	 }
	 else ring(absolute(cos(angle1)  + 1.5) - 0.25, absolute(cos(angle2) + 1.5) - 0.25, w , j+ w , part, false, false);
	 }
	}
    count = 0.0;
    count2 = 0.0;
	//Draw outside of the vase
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow_transparent);
	GLfloat i = 0.0;
    for (GLfloat i = -2.20; i < (x - (x/3)) ; i = i + w)
    {
	 angle1 = ((GLfloat)((i/x) * 180)/180) * (2 * PI);
     angle2 = ((GLfloat)(((i+w)/x) * 180)/180) * (2 * PI);
     //Draw bottom of the Vase once
	 if (!bottom)
	 {
       ring(absolute(cos(angle1)  + 1.5 + count),0.0,  0.0 , i + w , part, false, false);
	   bottom = true;
	 }
	 if ( i > 2 * (x/3.0)) 
	 {
      ring(absolute(cos(angle1)  + 1.5 + count), absolute(cos(angle2) + 1.5 + (count-(4.5 * (w/x)))), w , i+ w , part, true, false);
      
	  count = count - (4.5 * (w/x));
	 }
	 else  ring(absolute(cos(angle1)  + 1.5), absolute(cos(angle2) + 1.5), w , i+ w , part, true, false);
	}
    count = count + (4.5 * (w/x));
    ring(absolute(cos(angle2) + 1.5 + (count-(4.5 * (w/x)))) , absolute(cos(angle2) + 1.5 + (count-(4.5 * (w/x)))) - 0.25 , 0.0 , i+ w , part, false, true);
}
//*************FUNCTION BUBBLES****************************
//Idle function for "swirling spheres" animation
void bubbles(void)
{
 int c = 0;
 for (c = 0; c < stepsize; c++)
 {
  step[c] = step[c] + (20 * (1/return_rad(vert[c])));
  if (step[c] > 360)
	 step[c] = step[c]  - 360.0;
 }
 glutPostRedisplay();
}
//***************FUNCTION INIT*******************************
void init(void) 
{
   writemessage(); 
   set_arrays();
   //Display List for the Vase
   theVase = glGenLists(1);
   glNewList(theVase, GL_COMPILE);
     glPushMatrix();
       glTranslatef(0.0,1.6,0.0);
       all_rings();
     glPopMatrix();
   glEndList();
   //Display List for the Table
   theTable = glGenLists(1);
   glNewList(theTable, GL_COMPILE);
      int color = 0;
	  float k = 0.001;
      for (k = 0.001; k < 5; k = k + 0.5)
	  {
       if (color % 2 == 0)	
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
       else		
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
       ring (k, k + 0.5, 0.0, -0.5, part, false, false);
       color ++;
	  }
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
      ring (k, k, 0.5, -1.0, part, false, false);
      ring (k, 0.0, 0.5, -1.0, part, true, false);
   glEndList();
   //"Background" color = white
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      /* initially GL_FILL mode, later GL_LINE to show wireframe */
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
      /* enable two-sided lighting to properly show interior of cube */
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   //Set GL_LIGHT1 and GL_LIGHT2 initial properties, because
   //they do not have the same initial properties as GL_LIGHT0 
   //I Learned how to initialize multiple light sources at :
   //  http://www.parallab.uib.no/SGI_bookshelves/SGI_Developer/books/OpenGL_PG/sgi_html/ch06.html#id27508
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
   
   glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
   glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
   glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
   glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
   glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
   glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
   //Enable 3 light sources
   glEnable(GL_LIGHT2);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT0);
}
//******FUNCTION DISPLAY**************************
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
     glLightfv(GL_LIGHT1, GL_POSITION, light_two);
     glLightfv(GL_LIGHT2, GL_POSITION, light_three);
     glLightfv(GL_LIGHT0, GL_POSITION, light_one);
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    /* draw sphere to show light source */
   if (light ==1 || light==0) 
     glMaterialfv(GL_FRONT, GL_EMISSION, white); 
   else
     glMaterialfv(GL_FRONT, GL_EMISSION, none);
   glPushMatrix();
     glTranslatef(light_one[0],light_one[1],light_one[2]);
     glutSolidSphere(0.1, 10, 8);
   glPopMatrix();
   if (light ==2 || light == 0) 
     glMaterialfv(GL_FRONT, GL_EMISSION, white); 
   else
     glMaterialfv(GL_FRONT, GL_EMISSION, none);
   glPushMatrix();
     glTranslatef(light_two[0],light_two[1],light_two[2]);
     glutSolidSphere(0.1, 10, 8);
   glPopMatrix();
   if (light ==3 || light ==0) 
     glMaterialfv(GL_FRONT, GL_EMISSION, white); 
   else
     glMaterialfv(GL_FRONT, GL_EMISSION, none);
   glPushMatrix();
     glTranslatef(light_three[0],light_three[1],light_three[2]);
     glutSolidSphere(0.1, 10, 8);
   glPopMatrix();
   /* remaining objects do not emit light */
   glMaterialfv(GL_FRONT, GL_EMISSION, none);
   /* note: need to set BACK material properties of the table since
    * BACK becomes visible when viewer position goes down */
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high);
   glNormal3f( 0.0, 1.0, 0.0); 
   //Display list for table
   if (table)
	   glCallList(theTable);
   /* specify both FRONT AND BACK material properties for faces
    * of cube, since INSIDE is visible when top opens! */
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
   glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, medium);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high);
   if (bubb)
	{
    for (int g = 0; g <stepsize; g++)
    {
	   if (g % 3 ==0)
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
       else if (g % 3 ==1)
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
	   else
	       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
    draw_spheres(vert[g], g);
    vert[g] = vert[g] + 0.025;
	 if (vert[g] > (len) )  vert[g] = -2.20  + 0.4 + (vert[g] - len) ;
	}
   }
   //set transparency
   if (transp)
	{
    glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glCallList(theVase);
    glDisable(GL_BLEND);
	}
	else
	{
     glCallList(theVase);
	}
   glFlush();
   glutSwapBuffers();
}
//*****************FUNCTION KEYBOARD************************ 
/* exit program with "esc" key 
 * light source position controlled by "a", "A", "b", "B", "c", "C"
 * viewer position controlled by "x", "X", "y", "Y", "z", "Z"
 * preset viewer position 1, 2, 3, 4, 5, 6
 * switch all lights on/off a/A
 * toggle transparency t
 * toggle Table T
 * start/stop swirling spheres animation M,m */
void keyboard(unsigned char key, int x, int y)
{
   static int filled=1;
   switch (key) {
      case 27:
         exit(0);
         break; 
      /* turn off/on transp */
         case 't':
         if (!transp)
			transp = true;
		 else 
			 transp = false;
         glutPostRedisplay();
         break;
      /* turn off/on table */
         case 'T':
         if (!table)
			table = true;
		 else 
			 table = false;
         glutPostRedisplay();
         break;
      /* start and stop bubble animatio */
        case 'M':
		 bubb = false;
         glutIdleFunc(NULL);
         glutPostRedisplay();
         break;  
	    case 'm':
  	     bubb = true;
         glutIdleFunc(bubbles);
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
      /* Turn ALL lights on/off */
      case 'a':                
         light = 0;
		 glEnable(GL_LIGHT2);
         glEnable(GL_LIGHT0);
         glEnable(GL_LIGHT1);
         glutPostRedisplay();
         break;
      case 'A':                 
         light = 4;
		 glDisable(GL_LIGHT2);
         glDisable(GL_LIGHT0);
         glDisable(GL_LIGHT1);
         glutPostRedisplay();
         break;
    
 	  // Preset Camera Positions 1-6
	  //***********************************************
	  case '1':                
         viewer[0] = 0.1;
		 viewer[1] = 10.0;
		 viewer[2] = 0;
	     glutPostRedisplay();
         break;
      case '2':       
         viewer[0] = 1;
		 viewer[1] = 1.5;
		 viewer[2] = -3.0;
         glutPostRedisplay();
         break;
      case '3':        
		 viewer[0] = 2;
		 viewer[1] = 11;
		 viewer[2] = 10;
         glutPostRedisplay();
         break;
      case '4':    
         viewer[0] = -10;
		 viewer[1] = 1;
		 viewer[2] = 1.5;
         glutPostRedisplay();
         break;
      case '5':        
		 viewer[0] = 2;
		 viewer[1] = 12;
		 viewer[2] = -4;
         glutPostRedisplay();
         break;
      case '6':        
		 viewer[0] = 12;
		 viewer[1] = 3;
		 viewer[2] = -10;
         glutPostRedisplay();
         break;
 	  // Switch Between three lights
	  case '7':
         light = 1;
         glEnable(GL_LIGHT0);
         glDisable(GL_LIGHT1);
         glDisable(GL_LIGHT2);
         glutPostRedisplay();
		 break;
      case '8':
	     light = 2;
         glEnable(GL_LIGHT1);
         glDisable(GL_LIGHT0);
         glDisable(GL_LIGHT2);
         glutPostRedisplay();
		 break;
      case '9':
         light = 3;
         glEnable(GL_LIGHT2);
         glDisable(GL_LIGHT0);
         glDisable(GL_LIGHT1);
         glutPostRedisplay();
		 break;
       //****************************************************
      /* control viewer position */
      case 'x':                
         viewer[0] = viewer[0] + 0.4;
         glutPostRedisplay();
         break;
      case 'X':                 
         viewer[0] = viewer[0] - 0.4;
         glutPostRedisplay();
         break;
      case 'y':                
         viewer[1] = viewer[1] + 0.4;
         glutPostRedisplay();
         break;
      case 'Y':                 
         viewer[1] = viewer[1] - 0.4;
         glutPostRedisplay();
         break;
      case 'z':                
         viewer[2] = viewer[2] + 0.4;
         glutPostRedisplay();
         break;
      case 'Z':                 
         viewer[2] = viewer[2] - 0.4;
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



