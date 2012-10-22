#include <iostream>
#include <string>
#include <conio.h>

using namespace std;
int main()
{
 string test = "Hello World";
 string *testPointer;
 testPointer = &test;
 cout << "value of testPointer:" << testPointer << endl;
 cout << "value at testPointer address:" << *testPointer << endl;

 cout << "at testpointer[0]:" << testPointer[3] << endl;

 _getch();



 return 0;
}