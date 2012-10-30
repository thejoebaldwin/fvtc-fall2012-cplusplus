#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;

//for larger font display
void setConsole();
void dynamicArray();


int main()
{
  //set font size and color
  setConsole();
  
  //declare for array length
  int arrLength;
  cout << "Array Length?";
  cin >> arrLength;
  cout << endl;

  //declare int pointer AND allocate new integer array of arrLength
  int *arr = new int[arrLength];

  for (int i =0; i < arrLength; i++)
  {
	  //initialize the array with the square of index
	  arr[i] = i * i;
	  cout << i << ":" << arr[i] << endl;
  }

  //allocate new integer array, length of 10 more than before
  //note: this will not destroy the old array, but arr will not point at the old array any longer
  arr = new int[arrLength + 10];

  //free up memory 
  delete[] arr;

  _getch();
  return 0;
}


//call dynamicArray in main() to test this code.
void dynamicArray()
{
  //variable for array length
  int arrLength;
  
  cout << "Please enter an array length:";
  cin >> arrLength;
  cout << endl;

  //declare a string pointer
  string *arr;
  //allocate memory for string array, point arr to address
  arr = new string[arrLength];

  for (int i = 0; i < arrLength; i++)
  {
	  //initialize and output array elements
	  arr[i] = i + 1;
	  cout << i << ":" << arr[i] << endl;
  }

  //allocate new string array in memory of 6 length
  string *tempArr = new string[6];
  //copy old arr values to new tempArr
  tempArr[0] = arr[0];
  tempArr[1] = arr[1];
  tempArr[2] = arr[2];
  tempArr[3] = arr[3];
  tempArr[4] = arr[4];
  tempArr[5] = arr[5];
  
  //arr gets pointed at new array memory address
  arr = tempArr;

  //loop through to display 6 element array copy
  for (int i = 0; i < 6; i++)
  {
	  cout << i << ":" << arr[i] << endl;
  }
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