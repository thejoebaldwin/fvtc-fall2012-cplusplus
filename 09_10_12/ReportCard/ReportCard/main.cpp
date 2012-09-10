#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

int main()
{
    //declare variable
	float score1 = .95;
	float score2 = 1;
	float score3 = 0.05;
	//calculate average
	float average = (score1 + score2 + score3) / 3;
	//store column widths in variable sow e can change them in one place
	int column1Width = 20;
	int column2Width = 10;

	//set the precision to 0 decimal places
	cout << fixed << setprecision(0);
	//set the fill character to '.'
	cout << setfill('.');
	cout << "Assignment\t\t\tScore\n";
	cout << "---------------------------------" << endl;

	cout << left << setw(column1Width) << "Hello World" 
		<< left << setw(column2Width) << score1 * 100 << "%" << endl;

	cout << left << setw(column1Width) << "Miles Calculator"
		<< left << setw(column2Width) << score2 * 100 << "%" << endl;

	cout << left << setw(column1Width) << "String Formatting"
		<< left << setw(column2Width) << score3 * 100 << "%" << endl;

	cout << "---------------------------------\n";

	//set the precision to show 5 decimal places on the average
	cout << std::setprecision(5);
	cout << left << setw(column1Width)
		<< "Average" << setw(column2Width) << average;
	//wait for a key press from the user
	_getch();
	return 0;
}