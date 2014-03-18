#include <glut.h>


class square
{
private:
	GLfloat _width;
	bool _isVisible;
	GLfloat x, y;
	GLfloat *_color;

public:
	square();
	square(GLfloat, GLfloat*);
	void show();
	void hide();
	void draw();
	void move(GLfloat, GLfloat);
	void setColor(GLfloat*);
};