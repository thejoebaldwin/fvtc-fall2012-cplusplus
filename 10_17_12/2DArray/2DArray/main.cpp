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



  int arrSales[2][3] = {  9, 67, 23,
	                      890, 456, 890 };

  int arrSales2[2][3] = {
	  {9, 56, 77},
	  {890, 44, 90}
  };

  int arrTotalSales[2][3];
  
  arrTotalSales[0][0] = arrSales[0][0] + arrSales2[0][0];

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