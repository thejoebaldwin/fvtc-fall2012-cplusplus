//these have to be in this order, or you will get compile errors
#include <stdlib.h>
#include <glut.h>

class square
{
private:
	GLfloat _width;
	bool _isVisible;
	GLfloat x, y;
	GLfloat *_color;
	GLfloat _top, _bottom, _left, _right;

public:
	GLfloat z;
	GLfloat _velocity_x;
	GLfloat _velocity_y;
	square();
	square(GLfloat, GLfloat*);
	void show();
	void hide();
	void draw();
	void move(GLfloat, GLfloat);
	void move();
	void setColor(GLfloat*);
	void setLimits(GLfloat, GLfloat, GLfloat, GLfloat);
};