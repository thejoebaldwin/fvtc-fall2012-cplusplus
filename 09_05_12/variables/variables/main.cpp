#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	//declare variables
	int numberOne = 5;
	int numberTwo = 6;
	int total = 0;
	//display greeting message
	cout << "******************************************\n";
	cout << "*Welcome to the static number calculator!*\n";
	cout << "******************************************\n";
	//show the two numbers that we are adding
	cout << "\tWe are adding 5 and 6 together today.\n\n";
	//calculate the two numbers added
	total = numberOne + numberTwo;
	//display the total
	cout << "The total is:";

	cout << total;
	//output goodbye/press any key message
	cout << "\n\nThank you! Press any key to exit.";
	getch();
	return 0;
}