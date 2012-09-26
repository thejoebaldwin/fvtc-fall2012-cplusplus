#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
#include <string>


using namespace std;

void initFont()
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



bool isNumber(char c)
{
bool isNumeric = false;
	switch(c)
	{
		case '0':
			isNumeric = true;
			break;
		case '1':
			isNumeric = true;
			break;
		case '2':
			isNumeric = true;
			break;
		case '3':
			isNumeric = true;
			break;
		case '4':
			isNumeric = true;
			break;
		case '5':
			isNumeric = true;
			break;
		case '6':
			isNumeric = true;
			break;
		case '7':
			isNumeric = true;
			break;
		case '8':
			isNumeric = true;
			break;
		case '9':
			isNumeric = true;
			break;
	}
	return isNumeric;
}


int main()
{
  initFont();
  bool isNotQuit = true;

  while (isNotQuit)
  {
	string myString = "hello world";

	cout << "Please enter a whole number, q to quit:";
	cin >> myString;
	cout << "You entered in: " << myString << endl;
	
	bool isNumeric = true;

	for (int i = 0; i < myString.length(); i++)
	{
		char c = myString[i];
		if (isNumber(c) == false)
		{
		  isNumeric = false;
		}
	}
	
	if (isNumeric)
	{
		cout << "IS A NUMBERRR!!!"<< endl;
	}
	else
	{
		cout << "Not a number."<< endl;
	}

	



	if (myString == "q")
	{
		isNotQuit = false;
	}

  }

  

  _getch();
  return 0;
}


