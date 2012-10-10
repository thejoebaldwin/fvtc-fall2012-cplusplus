#include <iostream>
#include <conio.h>
using namespace std;

void getPi(float &piContainer)
{
	piContainer = 22/7;
}


int main()
{
	float piValue = 0;
	getPi(piValue);
	cout << piValue << endl;
	_getch();
	return 0;
}