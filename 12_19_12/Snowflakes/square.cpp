
#include "square.h"
#include <string>




square::square()
{
	isRotating = false;
	_width = ((rand() % 50) / (float) 10);
	_isVisible = true;
	x = 0;
	y = 0;
	_color = new GLfloat[4];
	_color[0] = 1;
	_color[1] = 0;
	_color[2] = 0;
	_color[3] = 1;
	textureIndex = 0;
	_velocity_x = getNewVelocity() * getNegative();
	
	_velocity_y = getNewVelocity(); // * getNegative();
	if (_velocity_y > 0) _velocity_y = _velocity_y * -1;
	
	_angleIncrement_x = (rand() % 100) /(float) 1000 * getNegative();
	_angleIncrement_z = (rand() % 100) /(float) 1000 * getNegative();
	_type = "square";
	_angle = 0;
}


int square::getNegative()
{
	int multiplier = 1;
	if (rand() % 2 == 0) multiplier = -1;
	return multiplier;
}
void square::setLimits(GLfloat top, GLfloat bottom, GLfloat left, GLfloat right)
{
	_top = top;
	_bottom = bottom;
	_left = left;
	_right = right;
}

void square::rotate()
{
	if (isRotating)
	{
		_angle += _angleIncrement_x;
	}
}


//mutator to update square position. Can detect if a collision with boundaries occurred.
void square::move()
{
	bool isCollision = false;

	//_right, _left, _top and _bottom are boundaries WE set to represent the edge of the screen. 
	//if square goes past it, flip the corresponding velocity to opposite
	//also set the flag that a collision ocurred.
	if (x > _right)
	{
		//_velocity_x = _velocity_x * -1;
		x = _left;
		isCollision = true;
	}
	else if (x < _left)
	{
		//_velocity_x = _velocity_x * -1;
		x = _right;
		isCollision = true;
	}
	/*if (y > _top)
	{
		_velocity_y = _velocity_y * -1;
		isCollision = true;
	}
	else*/
	if (y < _bottom)
	{
		//_velocity_y = _velocity_y * -1;
		//isCollision = true;
		y = _top;
	}
	//if a collision occured then randomly set a new color and width
	if (isCollision)
	{
		_color[0] = (rand() % 10) /(float) 10;
		_color[1] = (rand() % 10) /(float) 10;
		_color[2] =  (rand() % 10) /(float) 10;
		//_width = (rand() % 10);
	}
	//update the x and y position according to the velocities
	x += _velocity_x / 4;
	y += _velocity_y;
}

GLfloat square::getNewVelocity()
{
	
return (rand() % 100) /(float) 10000;

}

//constructor to set width and color
square::square(GLfloat width, GLfloat *color)
{
	_width = width;
	_isVisible = true;
	x = 0;
	y = 0;
	_color = new GLfloat[4];
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];
	_color[3] = color[3];
	_type = "square";
}

//set the visible flag to true
void square::show()
{
	_isVisible = true;
}

//set the visible flag to false
void square::hide()
{
	_isVisible = false;
}

void square::setWidth(GLfloat width)
{
	_width = width;
}

//compute the vertices and render the square using GL_QUADS
void square::draw()
{
	if (_isVisible)
	{
	static GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};
		static GLfloat green[]   = {0.0, 1.0, 0.0, 1.0};
		static GLfloat white[]   = {1.0, 1.0, 1.0, 1.0};
	 glPushMatrix();
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 255.0f);
	   glTranslatef(x, y, z);
	   glRotatef(_angle, 0.0f, 1.0f, 0.5f); glBegin(GL_QUADS);
	     glNormal3f(0.0f, 0.0f, -1.0f);
	       
		   
		   glTexCoord2f(0.0, 0.0); glVertex3f(- _width / 2,- _width / 2,  z);
		
		   glTexCoord2f(0.0, 1.0); glVertex3f(- _width / 2,_width / 2,  z);
		  
		   glTexCoord2f(1.0, 1.0); glVertex3f(_width / 2,_width / 2,  z);
		  
		   glTexCoord2f(1.0, 0.0); glVertex3f(_width / 2,- _width / 2, z);
	   glEnd();
	  

	      glBegin(GL_QUADS);
	     
		   glNormal3f(0.0f, 0.0f, 1.0f);
		    glTexCoord2f(0.0, 0.0); glVertex3f(- _width / 2,- _width / 2,  z + 0.01f);
		      glTexCoord2f(1.0, 0.0); glVertex3f(_width / 2,- _width / 2, z + 0.01f);
		     glTexCoord2f(1.0, 1.0); glVertex3f(_width / 2,_width / 2,  z + 0.01f);

		  glTexCoord2f(0.0, 1.0); glVertex3f(- _width / 2,_width / 2,  z + 0.01f);

		  
		  
	   glEnd();

	  
	 glPopMatrix();
	}
}

//move the square x and y values 
void square::move(GLfloat move_x, GLfloat move_y)
{
	x += move_x;
	y += move_y;
}

//move the square x and y values 
void square::move(GLfloat move_x, GLfloat move_y, GLfloat move_z)
{
	x += move_x;
	y += move_y;
	z += move_z;
}

//set the RGBA values for the render color
void square::setColor(GLfloat* color)
{
	_color[0] = color[0];
	_color[1] = color[1];
	_color[2] = color[2];
	_color[3] = color[3];
}


GLint square::getName()
{
	return _name;
}

void square::setName(GLint name)
{
	_name = name;
}

void square::update()
{
	move();
	rotate();
}

string square::getType()
{
	return _type;
}

void square::grow()
{
	_width *= 1.05f;
}


ostream& operator<<(ostream &os, square &s)
{
	os << "Width:" << s._width << "||x:" << s.x << "||y:" << s.y << endl;
	os << "||I am a " << s._type << endl;
	return os;
}


square& operator+(square &s1, square &s2)
{
	square sum;
	sum._width = s1._width + s2._width;
	return sum;
}