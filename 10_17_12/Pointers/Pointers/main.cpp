#include <iostream>
#include <conio.h>
#include <iomanip>
//need for shell color on windows machine
#include <Windows.h>
using namespace std;

void setConsole();
void outputVariableInfo(int &variable);
void pointer1();
void pointer2();

void pointer1()
{
   int primeNumber = 7;
  outputVariableInfo(primeNumber);
  primeNumber = 11;
  outputVariableInfo(primeNumber);
  int *primeNumberPointer;
  primeNumberPointer = &primeNumber;
  cout << "Prime Number Pointer Value:" << primeNumberPointer <<endl;
  cout << "Primer Number Pointer Target Value:" << *primeNumberPointer << endl;
  *primeNumberPointer = 13;
   outputVariableInfo(primeNumber);

}

void pointer2()
{
	int grade1 = 99;
  int *pointerGrade1;
  pointerGrade1 = &grade1;

  //address of grade 1
  cout << "grade1 value:" << grade1 << endl;
  //value of grade 1
  cout << "grade1 address:" << &grade1 << endl;
  //value of pointer Grade 1
  cout << "pointerGrade1Value:" << pointerGrade1 <<endl;
  //value what pointer Grade 1 is pointing to
  cout << "what pointerGrade1 is pointing to value:" << *pointerGrade1 << endl;

  int *pointer2 = &grade1;
  int *pointer3 = &grade1;
  *pointer2 = 45;
  *pointer3 = 77;
  cout << "pointer2:" << *pointer2 << endl;
  
  cout << "size of pointer2:" << sizeof(string*) << endl;
  cout << sizeof(string);

}

void outputVariableInfo(int &variable)
{
  cout << "address:" << &variable << endl;
  cout << "value:" << variable << endl;
}

int main()
{
  setConsole();
  

  int arrPrime[] = {3, 5, 7, 11, 13, 17, 23};
  int primeNumber = 23;
  int *primePointer = &primeNumber;
  
  int primeLength = 7;
  //for loop to output each arrPrime number here
  for (int i = 0; i < 15; i++)
  {
	  cout << "Prime #" << i << ":" << primePointer[i] << endl;
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