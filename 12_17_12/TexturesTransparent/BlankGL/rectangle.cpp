#include "rectangle.h"


rectangle::rectangle()
{
	square::square();
	_type = "rectangle";
}


void rectangle::draw()
{
	if (_isVisible)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(_angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _color);
			glVertex3f(-_width/2,_width/2 , 0.0f);
			glVertex3f(_width,_width/2 , 0.0f);
			glVertex3f(_width,-_width/2 , 0.0f);
			glVertex3f(-_width/2,-_width/2 , 0.0f);
		glEnd();
	 glPopMatrix();
	}

}