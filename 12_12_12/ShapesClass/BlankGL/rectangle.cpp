#include "rectangle.h"


rectangle::rectangle()
{

	_type = "rectangle";
	_angle = 0;

}

void rectangle::rotate()
{
	_angle += 1;
}
void rectangle::draw()
{
	if (_isVisible)
	{

		glPushMatrix();
		glRotatef(_angle, 1.0f, 0.0f, 0.0f);

		glBegin(GL_QUADS);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _color);
			glVertex3f(-_width/2 + x,_width/2 + y, z);
			glVertex3f(_width + x,_width/2 + y,z);
			glVertex3f(_width + x,-_width/2 + y,z);
			glVertex3f(-_width/2 +x,-_width/2 + y,z);
		glEnd();
	 glPopMatrix();
	}

}