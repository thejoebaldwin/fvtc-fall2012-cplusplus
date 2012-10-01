#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;

int getSum(int num1, int num2, int num3);
int getSum(int num1, int num2);
int getSum(int num1, int num2, int num3, int num4);
int getSum(int num1, int num2, int num3, int num4, int num5);
double getSumDouble(int num1, int num2, int num3);
void setConsole();



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



int getSum(int num1, int num2)
{
	return getSum(num1, num2, 0);
}

int getSum(int num1, int num2, int num3)
{
	return num1 + num2 + num3;
}

double getSumDouble(int num1, int num2, int num3)
{
	return getSum(num1, num2, num3);
}

int getSum(int num1, int num2, int num3, int num4)
{
	return getSum(num1, num2, num3) +  num4;
}

int main()
{
	setConsole();
	int inputNum1 = 0;
	int inputNum2 = 0;
	int inputNum3 = 0;
	cout << "Please enter in the first number to add:";
	cin >> inputNum1;
	cout << endl << "Please enter the second number to add:";
	cin >> inputNum2;
	cout << endl << "Please enter the third number to add:";
	cin >> inputNum3;
	int total = getSum(inputNum1, inputNum2, inputNum3);
	cout << endl << "The sum is: " << total;

	
	
	_getch();
	return 0;
}



