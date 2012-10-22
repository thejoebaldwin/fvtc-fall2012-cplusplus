#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
#include <string>
#include <ctype.h>

using namespace std;

void setConsole();

const string SECRET_WORD = "hello world";

int main()
{
  
	

  setConsole();
  string test = "hello world";

  string firstName = "rick";
  string lastName = "jones";
  //string wholeName = firstName + ' ' + lastName;
  cout << firstName + ' ' + lastName << endl;

  cout << "length of firstName:" << firstName.length() << endl;
  cout << "size of firstName:" << firstName.size() << endl;
  cout << "sizeOf firstName:" << sizeof(firstName) << endl;

  
  string emptyTest;
  //cout << "Am I empty?" << emptyTest.empty() << endl;
  if (emptyTest.length() == 0)
  {
	  cout << "I am Empty!" << endl;
  }
  else
  {
	  cout << "NOT Empty!" << endl;
  }


  //string compare
  cout << "compare:" << test.compare(SECRET_WORD) << endl;

  if (test == SECRET_WORD)
  {
	  cout << "I am Equal!" << endl;
  }
  else
  {
	  cout << "NOT EQUAL" << endl;
  }

  //search word for another word

  size_t findIt = test.find("hot dog");
  cout << "test contains \"world\"" << int(findIt) << endl;

  //same thing
  cout << "test contains \"world\"" << int(test.find("hot dog")) << endl;

  float f = 12.345678;
  int i = int(f);
  cout << "testing cast" << i << endl;

  //substring
  cout << "first part of test:" << test.substr(0, 5) << endl;

   

  //case sensitivity, tolower
   string compareMe1 = "NAME";
   string compareMe2 = "name";

   for (int i =0; i < compareMe1.length(); i++)
   {
	   compareMe1[i] = toupper(compareMe1[i]);
   }

   for (int i =0; i < compareMe2.length(); i++)
   {
	   compareMe2[i] = tolower(compareMe2[i]);
   }

   if (compareMe1.compare(compareMe2) == 0)
   {
	   cout << "We ARE EQUAL";
   }
   else
   {
	   cout << "NOT EQUAL";
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