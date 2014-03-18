
#include <iostream>
#include <glut.h>

#define PI 3.14159265
#define BUFSIZE 512

using namespace std;


bool smoothNormals = true;
bool  * beenHit;
bool  * beenHit2;
bool  * beenHit3;
int ww, hh;

GLuint theArena, theSun;
GLuint texture_id[6];

GLfloat sphereJoints = 5.0;
GLfloat sphereBody = 10.0;

static int object_row = 0;
static int object_col = 0;

static GLfloat bugPos2[] = {0.0, 2.0, 0.0};

const int table = 10;
GLfloat lavaPts[table][table][3];

int unit = 12.0;
GLfloat lavaChange[table][table];
GLUquadricObj *sphereObj;
int time = 0;

float angleChange1 = 1;
float angleChange2 = 1;

/* position of light source */
static GLfloat lpos[] = {1.95, 3.0, 1.95};
/* position of viewer */
static GLdouble viewer[] = {-10.0, 10.0, 15.0}; 


/* vectors to specify material properties */ 
static GLfloat extreme[] = {200.0};
static GLfloat high[]  = {100.0}; /* for shininess */
static GLfloat low[]  = {25.0}; /* for shininess */
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
static GLfloat black[]= {0.0, 0.0, 0.0, 0.0}; 
/* vectors for translucent properties */
static GLfloat red_transparent[] = {1.0, 0.0, 0.0, 0.5};
static GLfloat yellow_transparent[] = {1.0, 1.0, 0.0, 0.7};
static GLfloat blue_transparent[] = {0.0, 0.0, 1.0, 0.7};
static GLfloat green_transparent[] = {0.0, 1.0, 0.0, 0.7};
static GLfloat black_transparent[] = {0.0, 0.0, 0.0, 0.7};


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

//**************FUNCTION ABSOLUTE***************************************
//returns absolute value of number
float absolute(float f)
{
 if (f < 0.0) f = f * -1.0;
 return f;
}

//*********FUNCTION TOWARDS******************************
//Takes pointer to a array of 3, moves that array 1 in each axis towards origin
void towards(GLfloat * mp)
{
 if (mp[0] < 0.0) mp[0] = mp[0] + 0.1;
  else
	  if (mp[0] > 0.0) mp[0] = mp[0] - 0.1;
 if (mp[2] < 0.0) mp[2] = mp[2] + 0.1;
  else
	  if (mp[2] > 0.0) mp[2] = mp[2] - 0.1;
}
//********FUNCTION DIST**********************************
//returns distance from origin
float dist(float x, float z)
{
 return sqrt((x*x) + (z*z));
}

//********VECTOR DATA STRUCTURE*********************
//Encapsulates a point
struct vek{
     GLfloat x;
	 GLfloat y;
	 GLfloat z;
	 };

//***************FUNCTION NORMALIZE************************
//Returns a unit vector of given vector
vek normalize(vek a)
{
 float magn = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
 a.x = a.x / magn;
 a.y = a.y / magn;
 a.z = a.z / magn;
 return a;
}
//************CLASS PLANE****************
//Plane class allows for easier drawing of polygons
class plane{
public:
     vek a;
	 vek b;
	 vek c;
	 vek d;
	 vek normal;
	 void makeNorm();
	 vek aNorm;
	 vek bNorm;
	 vek cNorm;
	 vek dNorm;
     };

//******************CLASS FUNCTION PLANE::MAKENORM***********************
//Produces normal vectors for plane class
void plane::makeNorm()
{
float temp[3];
norm(temp, a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);\
normal.x = temp[0];
normal.y = temp[1];
normal.z = temp[2];
aNorm = normal;
bNorm = normal;
cNorm = normal;
dNorm = normal;
}

//****************CLASS THING*************************************
//Class thing allows for creation of different shaped, but allows all to be drawn
//  using the same methods. Allows for easier manipulation and creation of objects later.
class thing{
public:
    int columns;
	int rows;
    int row_index;
	int col_index;
	vek pos;
	float xAngle;
	float yAngle;
    float zAngle;
	bool x_axis, y_axis, z_axis;
	plane obj[60][60];
	void init();
	void smooth_thing();
    void draw_smooth(plane, bool);
	void draw_thing();
    void half_ring(float,float , float , float , float , bool);
	void close(float,float , float , float , float , bool);
    void ring(float,float , float , float , float , bool );
	void rod(float, float);
	void foot();
	void half_rod(float, float, bool);
    void rect(float, float, float);
	bool is_rect;
	void move(float, float, float);
	void rot(float, bool, bool, bool);
	bool is_rod;
	bool is_half_rod;
	bool is_piston;
	bool is_rocket;
	bool is_foot;
	int ring_parts;
    GLfloat color[4];
	void setColor(GLfloat *);
    void tube(float, float , float ); 
};
//*********CLASS FUNCTION THING::INIT************************
//Initialize Class Data members
void thing::init()
{
 pos.x = 0.0;
 pos.y = 0.0;
 pos.z = 0.0;
 xAngle = 0.0;
 yAngle = 0.0;
 zAngle = 0.0;
 x_axis = false;
 y_axis = false;
 z_axis = false;
 color[0] = red[0];
 color[1] = red[1];
 color[2] = red[2];
 color[3] = red[3];
 columns = 0;
 rows = 0;
 row_index = 0;
 col_index = 0;
 is_rod = false;
 is_half_rod = false;
 is_rocket = false;
 is_foot = false;
 ring_parts = 10;
}
//**********CLASS FUNCTION THING::SMOOTH_THING*******************
//"Blends" normals together across object
void thing::smooth_thing()
{
 
 {
	//smooth vertically
 if (!is_half_rod && !is_rod && !is_foot)
 for (int i = 0; i < columns; i ++)
 {
 for (int j = 0; j < rows -1; j ++)
   {
    obj[i][j].aNorm = obj[i+1][j].dNorm;
    obj[i][j].bNorm = obj[i+1][j].cNorm;
   }
 }
  if (is_rod && !is_half_rod)
  {
   for (int k = 0; k < rows; k++)
   for (int l = 0; l < columns; l ++)
   { 
   	if (l == columns - 1)
	{
	 obj[k][l].bNorm = obj[k][0].aNorm;
     obj[k][l].cNorm = obj[k][0].dNorm;
	}
	else
	{
	 obj[k][l].bNorm = obj[k][l+1].aNorm;
     obj[k][l].cNorm = obj[k][l+1].dNorm;
	}
   }
  }
  if (is_foot)
  {
   for (int k = 0; k < rows; k++)
   for (int l = 0; l < columns; l ++)
   { 
   	 if (k != 0 || k !=2)
	 {
	 obj[k][l].bNorm = obj[k][l+1].aNorm;
     obj[k][l].cNorm = obj[k][l+1].dNorm;
	 }
   }

   for ( int y = 0; y < columns; y++)
	   obj[15][y].makeNorm();
  
 }

  if (is_half_rod)
  {
   for (int o = 0; o <rows; o++)
   	  for (int p = 0; p < ((ring_parts/2) - 1)  ; p++)
   {
    
	obj[o][p].bNorm = obj[o][p + 1].aNorm;
    obj[o][p].cNorm = obj[o][p + 1].dNorm;
   }
  }
 }
}

//**********CLASS FUNCTION THING::DRAW_SMOOTH***************************
//Draws object with "Blended" normals 
void thing::draw_smooth(plane p, bool face)
{
  if (smoothNormals)
  {  
	if (!face)
	{
	glBegin(GL_POLYGON);
        glNormal3f(p.aNorm.x, p.aNorm.y, p.aNorm.z);
	  glVertex3f(p.a.x, p.a.y, p.a.z);
	    glNormal3f(p.bNorm.x, p.bNorm.y, p.bNorm.z);
	  glVertex3f(p.b.x, p.b.y, p.b.z);
        glNormal3f(p.cNorm.x, p.cNorm.y, p.cNorm.z);
	  glVertex3f(p.c.x, p.c.y, p.c.z);
       glNormal3f(p.dNorm.x, p.dNorm.y, p.dNorm.z);
	  glVertex3f(p.d.x, p.d.y, p.d.z);
    glEnd();
    }
	else
	{
    glBegin(GL_POLYGON);
      glNormal3f(p.aNorm.x, p.aNorm.y, p.aNorm.z);
	  glVertex3f(p.a.x, p.a.y, p.a.z);
	  glNormal3f(p.bNorm.x, p.bNorm.y, p.bNorm.z);
	  glVertex3f(p.b.x, p.b.y, p.b.z);
      glNormal3f(p.cNorm.x, p.cNorm.y, p.cNorm.z);
	  glVertex3f(p.c.x, p.c.y, p.c.z);
      glNormal3f(p.dNorm.x, p.dNorm.y, p.dNorm.z);
	  glVertex3f(p.d.x, p.d.y, p.d.z);
    glEnd();
    }
  }
  else 
  { 
   if (!face)
	{
	glBegin(GL_POLYGON);
      glNormal3f(p.normal.x, p.normal.y, p.normal.z);
	  glVertex3f(p.a.x, p.a.y, p.a.z);
	  glVertex3f(p.b.x, p.b.y, p.b.z);
      glVertex3f(p.c.x, p.c.y, p.c.z);
      glVertex3f(p.d.x, p.d.y, p.d.z);
    glEnd();
    }
	else
	{
    glBegin(GL_POLYGON);
      glNormal3f(p.normal.x, p.normal.y, p.normal.z);
	  glVertex3f(p.a.x, p.a.y, p.a.z);
	  glVertex3f(p.b.x, p.b.y, p.b.z);
      glVertex3f(p.c.x, p.c.y, p.c.z);
      glVertex3f(p.d.x, p.d.y, p.d.z);
    glEnd();
    }
  }
}
//************CLASS FUNCTION THING::DRAW_THING****************
//Draw object with specified translations/rotations
void thing::draw_thing()
{
 glPushMatrix();
 if (x_axis) glRotatef(xAngle, 1.0, 0.0, 0.0);
 if (y_axis) glRotatef(yAngle, 0.0, 1.0, 0.0);
 if (z_axis) glRotatef(zAngle, 0.0, 0.0, 1.0);
  
 glPushMatrix();
 glTranslatef(pos.x, pos.y, pos.z);
 
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
 if (!is_rect)
 {
 for (int i = 0; i < rows; i ++)
 { 
	 for (int j = 0; j < columns; j ++)
	  {
		if (i > rows - 10 && is_rocket)
             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
       draw_smooth(obj[i][j], true);
	  }
 }
 }
 else
 { /////////////////////
  for (int i = 0; i < 6; i ++)
  {
    
   glNormal3f(-obj[0][i].normal.x, -obj[0][i].normal.y, -obj[0][i].normal.z);
   glBegin(GL_POLYGON);
      glVertex3f(obj[0][i].b.x, obj[0][i].b.y, obj[0][i].b.z);
      glVertex3f(obj[0][i].a.x, obj[0][i].a.y, obj[0][i].a.z);
      glVertex3f(obj[0][i].d.x, obj[0][i].d.y, obj[0][i].d.z);
   glEnd();

   glBegin(GL_POLYGON);
    glVertex3f(obj[0][i].b.x, obj[0][i].b.y, obj[0][i].b.z);
    glVertex3f(obj[0][i].d.x, obj[0][i].d.y, obj[0][i].d.z);
    glVertex3f(obj[0][i].c.x, obj[0][i].c.y, obj[0][i].c.z);
   glEnd();
  }
 }
 glPopMatrix();
 glPopMatrix();
}
//****************CLASS FUNCTION THING::RING***************
//Creates a ring with specified attributes and stored it in object array
void thing::ring(float bottom_radius,float top_radius, float width, float origin, float partitions, bool inside)
{ 
   GLfloat angle1;
   GLfloat angle2;
   GLfloat segment = 360 / (GLfloat) partitions;
   vek a;
   vek b;
   vek c;
   vek d;
   plane p;
   for (int i = 0; i<partitions; i++)
   {
	angle1 = ((segment * i) / 180) * PI;
	angle2 = ((segment * (i+1)) /180) * PI;
		
	if (!inside)
	{
		//Inside
       a.x = top_radius * cos(angle1); a.y = origin + width; a.z = top_radius * sin(angle1);
	   b.x =top_radius * cos(angle2); b.y = origin + width; b.z = top_radius * sin(angle2);
	   c.x =bottom_radius * cos(angle2); c.y = origin; c.z =  bottom_radius * sin(angle2);
       d.x =bottom_radius * cos(angle1); d.y = origin; d.z = bottom_radius * sin(angle1);
	}
	if (inside)
	{
       //OUTSIDE
	   a.x = top_radius * cos(angle1); a.y = origin + width; a.z = top_radius * sin(angle1);
	   b.x =top_radius * cos(angle2); b.y = origin + width; b.z = top_radius * sin(angle2);
	   c.x =bottom_radius * cos(angle2); c.y = origin; c.z =  bottom_radius * sin(angle2);
       d.x =bottom_radius * cos(angle1); d.y = origin; d.z = bottom_radius * sin(angle1);
	}
	p.a = a;
	p.b = b;
	p.c = c;
	p.d = d;
    p.makeNorm();
    obj[row_index][col_index] = p;
	col_index++;
	columns++;
	if (col_index >= partitions) 
	{
     col_index = 0;
	 row_index++;
	 rows++;
	}
   }
}
//****************CLASS FUNCTION THING::HALF_RING***************
//Creates half of a ring with specified attributes and stored it in object array
void thing::half_ring(float bottom_radius,float top_radius, float width, float origin, float partitions, bool inside)
{ 
   GLfloat angle1;
   GLfloat angle2;
   GLfloat segment = 360 / (GLfloat) partitions;
   vek a;
   vek b;
   vek c;
   vek d;
   plane p;
   for (int i = 0; i<(partitions/2); i++)
   { 
	angle1 = ((segment * i) / 180) * PI;
	angle2 = ((segment * (i+1)) /180) * PI;
	if (!inside)
	{
  	   //Outside
     a.x = top_radius * cos(angle1);   a.y = origin + width; a.z = top_radius * sin(angle1);
     b.x =top_radius * cos(angle2);    b.y = origin + width; b.z = top_radius * sin(angle2);
     c.x =bottom_radius * cos(angle2); c.y = origin;         c.z = bottom_radius * sin(angle2);
     d.x =bottom_radius * cos(angle1); d.y = origin;         d.z = bottom_radius * sin(angle1);
	 p.a = a;
	 p.b = b;
	 p.c = c;
	 p.d = d;
	}
	if (inside)
	{
       //Inside
	 a.x = top_radius * cos(angle1);   a.y = origin + width; a.z = top_radius * sin(angle1);
	 b.x =top_radius * cos(angle2);    b.y = origin + width; b.z = top_radius * sin(angle2);
	 c.x =bottom_radius * cos(angle2); c.y = origin;         c.z = bottom_radius * sin(angle2);
     d.x =bottom_radius * cos(angle1); d.y = origin;         d.z = bottom_radius * sin(angle1);
	 p.a = b;
	 p.b = a;
	 p.c = d;
	 p.d = c;
	}

    p.makeNorm();
    obj[row_index][col_index] = p;
	col_index++;
	columns++;
	if (col_index >= partitions) 
	{
     col_index = 0;
	 row_index++;
	 rows++;
	}
   }
}
//******************CLASS FUNCTION THING::CLOSE*********************
//"Seals up" the half_ring face that is open, given  the same parameters
void thing::close(float bottom_radius,float top_radius, float width, float origin, float partitions, bool inside)
{ 
 GLfloat segment = 360 / (GLfloat) partitions;
 vek a;
 vek b;
 vek c;
 vek d;
 plane p;
 a.x = -top_radius;    a.y = width + origin; a.z = 0.0; 
 b.x = top_radius;     b.y = width + origin; b.z = 0.0;
 c.x = bottom_radius;  c.y = origin;         c.z = 0.0;
 d.x = -bottom_radius; d.y = origin;         d.z = 0.0;
 p.a = b;
 p.b = a;
 p.c = d;
 p.d = c;
 p.makeNorm();
 obj[15][col_index] = p;
 col_index++;
}

//*****************CLASS FUNCTION THING::ROD**************************
//Creates Cylinder with specified attributes
void thing::rod (float length, float radius)
{
 ring(0.001, radius,  0.0,    0.0,    ring_parts, false);
 ring(radius, radius, length, 0.0,    ring_parts, false);
 ring(radius, 0.001, 0.0,    length, ring_parts, false);
 
 rows = 3;
 columns = ring_parts; 
 is_rod = true;
}
//******************CLASS FUNCTION THING::TUBE***********************
//Creates hollow tube with specified attibutes 
void thing::tube(float length, float outRadius, float inRadius)
{
 ring(inRadius, outRadius,  0.0,    0.0,    ring_parts, false);
 ring(outRadius, outRadius, length, 0.0,    ring_parts, false);
 ring(outRadius, inRadius, 0.0,    length, ring_parts, false);
 ring(inRadius, inRadius, length,    0.0, ring_parts, false);
 rows = 4;
 columns = ring_parts; 
 is_rod = true;
}
//****************CLASS FUNCTION THING::FOOT*******************
//Creates Foot object for Bug
void thing::foot()
{
 float angle1, angle2;
 int x = 15;
 float w = 0.05;
 float scaleBy = 0.3;
 bool tip = false;
 float width = 0.25;
 float ink = 0.0;
 float rad = 0.01;
 float start = 0.35;
 float end = 0.65;
 int middle = 0;
 float nose = 20.0;
 angle1 = ((GLfloat)((start) * 180)/180) * (2 * PI);
 half_ring((absolute(cos(angle1)) + rad) * scaleBy , 0.001 * scaleBy , 
	   0.0, ink * width , ring_parts, false); 
 for (float j = start; j <end; j = j + w)
 {
   angle1 = ((GLfloat)((j) * 180)/180) * (2 * PI);
   angle2 = ((GLfloat)(((j+w)) * 180)/180) * (2 * PI);
   {
   half_ring((absolute(cos(angle1)) + rad) * scaleBy , (absolute(cos(angle2)) + rad) * scaleBy , width, ink * width , ring_parts, false); 
   ink = ink + 1.0;
   }
 }
 angle1 = ((GLfloat)((end) * 180)/180) * (2 * PI);
 half_ring((absolute(cos(angle1)) + rad) * scaleBy , 0.001 * scaleBy , 
	   0.0, ink * width , ring_parts, false); 
 ink = 0.0;
 col_index = 0;
 for (float b = start; b <end; b = b + w)
 {
  angle1 = ((GLfloat)((b) * 180)/180) * (2 * PI);
  angle2 = ((GLfloat)(((b+w)) * 180)/180) * (2 * PI);
   {
   close((absolute(cos(angle1)) + rad) * scaleBy , (absolute(cos(angle2)) + rad) * scaleBy , width, ink * width , ring_parts, false); 
   ink = ink + 1.0;
   }
 }
 is_foot = true;
 rows = x + 1;
 columns = ring_parts;
}

//****************CLASS FUNCTION THING::HALF_ROD*********************
//Creates half cylinder object with specified attributes
void thing::half_rod (float length, float radius, bool open)
{
  half_ring(0.001, radius,  0.0,    0.0,    ring_parts, false);
  half_ring(radius, 0.001, 0.0,    length, ring_parts, false);
  half_ring(radius, radius, length, 0.0,    ring_parts, false);
  rows = 3;
  if (open)
  {
  plane p;
  vek temp;
  temp.x = radius; 
  temp.y = length;
  temp.z = 0.0;
  p.b = temp;
  temp.x = -radius; 
  temp.y = length;
  temp.z = 0.0;
  p.a = temp;
  temp.x = -radius; 
  temp.y = 0.0;
  temp.z = 0.0;
  p.d = temp;
  temp.x = radius; 
  temp.y = 0.0;
  temp.z = 0.0;
  p.c = temp;
  p.makeNorm();
  rows = 4;
  obj[row_index][col_index] = p;
  row_index++;
  }
  columns = ring_parts;  
  is_half_rod = true;
}

//***********CLASS FUNCTION THING::RECT*********************
//Creates rectangle object with specified atributes
void thing::rect(float w, float h, float l)
{
 is_rect = true;
 plane p;
 vek temp;
 columns = 6;
 rows = 1;
 //---------------------------------------
 temp.x = 0.0; temp.y = h; temp.z = l;
 p.a = temp;
 temp.x = w;   temp.y = h; temp.z = l;
 p.b = temp;
 temp.x = w; temp.y = 0.0; temp.z = l;
 p.c = temp;
 temp.x = 0.0;   temp.y = 0.0; temp.z = l;
 p.d = temp;
 p.makeNorm();
 obj[row_index][col_index] = p;
 col_index ++;
 //------------------------------------------
 p.a = obj[row_index][0].b;
 p.d = obj[row_index][0].c;
 temp.x = w; temp.y = h; temp.z = 0.0;
 p.b = temp;
 temp.x = w; temp.y = 0.0; temp.z = 0.0;
 p.c = temp;
 p.makeNorm();
 obj[row_index][col_index] = p;
 col_index++;
 //------------------------------------------
 p.a = obj[row_index][col_index -1].b;
 p.d = obj[row_index][col_index -1].c;
 temp.x = 0.0; temp.y = h; temp.z = 0.0;
 p.b = temp;
 temp.x = 0.0; temp.y = 0.0; temp.z = 0.0;
 p.c = temp;
 p.makeNorm();
 obj[row_index][col_index] = p;
 col_index++;
 //-------------------------------------------
 p.a = obj[row_index][2].b;
 p.b = obj[row_index][0].a;
 p.c = obj[row_index][0].d;
 p.d = obj[row_index][2].c;
 p.makeNorm();
 obj[row_index][col_index] = p;
 col_index++;
 //------------------------------------------
 p.a = obj[row_index][2].b;
 p.b = obj[row_index][2].a;
 p.c = obj[row_index][0].b;
 p.d = obj[row_index][0].a;
 p.makeNorm();
 obj[row_index][col_index] = p;
 col_index++;
 //---------------------------------------
 p.a = obj[row_index][2].d;
 p.b = obj[row_index][2].c;
 p.c = obj[row_index][0].d;
 p.d = obj[row_index][0].c;
 p.makeNorm();
 obj[row_index][col_index] = p;
 col_index++;
}
//****************CLASS FUNCTION THING::MOVE***************
//Changes position coordinates for object
void thing::move(float x, float y, float z)
{
 pos.x = x;
 pos.y = y;
 pos.z = z;
}
//*****************CLASS FUNCTION THING::ROT*******************
//Changes rotation data members for object
void thing::rot(float ang, bool x, bool y, bool z)
{
 if (x) 
 { 
  xAngle = ang;
  x_axis = x;
 }
 if (y) 
 {
  yAngle = ang;
  y_axis = y;
 }
 if (z)
 {
  zAngle = ang;
  z_axis = z;
 }
}
//***************CLASS FUNCTION THING::SETCOLOR******************
//sets color for object
void thing::setColor(GLfloat * c)
{
 color[0] = c[0];
 color[1] = c[1];
 color[2] = c[2];
 color[3] = c[3];
}

//****************CLASS BUG***********************************
//Encapsulates instances of Thing and GluSphere to make a "Bug",
//    with animations
class Bug
{
public:
 Bug(int);
 ~Bug();
 
 void bugDraw();
 void bugMaster();
 void mouseResponse(int);

private:
 void bugInit();
 void bugBody();
 void bugWings();
 void bugLegs();
 void bugHop();
 void bugSleep();
 void bugWalk();
 void bugAttention();

 int BID;
 float bugAngle;
 float bAngle;
 float kneeAngle;
 float armAngle;
 float armBase; 
 float elbowAngle;
 
 GLfloat sleepAngle;
 GLfloat * aniPos;
 GLUquadricObj *sphereObj;
 GLfloat * duckBug;
 GLfloat * myPos;

 float legBend;
 float finalAng;
 float sleepTime;
 float increment;

 thing leg1;
 thing leg2;
 thing calf1;
 thing calf2;
 thing leftFoot;
 thing rightFoot;
 thing rightArm;
 thing rightForearm;

 bool hopping;
 bool bugStop;
 bool kneeDown;
 bool hopUp;
 bool angleComp;
 bool happyAngry;

};

//************CLASS FUNCTION BUG::BUG*********************
Bug::Bug(int i)
{
 BID = i;
bugInit();
}
//*************CLASS FUNCTION BUG::~BUG*******************
Bug::~Bug()
{
delete [] myPos;
delete [] aniPos;
delete [] duckBug;
}
//************CLASS FUNCTION BUG::BUGINIT()**************
//Initializes Bug data Members
void Bug::bugInit()
{
 increment = 20.0;
 happyAngry = false;
 elbowAngle = 90.0;
 sleepTime = 0.0;
 sleepAngle = 0.0;
 angleComp = false;
 hopUp = false;
 kneeDown = false;
 kneeAngle = 35.0;
 bugStop = false;
 legBend = 1.0;
 hopping = false;
 bugAngle = rand() % 360;
 armAngle = rand() % 360;
 rightArm.init();
 rightArm.rod(0.6, 0.075);
 rightArm.setColor(yellow);
 rightArm.smooth_thing();
 myPos = new GLfloat[3];
 myPos[0] = 0.0;
 myPos[1] = 0.3;
 myPos[2] = 0.0;
 aniPos = new GLfloat[3];
 aniPos[0] = 0.0;
 aniPos[1] = 0.3;
 aniPos[2] = 0.0;
 duckBug = new GLfloat[3];
 duckBug[0] =0.0;
 duckBug[1] = 0.0;
 duckBug[2] = 0.0;
 rightForearm.init();
 rightForearm.rod(0.6, 0.075);
 rightForearm.setColor(yellow);
 rightForearm.smooth_thing();
 armBase = 0.0;
 leftFoot.init();
 leftFoot.ring_parts = 30.0;
 leftFoot.foot();
 leftFoot.setColor(red);
 leftFoot.smooth_thing();
 rightFoot.init();
 rightFoot.ring_parts = 30.0;
 rightFoot.foot();
 rightFoot.setColor(red);
 rightFoot.smooth_thing();
 leg1.init();
 leg1.rod(1.5, 0.1);
 leg1.setColor(yellow);
 leg1.smooth_thing();
 calf1.init();
 calf1.rod(1.5, 0.1);
 calf1.setColor(yellow);
 calf1.smooth_thing();
 calf2.init();
 calf2.rod(1.5, 0.1);
 calf2.setColor(yellow);
 calf2.smooth_thing();
 leg2.init();
 leg2.rod(1.5, 0.1);
 leg2.setColor(yellow);
 leg2.smooth_thing();
 sphereObj = gluNewQuadric();
 gluQuadricTexture(sphereObj, GL_TRUE); 
 gluQuadricOrientation( sphereObj, GLU_OUTSIDE );
}
//************CLASS FUNCTION BUG::BUGDRAW*************************
//Draw Bug
void Bug::bugDraw()
{
 glPushMatrix();
   glTranslatef(myPos[0], myPos[1] , myPos[2]);
   glRotatef(bugAngle, 0.0, 1.0, 0.0);
   glTranslatef(aniPos[0], aniPos[1], aniPos[2]);
   glRotatef(-sleepAngle, 1.0, 0.0, 0.0);
   bugLegs();
 glPopMatrix();
}
//***************CLASS FUNCTION BUG::BUGBODY**********************
//Draws Bug's Body, arms and Head

void Bug::bugBody()
{
   float armRad = ((armAngle)/360) * 2 * PI;
   float rotat = 90.0;
   float rotat2 = -80.0;
  
    if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
   //---------------------------BODY-----------------------------------
   glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
   glEnable ( GL_TEXTURE_2D );
   glPushMatrix();
   	 glTranslatef(0.0 ,(3 * cos(armRad)) - 3.35,0.0);
     glRotatef(-armAngle * legBend, 0.0, 1.0, 0.0);
	 glTranslatef(duckBug[0], duckBug[1], duckBug[2]);
     glRotatef(-90.0, 0.0, 1.0, 0.0);
     glPushMatrix();
       glRotatef(rotat2, 0.0, 1.0, 0.0);
       glRotatef(rotat, 1.0, 0.0, 0.0);
       gluSphere(sphereObj,1.0, sphereBody, sphereBody );
     glPopMatrix();
     glPushMatrix();
       glTranslatef(0.5, 1.25, 0.0);
       glRotatef(rotat2, 0.0, 1.0, 0.0);
	   glRotatef(rotat - 25.0, 1.0, 0.0, 0.0);
       gluSphere(sphereObj,0.75,sphereBody, sphereBody);
     glPopMatrix();
     glDisable ( GL_TEXTURE_2D );	
     //-------------------HEAD------------------------------------
     if (!happyAngry)
       glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
     else if (happyAngry)
       glBindTexture ( GL_TEXTURE_2D, texture_id[3] );  
     glEnable ( GL_TEXTURE_2D );
   	 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
     glPushMatrix();
       glTranslatef(1.0, 2.25, 0.0);
	   glRotatef(90.0, 1.0, 0.0, 0.0);
       glRotatef(50.0, 0.0, 0.0, 1.0);
       gluSphere(sphereObj,0.5, sphereBody, sphereBody );
     glPopMatrix();
     glDisable ( GL_TEXTURE_2D );
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
     //----------------------------EYES---------------------------
     if (!happyAngry)
       glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
     else if (happyAngry)
       glBindTexture ( GL_TEXTURE_2D, texture_id[5] );   
     glEnable ( GL_TEXTURE_2D );
     glPushMatrix();
       glTranslatef(1.3, 2.75, 0.15);
       glRotatef(180.0, 1.0, 0.0, 0.0);
       gluSphere(sphereObj,0.15, sphereJoints, sphereJoints);
     glPopMatrix();
     glPushMatrix();
       glTranslatef(1.3, 2.75, -0.15);
       glRotatef(180.0, 1.0, 0.0, 0.0);
       gluSphere(sphereObj,0.15,  sphereJoints, sphereJoints );
     glPopMatrix();
     glDisable ( GL_TEXTURE_2D );
     if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
     //------------------------------HIPS-----------------------------
     glPushMatrix();
       glTranslatef(0.05, 0.0, 0.85);
       glRotatef(armAngle + kneeAngle, 1.0, 0.0, 0.0);
       gluSphere(sphereObj,0.6, sphereJoints, sphereJoints);
     glPopMatrix();
     glPushMatrix();
       glTranslatef(0.05, 0.0, -0.85);
       glRotatef(-(armAngle * legBend + kneeAngle), 0.0, 0.0, 1.0);
       gluSphere(sphereObj,0.6, sphereJoints, sphereJoints);
     glPopMatrix();
     //-------------------------------ARMS-------------------------
     if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
     //--------------------TOP RIGHT ARM--------------------------
	 glPushMatrix();
       glTranslatef(0.7, 1.60, 0.70);
       glRotatef(-armAngle * legBend, 0.0, 0.0, 1.0);
	   glRotatef(-5.0, 1.0, 0.0, 0.0);
	   gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
	   glPushMatrix();
	     glTranslatef(0.0, -0.6, 0.4);
		 glRotatef(elbowAngle, 0.0, 0.0, 1.0);
	     glRotatef(180.0, 0.0, 0.0, 1.0);
         gluSphere(sphereObj,0.15, sphereJoints, sphereJoints );
		 rightForearm.draw_thing();
		 if (!happyAngry)
           glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
         else if (happyAngry)
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
		 glTranslatef(0.0, 0.75, 0.0);
	     gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
	   glPopMatrix();
	   glRotatef(-35.0, 1.0, 0.0, 0.0);  
	   glRotatef(180.0, 0.0, 0.0, 1.0);  
	   rightArm.draw_thing();
	 glPopMatrix();
     if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
   	 //----------------------BOTTOM RIGHT ARM--------------------------
	 glPushMatrix();
       glTranslatef(0.55, 1.20, 0.75);
       glRotatef(-armAngle * legBend, 0.0, 0.0, 1.0);
	   gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
       glPushMatrix();
	     glTranslatef(0.0, -0.6, 0.4);
		 glRotatef(elbowAngle, 0.0, 0.0, 1.0);
	     glRotatef(180.0, 0.0, 0.0, 1.0);
         gluSphere(sphereObj,0.15, sphereJoints, sphereJoints );
		 rightForearm.draw_thing();
		 if (!happyAngry)
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
         else if (happyAngry)
         glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);;
		 glTranslatef(0.0, 0.75, 0.0);
	     gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
	   glPopMatrix();
	   glRotatef(-35.0, 1.0, 0.0, 0.0);  
	   glRotatef(180.0, 0.0, 0.0, 1.0);  
	   rightArm.draw_thing();
     glPopMatrix();
     if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
     //----------------TOP LEFT ARM---------------------------------   
     glPushMatrix();
       glTranslatef(0.65, 1.60, -0.65);
       glRotatef(armAngle, 0.0, 0.0, 1.0);
	   glRotatef(5.0, 1.0, 0.0, 0.0);
	   gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
	   glPushMatrix();
	     glTranslatef(0.0, -0.6, -0.4);
		 glRotatef(elbowAngle, 0.0, 0.0, 1.0);
	     glRotatef(180.0, 0.0, 0.0, 1.0);
         gluSphere(sphereObj,0.15, sphereJoints, sphereJoints );
		 rightForearm.draw_thing();
		 if (!happyAngry)
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
         else if (happyAngry)
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
		 glTranslatef(0.0, 0.75, 0.0);
	     gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
	   glPopMatrix();
	   glRotatef(35.0, 1.0, 0.0, 0.0);  
	   glRotatef(180.0, 0.0, 0.0, 1.0);  
	   rightArm.draw_thing();
	 glPopMatrix();
     //----------------------------BOTTOM LEFT ARM--------------------
	 if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
     glPushMatrix();
       glTranslatef(0.5, 1.20, -0.7);
       glRotatef(armAngle, 0.0, 0.0, 1.0);
	   gluSphere(sphereObj,0.2, sphereJoints, sphereJoints );
	   glPushMatrix();
	      glTranslatef(0.0, -0.6, -0.4);
		  glRotatef(elbowAngle, 0.0, 0.0, 1.0);
	      glRotatef(180.0, 0.0, 0.0, 1.0);
          gluSphere(sphereObj,0.15, sphereJoints, sphereJoints );
		  rightForearm.draw_thing();
		  if (!happyAngry)
             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
          else if (happyAngry)
             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
		  glTranslatef(0.0, 0.75, 0.0);
	      gluSphere(sphereObj,0.2,sphereJoints, sphereJoints );
		glPopMatrix();
	    glRotatef(35.0, 1.0, 0.0, 0.0);  
	    glRotatef(180.0, 0.0, 0.0, 1.0);  
	    rightArm.draw_thing();
	  glPopMatrix();
   //--------------------------WINGS-------------------------------
	  glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        bugWings();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
}
//************CLASS FUNCTION BUG::BUGWINGS********************
//Draws Bug's transparent wings 
void Bug::bugWings()
{
  float wing = 2.0;
  float wingW = 0.4;
  float wingW2 = 0.3;
  float wingAngle;
  if (!happyAngry)
    wingAngle = 30.0;
  else if (happyAngry)
    wingAngle = 75.0;
  //--------------------RIGHT WING------------------------
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!happyAngry)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green_transparent);
  else if (happyAngry)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow_transparent);
  glPushMatrix();
  glTranslatef(0.0, 2.0, 0.3);
  glRotatef(149.0, 1.0, 0.0, 0.0);
  glRotatef(wingAngle, 0.0, 1.0, 0.0);
  glNormal3f(0.0, -1.0, 0.0);
  glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(wingW, 0.0, 1.0);
    glVertex3f(wingW2, 0.0, 1.5);
    glVertex3f(0.0, 0.0, 2.0);
    glVertex3f(-wingW2, 0.0, 1.5);
    glVertex3f(-wingW, 0.0, 1.0);
  glEnd();
  if (!happyAngry)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_transparent);
  else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_transparent);
    glBegin(GL_POLYGON);
      glVertex3f(wingW, 0.0, 1.0 + wing);
      glVertex3f(wingW2, 0.0, 1.5 + wing);
      glVertex3f(0.0, 0.0, 2.0 + wing);
      glVertex3f(-wingW2, 0.0, 1.5 + wing);
      glVertex3f(-wingW, 0.0, 1.0 + wing);
   	  glVertex3f(-wingW, 0.0, 2.0);
      glVertex3f(wingW, 0.0, 2.0);
	glEnd();  
	glBegin(GL_POLYGON);
	  glVertex3f(-wingW, 0.0, 1.0);
      glVertex3f(-wingW2, 0.0, 1.5);
      glVertex3f(-wingW, 0.0, 2.0);
      glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(-wingW2, 0.0, 1.5);
      glVertex3f(0.0, 0.0, 2.0);  
      glVertex3f(-wingW, 0.0, 2.0);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(0.0, 0.0, 2.0);
      glVertex3f(wingW2, 0.0, 1.5);
      glVertex3f(wingW, 0.0, 2.0);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(wingW2, 0.0, 1.5);
      glVertex3f(wingW, 0.0, 1.0);
      glVertex3f(wingW, 0.0, 2.0);
    glEnd();
  glPopMatrix();

  //-------------Left Wing--------------------------
  if (!happyAngry)
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green_transparent);
   else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow_transparent);
  
  glPushMatrix();
  glTranslatef(0.0, 2.0, 0.3);
  
  glRotatef(149.0, 1.0, 0.0, 0.0);
  glRotatef(-wingAngle, 0.0, 1.0, 0.0);
  glNormal3f(0.0, -1.0, 0.0);
  glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(wingW, 0.0, 1.0);
    glVertex3f(wingW2, 0.0, 1.5);
    glVertex3f(0.0, 0.0, 2.0);
    glVertex3f(-wingW2, 0.0, 1.5);
    glVertex3f(-wingW, 0.0, 1.0);
  glEnd();
   if (!happyAngry)
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_transparent);
   else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_transparent);
  
    glBegin(GL_POLYGON);
      glVertex3f(wingW, 0.0, 1.0 + wing);
      glVertex3f(wingW2, 0.0, 1.5 + wing);
      glVertex3f(0.0, 0.0, 2.0 + wing);
      glVertex3f(-wingW2, 0.0, 1.5 + wing);
      glVertex3f(-wingW, 0.0, 1.0 + wing);
   	  glVertex3f(-wingW, 0.0, 2.0);
      glVertex3f(wingW, 0.0, 2.0);
	glEnd();  
	glBegin(GL_POLYGON);
	  glVertex3f(-wingW, 0.0, 1.0);
      glVertex3f(-wingW2, 0.0, 1.5);
      glVertex3f(-wingW, 0.0, 2.0);
      glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(-wingW2, 0.0, 1.5);
      glVertex3f(0.0, 0.0, 2.0);  
      glVertex3f(-wingW, 0.0, 2.0);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(0.0, 0.0, 2.0);
      glVertex3f(wingW2, 0.0, 1.5);
      glVertex3f(wingW, 0.0, 2.0);
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(wingW2, 0.0, 1.5);
      glVertex3f(wingW, 0.0, 1.0);
      glVertex3f(wingW, 0.0, 2.0);
    glEnd();
  glPopMatrix();
 glDisable(GL_BLEND);
}

//*********CLASS FUNCTION BUG::MOUSERESPONSE**************************
//Process Mouse Button input for this object
void Bug::mouseResponse(int button)
{
 if (button == GLUT_LEFT_BUTTON)
 {
  beenHit[BID] = false;
  beenHit3[BID] = true;
  bugStop = true;
 }
 else if (button == GLUT_MIDDLE_BUTTON)
 {
  if (happyAngry) 
  {
   happyAngry = false;
   increment = 20.0;
  }
  else
  {
   happyAngry = true;
   increment = 40.0;
  }
 }
 else if (button == GLUT_RIGHT_BUTTON)
 {
  if (!beenHit[BID])
    beenHit[BID] = true;
  else
    beenHit[BID] = false;
  bugStop = !(beenHit[0]);
  }
  cout<<BID + 1<<" was selected."<<endl;
}

//***********CLASS FUNCTION BUG::BUGLEGS*********************
//Draw Bug's legs
void Bug::bugLegs()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
  //---------------BODY, ARMS, HEAD----------------------------
  glPushMatrix(); 
    bugBody();
 	glRotatef(-90.0, 0.0, 1.0, 0.0);
	float armRad = (armAngle/360) * 2 * PI;
    glPushMatrix();
   	  glTranslatef(0.0 ,sin(armRad),0.0);
      glRotatef(armAngle, 0.0, 0.0, 1.0);
	//------------------RIGHT THIGH-----------------------
      glPushMatrix();
      glTranslatef(1.05, -1.5, 1.00);
      glRotatef(kneeAngle + (armAngle), 0.0, 0.0, 1.0);
      leg1.draw_thing();
    glPopMatrix();
	//------------------RIGHT CALF------------------
    glPushMatrix();
      glTranslatef(1.00, -1.55, 1.00);
      glRotatef(-15.0, 0.0, 0.0, 1.0);
      glRotatef(180.0, 0.0, 0.0, 1.0);
      calf1.draw_thing();
    glPopMatrix();
    //--------------------RIGHT KNEE--------------------------
	if (!happyAngry)
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    else if (happyAngry)
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    glPushMatrix();
      glTranslatef(1.0, -1.45, 1.0);
      gluSphere(sphereObj,0.25, sphereJoints, sphereJoints );
    glPopMatrix();
  glPopMatrix();
  //---------------------RIGHT FOOT----------------------------
  glPushMatrix();
    glRotatef(armAngle, 0.0, 0.0, 1.0);
    if (!happyAngry)
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    else if (happyAngry)
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    glPushMatrix();
      glTranslatef(1.75, -3.15, 1.0);
      glRotatef(90.0, 0.0, 0.0, 1.0);
      glRotatef(90.0, 0.0, 1.0, 0.0);
      glRotatef(armAngle, 1.0, 0.0, 0.0);
      if (!happyAngry)
        rightFoot.setColor(red);
      else if (happyAngry)
        rightFoot.setColor(black);
      rightFoot.draw_thing();
    glPopMatrix();
   glPopMatrix();
   //----------------------LEFT THIGH-------------------
   glPushMatrix();
  	 glTranslatef(0.0,sin(-armRad * legBend),0.0);
     glRotatef(-armAngle * legBend, 0.0, 0.0, 1.0);
     glPushMatrix();
       glTranslatef(1.05, -1.5, -1.00);
       glRotatef(kneeAngle - (armAngle * legBend) , 0.0, 0.0, 1.0);
       leg2.draw_thing();
     glPopMatrix();
	 //---------------------LEFT CALF----------------
     glPushMatrix();
       glTranslatef(1.00, -1.55, -1.00);
       glRotatef(-15.0, 0.0, 0.0, 1.0);
       glRotatef(180.0, 0.0, 0.0, 1.0);
       calf2.draw_thing();
     glPopMatrix();
     //---------------------LEFT KNEE-------------------
	 if (!happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
     else if (happyAngry)
       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
     glPushMatrix();
       glTranslatef(1.0, -1.45, -1.0);
       gluSphere(sphereObj,0.25, sphereJoints, sphereJoints);
     glPopMatrix();
   glPopMatrix();
     //----------------------LEFT FOOT------------------------ 
   glPushMatrix();
     glRotatef(-armAngle * legBend, 0.0, 0.0, 1.0);
     glPushMatrix();
       glTranslatef(1.75, -3.15, -1.0);
       glRotatef(90.0, 0.0, 0.0, 1.0);
       glRotatef(90.0, 0.0, 1.0, 0.0);
       glRotatef(-armAngle * legBend, 1.0, 0.0, 0.0);
       if (!happyAngry)
         leftFoot.setColor(red);
       else if (happyAngry)
       leftFoot.setColor(black);
       leftFoot.draw_thing();
     glPopMatrix();
   glPopMatrix();
}

//***********CLASS FUNCTION BUG::BUGHOP*****************************
//Make Bug Jump, and Turn 180 degrees
void Bug::bugHop()
{
if (beenHit2[BID])
 {
  //Bend Knees Down 
  if (!angleComp)
  {
   beenHit[BID] = false;
   angleComp = true;
   finalAng = 180.0;
   hopping = true;
  } 
  float ll = 1.5;
  float hopAngle = (kneeAngle/360.0) * 2 * PI; 
  if (!kneeDown)
  {
   //Don't do anything unless bug has stopped moving 
   if (((!happyAngry && armBase <185 && armBase >165)) || (happyAngry && armBase <195 && armBase >155))
   {
    if (kneeAngle < 90.0)
        kneeAngle = kneeAngle + 5.0;
    duckBug[1] = 0.25 +  sin(hopAngle -35.0);
    duckBug[2] = 0.25 +  sin(hopAngle - 35.0) ; 
   }
   
   if (kneeAngle >= 90.0) kneeDown = true;
  }
  
  //Bend Knees Up and Jump   
 if (kneeDown)
 {
  if (kneeAngle > 35.0)
     kneeAngle = kneeAngle - 10.0;
  duckBug[1] =  0.25 + sin(hopAngle - 35.0) ; 
  duckBug[2] =  0.25 + sin(hopAngle - 35.0) ; 
  if (kneeAngle <=35.0)
  {
   kneeAngle = 35.0;
   duckBug[1] = 0.0; 
   duckBug[2] = 0.0; 
   //bug has to jump and turn
   if (finalAng > 0.0)
   {
    finalAng = finalAng - 17.0;
    bugAngle = bugAngle + 17.0;
    if (bugAngle >=360.0)
      bugAngle = bugAngle - 360.0;
   }
   towards(myPos);
   //Translate upwards for Jump
   if (!hopUp && myPos[1] < 2.0)
      myPos[1] = myPos[1] + 0.35;
   if (!hopUp && myPos[1] > 2.0)
      hopUp = true;
   //Translate downward for Jump
   if (hopUp && myPos[1] > 0.3)
      myPos[1] = myPos[1] - 0.35;
   //Jump is over, Cleanup
   if (hopUp && myPos[1] <= 0.3)
   {
     kneeDown = false;
     beenHit2[BID] = false;
	 hopUp = false;
	 angleComp = false;
     beenHit[BID] = true;
     bugStop = false;
	 hopping = false;
   }
  }
 }
 
 }
}

//**************CLASS FUNCTION BUG::BUGSLEEP************************
//Make Bug go to sleep
void Bug::bugSleep()
{

if (beenHit3[BID] && !hopping)
 {
 
  float ll = 1.5;
  if (!kneeDown)
  {
   //Don't do anything unless bug has stopped moving
   if (((!happyAngry && armBase <185 && armBase >165)) || 
	              ((happyAngry && armBase <195 && armBase >155)) )
   {
    //--------------------------------
    if (sleepAngle < 90.0 && sleepTime == 0.0)
	{
     sleepAngle = sleepAngle + 10.0;
	 elbowAngle = elbowAngle - 9.5;
     aniPos[1] = -sin((sleepAngle/360) * 2 * PI) * 2.5;
	 aniPos[2] = -sin((sleepAngle/360) * 2 * PI) * 2.0;
	}
  
   //-----------------------------------
   if (sleepAngle >=90.0)
   {
    if (time % 10 == 0 && sleepTime < 40.0)
	   sleepTime = sleepTime + 1.0;
   }
   //-------------------------
   if (sleepTime >= 40.0)
	{
    if (sleepAngle > 0.0)
	{
     sleepAngle = sleepAngle - 10.0;
	 elbowAngle = elbowAngle + 9.5;
     aniPos[1] = -sin((sleepAngle/360) * 2 * PI) * 2.5;
	 aniPos[2] = -sin((sleepAngle/360) * 2 * PI) * 2.0;
	}
    if (sleepAngle <= 0.0)
	{
     beenHit3[BID] = false;
	 beenHit[BID] = true;
	 bugStop = false;
	 sleepAngle = 0.0;
	 sleepTime = 0.0;
	 happyAngry = false;
	 increment = 20.0;
	}
   }
   }
  }
 }
}
//******************CLASS FUNCTION BUG::BUGWALK********************
//Make Bug walk
void Bug::bugWalk()
{
 if (time % 20 == 0)
  {
  angleChange1 = rand() % 2;
  if (angleChange1 ==1) angleChange1 = -1;
  if (angleChange1 ==0) angleChange1 = 1;
  angleChange2 = rand() % 2;
  if (angleChange2 ==1) angleChange2 = -1;
  if (angleChange2 ==0) angleChange2 = 1;
  } 
  float moveIncr = 0.25;
  bAngle = (bugAngle/360.0) * 2.0 * PI;
  //Bug leg movement
  if (beenHit[BID] && !bugStop && sleepAngle==0.0)
    armBase = armBase + increment;
  if (armBase >=360) armBase = 0.0;
  armAngle = sin((armBase/360) * 2 * PI) * 30;
  //Bug movement X and Z 
  if (beenHit[BID] && !bugStop && sleepAngle==0.0)
  {
  if (!happyAngry)
	  bugAngle =  bugAngle + ((rand() % 10) * angleChange1);
  else if (happyAngry)
   bugAngle =  bugAngle + ((rand() % 15) * angleChange1);
   if (dist(myPos[0], myPos[2]) > 15.0) 
   {
    beenHit2[BID] = true;
    bugStop = true;
   }
   myPos[2] = myPos[2] + (moveIncr * cos(bAngle));
   myPos[0] = myPos[0] + (moveIncr * sin(bAngle));
  }
}
//******************CLASS FUNCTION BUG::BUGATTENTION*********************
//Make Bug stand at attention (original position)
void Bug::bugAttention()
{
  if (!happyAngry && bugStop && (!(armBase <185 && armBase >165)) || 
	       (happyAngry && bugStop && (!(armBase <195 && armBase >155))))
  armBase = armBase + increment;
  if (armBase >=360) armBase = 0.0;
  armAngle = sin((armBase/360) * 2 * PI) * 30;
  }
//******************CLASS FUNCTION BUG::BUGMASTER************************
//Manage Bug's animations
void Bug::bugMaster()
{
 bugAttention();
 bugSleep();
 bugHop();
 bugWalk();
}

//************FUNCTION WRITEMESSAGE*****************
void writemessage()
{
   printf("\n\
   program4.cpp by Joe Baldwin\n\
   Extra: Bugs are made of 3 segments and have animated arms and legs.\n\
   Extra: Bugs' appearance changes texture depending on if Bug is angry.\n\
   Extra: Animated Lava Surrounding Platform\n\
   Prints out record of hits in standard output.\n\
   Uses double buffering for smooth animation\n\
   Left mouse click on Bug---- Bug will go to Sleep\n\
   Middle mouse click on Bug-- Bug will get Angry/Happy\n\
   Right Mouse click on Bug--- Bug will start/stop walking \n\
   a, A, b, B, c, C ---------- change light source position\n\
   x, X, y, Y, z, Z ---------- change viewer position\n\
   1, 2, 3, 4, 5, 6 ---------- change to preset viewer positions\n\
   ESC ----------------------- exit\n\
   \n");
}

//************FUNCTION LOAD TEXTURE*********************
//Given File name and attributes, load texture
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
   gluBuild2DMipmaps ( GL_TEXTURE_2D, colour_type, width, height,
                        colour_type, GL_UNSIGNED_BYTE, bitmap );
   //  Free up the array
   free ( bitmap );
}
//********Initialize Bugs******************************



Bug bugOne(0);
Bug bugTwo(1);
Bug bugThree(2);
Bug bugFour(3);




//*******FUNCTION LAVAPROCESS**************************
//Increments lavaChange's values
void lavaProcess()
{
 
	 for (int i = 0; i < table; i++)
	   for (int j = 0; j < table; j++)
		{
         lavaChange[i][j] =  lavaChange[i][j] + 2.0;
		 if ( lavaChange[i][j] >= 360.0)  
			   lavaChange[i][j] =  0.0;
		 lavaPts[i][j][1] = cos( (lavaChange[i][j]/360) * 2 * PI);
 		}
     
}

//**********FUNCTION BUGMOVEMENT****************************
//Idle Animation Function Controlling All bugs' movement
void bugMovement(void)
 {
  time = time + 1;
  if (time == 20) time = 0;
  lavaProcess();
  bugOne.bugMaster();
  bugTwo.bugMaster(); 
  bugThree.bugMaster();
  bugFour.bugMaster();
  glutPostRedisplay();
 }


//*****************FUNCTION DRAWALLBUGS***********************
//Draw all bugs and load names for selection
void drawAllBugs(GLenum mode)
{
 if (mode== GL_SELECT)
 glPushName(1);
 bugOne.bugDraw();
 if (mode== GL_SELECT)
 glLoadName(2);
 bugTwo.bugDraw();
 if (mode== GL_SELECT)
 glLoadName(3);
 bugThree.bugDraw();
 if (mode== GL_SELECT)
 glLoadName(4);
 bugFour.bugDraw();
}
//****************FUNCTION LEASTOF***************************
//Returns index of least non-zero element
int leastOf(float a, float b, float c, float d)
{
 int temp = 0;
 float holdUm[4];
 holdUm[0] = a;
 holdUm[1] = b;
 holdUm[2] = c;
 holdUm[3] = d;
 float least;
 bool gotLeast = false;
 for (int i = 0; i < 4; i++)
 {
  if (holdUm[i] != 0.0 && !gotLeast)
  {
   least = holdUm[i];
   temp = i;
   gotLeast = true;
  }
  if (least > holdUm[i] && holdUm[i] != 0.0)
  {
   least = holdUm[i];
   temp = i;
  }
 }
 return temp;
}
//***************FUNCTION MOSTOF****************************
//Returns index of greatest element
int mostOf(float a, float b, float c, float d)
{
 int temp = 0;
 if (a>=b && a>=c && a>=d) temp = 0;
 if (b>=a && b>=c && b>=d) temp = 1;
 if (c>=a && c>=b && b>=d) temp = 2;
 if (d>=a && d>=b && d>=c) temp = 3;
 return temp;
}


//**************FUNCTION PROCESSHITS***********************
//Process Mouse Hits and send results to affected Bugs
void processHits (GLuint hits, GLuint buffer[], int button)
{
 unsigned int i,j;
 GLuint names, *ptr;
 printf ("hits = %d\n", hits);
 ptr = (GLuint *) buffer;
 
 float z1;
 
 float zOne = 0.0;
 float zTwo = 0.0;
 float zThree = 0.0;
 float zFour = 0.0;

 for (i=0; i < hits; i++) 
 {
	 names = *ptr;
	 ptr++;
	 z1 = (float) *ptr/0x7fffffff;
	 ptr++;
	 ptr++;
	 cout<<"Name is ";
	 for (j = 0; j < names; j++)
	 {
		  if (*ptr !=0) cout<<*ptr;
		  if (j==1)
		  {
		  if (*ptr == 1) zOne = z1; 
		  else if (*ptr ==2) zTwo = z1;
		     else if (*ptr ==3) zThree = z1;
		        else if (*ptr ==4) zFour = z1; 
		  cout<<" with z of "<<z1<<endl;
		  }
   	  ptr++;
	 }
 }
     int t;
	if (hits==1)
	  t = mostOf(zOne,zTwo,zThree,zFour);
	else if (hits > 1)
	  t = leastOf(zOne,zTwo,zThree,zFour);
    
	if (t==0)  bugOne.mouseResponse(button);
	 else if (t==1)  bugTwo.mouseResponse(button);
	  else if (t==2) bugThree.mouseResponse(button);
	   else if (t==3) bugFour.mouseResponse(button);
          
  cout<<"-----------------------------"<<endl;
}

//******************FUNCTION PICKBUGS******************
//Use Mouse to select Bugs. If Multiple Bugs are Hit, use Bug with Smallest
//  Z-Value
void pickBugs(int button, int state, int x, int y)
{
 GLuint selectBuf[ BUFSIZE ] ;
 GLint hits;
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
   gluPerspective(45.0, (GLfloat) ww/(GLfloat) hh, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW); 
   glPushMatrix();
     glTranslatef(bugPos2[0], bugPos2[1], bugPos2[2]);
     drawAllBugs(GL_SELECT);
   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glFlush();
 glMatrixMode(GL_MODELVIEW); 
 hits = glRenderMode(GL_RENDER);
 processHits(hits,selectBuf, button);
 glutPostRedisplay();
}

//***********FUNCTION RESHAPE*****************************
void reshape(int w, int h)
{
 ww = w;
 hh = h;
 glViewport(0, 0, (GLsizei) w, (GLsizei) h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 1.0, 70.0);
 glMatrixMode(GL_MODELVIEW);
}
//***************FUNCTION INIT*******************************

void init(void) 
{
	//Initialize array of points for lava
    int negat = rand() % 2;
	if (negat==0) negat = -1;
	else negat = 1;
	for (int i = 0; i < table; i++)
		for (int j = 0; j < table; j++)
		{
         lavaPts[i][j][0] =  (float) j * unit;
         lavaPts[i][j][1] =  0.0; 
         lavaPts[i][j][2] =  (float) i * unit;
		 lavaChange[i][j] = rand() % 360;
		}

   writemessage(); 
   glClearColor(0.0, 1.0, 1.0, 1.0);
   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      /* initially GL_FILL mode, later GL_LINE to show wireframe */
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
      /* enable two-sided lighting to properly show interior of cube */
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glDepthRange(0.0, 30.0);
   
   
   glEnable(GL_LIGHT0);
   
  //*********************************************
   //Learned how to do multiple textures
   //   http://home.clara.net/paulyg/prog4.htm
   
   glEnable ( GL_TEXTURE_2D );
   glGenTextures (6, texture_id); 
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
    //bug shell texture
   glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
     load_texture ( "balj3289F.bmp", 256, 256, 3, GL_RGB, GL_LINEAR );
   //Picture was found at: http://www.tresandpaul.freeservers.com/Tres%20Mosaics.htm
   //  then modified.
   //floor tecture
   glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
     load_texture ( "balj3289A.bmp", 256, 256, 3, GL_RGB, GL_LINEAR );
   //bug happy face texture
   glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
     load_texture ( "balj3289E.bmp", 128, 128, 3, GL_RGB, GL_LINEAR );
   //bug angry face texture
   glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
     load_texture ( "balj3289D.bmp", 128, 128, 3, GL_RGB, GL_LINEAR );
   //happy eyes texture
   glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
     load_texture ( "balj3289B.bmp", 64, 64, 3, GL_RGB, GL_LINEAR );
   //angry eyes texture
   glBindTexture ( GL_TEXTURE_2D, texture_id[5] );
     load_texture ( "balj3289C.bmp", 64, 64, 3, GL_RGB, GL_LINEAR );
   glDisable(GL_TEXTURE_2D);
   //Initialize pointer object
   sphereObj = gluNewQuadric();
   gluQuadricTexture( sphereObj, GL_TRUE); 
   gluQuadricOrientation( sphereObj, GLU_OUTSIDE );
   //*********************
    //Initialize arrays for animation depending on selection
    beenHit = new bool[4];
	beenHit[0] = true;
	beenHit[1] = true;
	beenHit[2] = true;
	beenHit[3] = true;

    beenHit2 = new bool[4];
	beenHit2[0] = false;
	beenHit2[1] = false;
    beenHit2[2] = false;
	beenHit2[3] = false;

    beenHit3 = new bool[4];
	beenHit3[0] = false;
	beenHit3[1] = false;
  	beenHit3[2] = false;
	beenHit3[3] = false;
    //********************
     
   //Display List for floor
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
   theArena = glGenLists(1);
   glNewList(theArena, GL_COMPILE);
     glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
     glEnable ( GL_TEXTURE_2D );
     glPushMatrix();
       glTranslatef(-0.5, 0.0, 0.0);
        glRotatef(90.0, 0.0, 1.0, 0.0);
	   glRotatef(90.0, 1.0, 0.0, 0.0);
       gluDisk(sphereObj, 0.0, 20.0, 10.0, 10.0 );
     glPopMatrix();
     glDisable ( GL_TEXTURE_2D );
   glEndList();
   //Display List for Sun
   theSun = glGenLists(2);
   glNewList(theSun, GL_COMPILE);
     glPushMatrix();
      glMaterialfv(GL_FRONT, GL_EMISSION, yellow); 
   glTranslatef(10.0, 10.0, -30.0);
   gluSphere(sphereObj,5.0, sphereBody, sphereBody );
   glPopMatrix();
     glMaterialfv(GL_FRONT, GL_EMISSION, none); 
   glEndList();

   glutIdleFunc(bugMovement);
   
}

//********************FUNCTION GOLAVA**************************
//increments or decrements lava points' y values
void goLava()
{

float n[3];
glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
  glPushMatrix();
  glTranslatef(-((float) table * unit)/2.0, -2.5, -((float) table * unit)/2.0);
	 for (int i = 0; i < table - 1; i++)
	   for (int j = 0; j < table - 1; j++)
	   {
          
		   norm(n, lavaPts[i][j][0],lavaPts[i][j][1],lavaPts[i][j][2],
			   lavaPts[i][j+1][0],lavaPts[i][j+1][1],lavaPts[i][j+1][2],
			   lavaPts[i+1][j+1][0],lavaPts[i+1][j+1][1],lavaPts[i+1][j+1][2]);
		   glNormal3f(n[0],n[1],n[2]);
		   glBegin(GL_POLYGON);
            glVertex3f(lavaPts[i][j][0],lavaPts[i][j][1],lavaPts[i][j][2]);
	        glVertex3f(lavaPts[i][j+1][0],lavaPts[i][j+1][1],lavaPts[i][j+1][2]);
            glVertex3f(lavaPts[i+1][j+1][0],lavaPts[i+1][j+1][1],lavaPts[i+1][j+1][2]);
            glVertex3f(lavaPts[i+1][j][0],lavaPts[i+1][j][1],lavaPts[i+1][j][2]);
          glEnd();
	   }
   glPopMatrix();
  
}


//********************FUNCTION DISPLAY**************************
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   glLoadIdentity(); 
   gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);
   
   
   glMaterialfv(GL_FRONT, GL_EMISSION, white); 
   glLightfv(GL_LIGHT0, GL_POSITION, lpos);
   
   glPushMatrix();
     glTranslatef(lpos[0],lpos[1],lpos[2]);
     glutSolidSphere(0.25, 10, 8);
   glPopMatrix();
   glMaterialfv(GL_FRONT, GL_EMISSION, none);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, medium);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, medium);
   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   
   glPushMatrix();
     glTranslatef(0.0, -1.25, 0.0);
     glCallList(theArena);
   glPopMatrix();
     glCallList(theSun);
   
   goLava();
   
   glPushMatrix();
     glTranslatef(bugPos2[0], bugPos2[1], bugPos2[2]);
     drawAllBugs(GL_RENDER);
   glPopMatrix();
   
   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
   glFlush();
   glutSwapBuffers();
  
}

//*****************FUNCTION KEYBOARD************************ 
/* exit program with "esc" key 
 * light source position controlled by "a", "A", "b", "B", "c", "C"
 * viewer position controlled by "x", "X", "y", "Y", "z", "Z"
 * preset viewer position 1, 2, 3, 4, 5, 6
 * switch between lights 1-3 --> 8,9,0
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
      

 	  // Preset Camera Positions 1-6
	  //***********************************************
	  case '1':                
         viewer[0] = -30.0;
		 viewer[1] = 10.0;
		 viewer[2] = 30.0;
	     glutPostRedisplay();
         break;
      case '2':       
         viewer[0] = 1.0;
		 viewer[1] = 5.0;
		 viewer[2] = -3.0;
         glutPostRedisplay();
         break;
      case '3':        
		 viewer[0] = -10.0;
		 viewer[1] = 2.0;
		 viewer[2] = 10.0;
         glutPostRedisplay();
         break;
      case '4':    
         viewer[0] = -10.0;
		 viewer[1] = 10.0;
		 viewer[2] = 15.0;
         glutPostRedisplay();
         break;
      case '5':        
		 viewer[0] = 2.0;
		 viewer[1] = 30.0;
		 viewer[2] = -4.0;
         glutPostRedisplay();
         break;
      case '6':        
		 viewer[0] = 12.0;
		 viewer[1] = 15.0;
		 viewer[2] = -10.0;
         glutPostRedisplay();
         break;
 	  // Switch Between three lights
	
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
   glutInitWindowSize(900, 800); 
   glutInitWindowPosition(300, 0);
   glutCreateWindow("Program 3: Joe Baldwin");
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutKeyboardFunc(keyboard);
   glutMouseFunc(pickBugs);
   glutMainLoop();
   return 0;
}



