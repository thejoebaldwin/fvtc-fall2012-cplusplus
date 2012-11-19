//box.h
#include <iostream>
#include <string>
using namespace std;

class box
{
private:
	int _width;
public:
	void setWidth(int width);
	string toString();
	box(int width);
	box();
	friend ostream& operator<<(ostream&, const box&);


};
