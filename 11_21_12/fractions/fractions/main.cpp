#include <iostream>
#include <string>
#include <conio.h>
#include "fraction.h"
using namespace std;


int main()
{
	fraction f1(13,29);
	fraction f2(5,20);
	fraction f3 = f1 + f2;
	cout << "Fraction1: " << f1 << "=" << f1.ToDouble() << endl;
	cout << "Fraction2: " << f2 << "=" << f2.ToDouble() << endl;
	cout << "Fraction3: " << f3 << "=" << f3.ToDouble() << endl;

	f2.reduce();
	cout << "f2 Reduced to:" << f2 << endl;

	f1.reduce();
	cout << "f1 Reduced to:" << f1 << endl;

	f3.reduce();
	cout << "f3 Reduced to:" << f3 << endl;

	_getch();
	return 0;
}