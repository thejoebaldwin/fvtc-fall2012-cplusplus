#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	char first, last;
	cin >> first;
	cin.ignore(256, ' ');
	cin >> last;
	cout << "Your input was " << first << " " << last << endl;
	_getch();


	return 0;
}
