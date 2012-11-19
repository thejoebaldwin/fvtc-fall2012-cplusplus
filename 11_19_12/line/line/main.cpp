#include <conio.h>
#include <iostream>
#include "line.h"
#include <string>

using namespace std;

int main()
{


	


	int width;
	int height;



		

	cout << "Please enter a line height:";
	cin >> height;
	cout << endl << "Please enter a line width:";
	cin >> width;
	cout << endl;
	
	line l(width, height);

	
	cout << l.toString();

	

	_getch();
	return 0;
}