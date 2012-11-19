#include <conio.h>
#include <iostream>

using namespace std;

class line
{
private:
  int _height;
  int _width;

public:
    line();
	line(int w, int h);
	void setHeight(int h);
	void setWidth(int w);
	string toString();
};