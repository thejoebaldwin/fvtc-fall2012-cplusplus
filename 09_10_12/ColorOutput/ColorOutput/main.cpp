#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;

int main()
{
    //color value for console
	int color = 25;  
	//console reference	
	HANDLE	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//this will loop until either 0 is entered, or a non-numeric value
	while (color != 0)
	{
		cout << "Enter a number to see what color you get:" << endl; 
		//accept input for user
		cin >> color;	
		//set the color of the console output
		SetConsoleTextAttribute(hConsole, color); 
	}
	_getch();
	return 0;
}