#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;

void setConsole();

int main()
{
    setConsole();

	for (int i = 0; i < 5; i++) cout << "hello" <<endl;
	if (1 == 1) cout << "DONT NEED EM" << endl;

	int testMe = 5;
	switch(testMe)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
	

	for (int i = 0; i < 5;i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << i << j <<endl;
		}
	}


	int option = 5;
	if (option == 2)
	{
		cout << "You selected option 2" << endl;
	}
	else
	{
		cout << "Goodbye" << endl;
	}


	_getch();
	return 0;
}


void setConsole()
{
	  //color value for console
	int color = 25;  
	//console reference	
	HANDLE	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//this will loop until either 0 is entered, or a non-numeric value

   PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX();
   font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
   
   //CONSOLE_FONT_INFOEX is defined in some windows header
    GetCurrentConsoleFontEx(hConsole, false, font);
	//PCONSOLE_FONT_INFOEX is the same as CONSOLE_FONT_INFOEX*
    font->dwFontSize.X = 10;
    font->dwFontSize.Y = 18;

	SetCurrentConsoleFontEx(hConsole, false, font);
    
	SetConsoleTextAttribute(hConsole, 240); 

}