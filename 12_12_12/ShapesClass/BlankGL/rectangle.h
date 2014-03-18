#include "square.h"


class rectangle : public square
{
public:

	GLfloat _angle;
	void rotate();
	rectangle();
	void draw();
};
