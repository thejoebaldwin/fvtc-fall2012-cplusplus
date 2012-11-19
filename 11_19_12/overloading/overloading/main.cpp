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

	/*cout << b << endl;
	cout << c;*/


	box arrBox[5];
	int arrBoxLength = 5;
	for (int i = 0; i < arrBoxLength;i++)
	{
		arrBox[i] = NULL;
	}

	

	for (int i = 0; i < arrBoxLength;i++)
	{
		
		 cout << arrBox[i] << endl << endl;
		
	}



	_getch();
	return 0;
}