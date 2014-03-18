
#include "square.h"

square::square()
{
	_width = 5.0f;
	_isVisible = true;
	x = 0;
	y = 0;
	_color = new GLfloat[4];
	_color[0] = 1;
	_color[1] = 0;
	_color[2] = 0;
	_color[3] = 1;
	_velocity_x = (rand() % 100) / 1000;
	_velocity_y = (rand() % 100) / 1000;
}

void square::setLimits(GLfloat top, GLfloat bottom, GLfloat left, GLfloat right)
{
	_top = top;
	_bottom = bottom;
	_left = left;
	_right = right;
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
		_velocity_x = _velocity_x * -1;
		isCollision = true;
	}
	else if (x < _left)
	{
		_velocity_x = _velocity_x * -1;
		isCollision = true;
	}
	if (y > _top)
	{
		_velocity_y = _velocity_y * -1;
		isCollision = true;
	}
	else if (y < _bottom)
	{
		_velocity_y = _velocity_y * -1;
		isCollision = true;
	}
	//if a collision occured then randomly set a new color and width
	if (isCollision)
	{
		_color[0] = (rand() % 10) /(float) 10;
		_color[1] = (rand() % 10) /(float) 10;
		_color[2] =  (rand() % 10) /(float) 10;
		_width = (rand() % 10);
	}
	//update the x and y position according to the velocities
	x += _velocity_x;
	y += _velocity_y;
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

//compute the vertices and render the square using GL_QUADS
void square::draw()
{
	if (_isVisible)
	{
	 glBegin(GL_QUADS);
       glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _color);
	   glVertex3f(-_width/2 + x,_width/2 + y, z);
	   glVertex3f(_width/2 + x,_width/2 + y,z);
       glVertex3f(_width/2 + x,-_width/2 + y,z);
	   glVertex3f(-_width/2 +x,-_width/2 + y,z);
     glEnd();
	}
}

//move the square x and y values 
void square::move(GLfloat move_x, GLfloat move_y)
{
	x += move_x;
	y += move_y;
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
	//os << "||I am a " << s._type << endl;
	return os;
}


square& operator+(square &s1, square &s2)
{
	square sum;
	sum._width = s1._width + s2._width;
	return sum;
}