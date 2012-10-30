#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;

void setConsole();
double convertToKilometers(double Miles);
void outputGrades(float arrGrades[], int length);
void clearInput();












void calculate(float price, int &fives, int &ones, int &quarters, int &nickels, int &pennies)
{

}





int main()
{
  setConsole();
  float grades[] = {99, 88.7, 36, 54, 0, 77, 99, 101, 34};

  float grades2[100];

 /* float gradesLength = 6;*/

  int length = sizeof(grades) / sizeof(grades[0]);
  cout << "OUTSIDE FUNCTION CALL" << endl;
  cout << "sizeof array:" << sizeof(grades) << endl;
  cout << "sizeof array[0]:" << sizeof(grades[0]) << endl;
  cout << "length:" << length << endl << endl << endl;
 
  
  outputGrades(grades, length);
  
  cout << "ELEMENT 0 = " << grades[0] << endl;
  

  clearInput();
  //cout << quizzes[4];
  
  _getch();


  return 0;
}

void outputGrades(float arrGrades[], int length)
{
  float sum = 0;
   cout << "INSIDE FUNCTION CALL" << endl;
  cout << "sizeof array:" << sizeof(arrGrades) << endl;
  cout << "sizeof array[0]:" << sizeof(arrGrades[0]) << endl;

  for (int i = 0; i < length; i++)
  {
	  cout <<"Grade #" << i + 1 << ":" << arrGrades[i];
	  cout << endl;
	  sum += arrGrades[i];
  }
  cout << "Total Grades:" << sum << endl;
  arrGrades[0] = 999999;
}

double convertToKilometers(double Miles)
{
   Miles = Miles * 1.256;
   return Miles;
}


void clearInput()
{
	  char c = '0';
  while (c != 'q')
  {
	double inputMiles = 4.5;
	cout << " Kilometers:" << convertToKilometers(inputMiles);
	cout << " Input Miles:" << inputMiles;
	cout << endl;
	cout << "Press Any Key To Continue, 'q' to Quit";
	cin.clear();
	cin.ignore(1024, '\n');
	cin >> c;
  }
  _getch();

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