#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
#include <string>

using namespace std;

void setConsole();


int main()
{
  setConsole();
  string arrStudents[15];
  int arrStudents_Length = 15;

  string arrOtherStudents[4][2];
  string arrOtherStudentsLastNames[4];

  int arrOtherStudents_Length = 4;
  
  arrOtherStudents[3][0] = "Tim";
  arrOtherStudents[3][1] = "L.";

  arrOtherStudents[2][0] = "Cody";
  arrOtherStudents[2][1] = "B.";

  arrOtherStudents[1][0] = "Stefan";
  

  int arrGrades[3][3] = 
  {
	  {0, 1, 2},
	  {4, 5, 6},
	  {7, 8, 9}
  };

  for (int i = 0; i < 3; i++)
  {
	  for (int j = 0; j < 3;j++)
	  {
		  cout << arrGrades[i][j] << " ";
	  }
	  cout << endl;
  }
  
	  
	  
  


  

  /*cout << "SizeOf arrOtherStudents:" << sizeof(arrOtherStudents) << endl;
  cout << "SizeOf arrOtherStudents[3]:" << sizeof(arrOtherStudents[3]) << endl;
  cout << "Length of array:" << sizeof(arrOtherStudents) / sizeof(arrOtherStudents[3]) << endl;*/

  for (int i =0; i < arrOtherStudents_Length; i++)
  {
	  cout << "Student First Name:" << arrOtherStudents[i][0] << endl;
	  cout << "Student Last Name:" << arrOtherStudents[i][1] << endl;
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