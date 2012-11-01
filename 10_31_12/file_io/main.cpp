#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
//need this to work with files
#include <fstream>
#include <string>
using namespace std;

void setConsole();

int main()
{
  //large font
  setConsole();
  
  //declare output file stream
  ofstream writeFile;
  //open file
  writeFile.open("example.txt");
  //write to file using <<
  writeFile << "Hello World\n";
  writeFile << "Writing to a text file\n";
  //close file
  writeFile.close();

  //declare input file stream object (same one we just wrote to)
  ifstream readFile ("example.txt");
  //test to make sure the file is open
  if (readFile.is_open())
  {
	  //while there is more file
	  while (readFile.good())
	  {
		  string lineContent;
		  //read the line contents into our string variable
		  getline(readFile, lineContent);
		  //out the string contents to the console
		  cout << lineContent << endl;
	  }
	  //close the file here (in the else it's not open because something went wrong)
	  readFile.close();
  }
  else
  {
	  cout << "There was a problem with opening the file" << endl;
  }
  //pause on user input
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