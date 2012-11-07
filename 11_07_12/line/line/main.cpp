#include <conio.h>
#include <iostream>
#include "line.h"
#include <string>

using namespace std;

int main()
{
	int width;
	int height;


	char cubed = 254;

	string hello = "power of " + cubed;

	cout << cubed << endl;
	_getch();
		

	cout << "Please enter a line height:";
	cin >> height;
	cout << endl << "Please enter a line width:";
	cin >> width;
	cout << endl;
	
	line l(width, height);

	//l.setHeight(height);
	//l.setWidth(width);
	cout << l.toString();

	
	/*line l;
	l.setWidth(10);
	l.setHeight(1);
	cout << l.toString() << endl;

	line myLine;
	myLine.setHeight(20);
	myLine.setWidth(4);
	cout << myLine.toString() << endl;*/



	_getch();
	return 0;
}