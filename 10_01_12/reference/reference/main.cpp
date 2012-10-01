#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;


void setConsole();
int sumValue(int num1, int num2);
int sumReference(int &num1, int &num2);

int main()
{
    setConsole();
	int input1 = 100;
	int input2 = 200;
	int total = sumValue(input1, input2);
	cout << "input1:" << input1 << " input2:" << input2 << " total:" << total << endl;
	total = sumReference(input1, input2);
	cout << "input1:" << input1 << " input2:" << input2 << " total:" << total << endl;


	cout << "hello";
	_getch();
	return 0;
}


int sumValue(int num1, int num2)
{
 num1 = num1 + num2;
 return num1;
}

int sumReference(int &num1, int &num2)
{
	num1 = num1 + num2;
	return num1;
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
		
		
	

}