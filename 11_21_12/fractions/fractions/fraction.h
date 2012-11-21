#include <iostream>

using namespace std;

class fraction
{
private:

public:
	fraction();
	fraction(int, int);
	int Top;
	int Bottom;

	void reduce();
	double ToDouble();
	friend ostream& operator <<(ostream&, fraction&);
	friend fraction& operator +(fraction&, fraction&);
};