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

   PCONSOLE_FONT_INFOEX font = new CONSOLE_FONT_INFOEX();
   font->cbSize = sizeof(CONSOLE_FONT_INFOEX);
   
   //CONSOLE_FONT_INFOEX is defined in some windows header
    GetCurrentConsoleFontEx(hConsole, false, font);
	//PCONSOLE_FONT_INFOEX is the same as CONSOLE_FONT_INFOEX*
    font->dwFontSize.X = 10;
    font->dwFontSize.Y = 18;
    
	

        //SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, lpConsoleCurrentFontEx);


	
	
	SetCurrentConsoleFontEx(hConsole, false, font);
    //SetConsoleTextAttribute(hConsole, color); 
    //SetConsoleTextAttribute(hConsole, 0x0C);




	//while (color < 255)
	//{
	//	cout << "Using Color:" << color << endl; 
	//	//accept input for user
	//	//cin >> color;	
	//	color++;
	//	//set the color of the console output
	//	SetConsoleTextAttribute(hConsole, color); 
	//}
	SetConsoleTextAttribute(hConsole, 240); 
		
		
	cout << font->FaceName << endl;

	cout << "hello";
	_getch();
	return 0;
}