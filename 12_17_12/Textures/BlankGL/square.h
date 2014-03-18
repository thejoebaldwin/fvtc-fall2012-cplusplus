//these have to be in this order, or you will get compile errors
#include <stdlib.h>
#include <glut.h>
#include <iostream>

using namespace std;

class square
{
private:
	/*GLfloat _width;
	bool _isVisible;
	GLfloat x, y;
	GLfloat *_color;
	GLfloat _top, _bottom, _left, _right;
	GLint _name;*/

protected:
	GLfloat _width;
	bool _isVisible;
	GLfloat x, y;
	GLfloat *_color;
	GLfloat _top, _bottom, _left, _right;
	GLint _name;
	string _type;
	GLfloat _angle;
	GLfloat _angleIncrement_x;
	GLfloat _angleIncrement_z;
	GLfloat getNewVelocity();
	int getNegative();
	

public:
	string getType();
	GLfloat z;
	bool isRotating;
	GLfloat _velocity_x;
	GLfloat _velocity_y;
	square();
	square(GLfloat, GLfloat*);
	void show();
	void hide();
	void virtual draw();
	void move(GLfloat, GLfloat);
	void move();
	void setColor(GLfloat*);
	void setLimits(GLfloat, GLfloat, GLfloat, GLfloat);
	GLint getName();
    void setName(GLint);
	void rotate();

	void grow();
	friend ostream& operator<<(ostream&, square&);
	friend square& operator+(square&, square&);

};