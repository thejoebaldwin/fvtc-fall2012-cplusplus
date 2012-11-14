#include <iostream>
#include <conio.h>
#include "box.h"

using namespace std;


int main()
{
	box b;
	//b.setWidth(10);

	box c(13);
	//c.setWidth(4);


	/*cout << b.toString() << endl;
	cout << c.toString();*/

	cout << b << endl;
	cout << c;

	_getch();
	return 0;
}