#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

bool isNumeric(string s);
bool isInteger(string s);
int toInteger(string s);
int toFloat(string s);
int charToInt(char c);

int main()
{
	cout << "Please enter a number:";
	string s;
	getline(cin, s);
	cout << "isInteger? :" << isInteger(s) << endl;
	if (isInteger(s))
	{
		cout << "toInteger ?:" << toInteger(s) << endl;
	}
	else
	{
		cout << "isNumeric? :" << isNumeric(s) << endl;
	}
	_getch();
	return 0;
}


bool isInteger(string s)
{
    bool isOK = true;
	for (int i = 0; i < s.length(); i++)
	{
		char c = tolower(s[i]);
		if (c != '0' && c!= '1'	&& c!= '2'	&& c!= '3'
			&& c!= '4' && c!= '5' && c!= '6' && c!= '7'
			&& c!= '8'	&& c!= '9')
		{
			isOK = false;
			break;
		}
	}
	return isOK;
}
bool isNumeric(string s)
{
	bool isOK = true;
	if (s.length() > 0 && (s[0] == '.' || s[s.length() -1] == '.'))
	{
		isOK = false;
	}
	else
	{
		int periodCount = 0;
		for (int i = 0; i < s.length(); i++)
	{
		char c = tolower(s[i]);
		if (c != '0' && c!= '1'	&& c!= '2'	&& c!= '3'
			&& c!= '4' && c!= '5' && c!= '6' && c!= '7'
			&& c!= '8'	&& c!= '9' && c!= '.')
		{
			isOK = false;
			break;
		}
		else
		{
			if (s[i] == '.')
			{
				periodCount++;
				if (periodCount > 1)
				{
					isOK = false;
					break;
				}
			}
		}
	}
	}
	return isOK;
}



int toInteger(string s)
{
	//no error checking, call isInteger first!
	int result = 0;
	if (s.length() == 1 && s[0] == '0')
	{
		//do nothing
	}
	else
	{
		int multiplier = 1;
		
		for (int i = s.length() - 1; i >= 0; i--)
		{
			int base = charToInt(s[i]);
			result += base * multiplier;
			multiplier *= 10;
		}
	}
	return result;
}
int toFloat(string s)
{
	//TODO
	return 0;
}

int charToInt(char c)
{
	int result;
	switch (c)
	{
		case '0':
			result = 0;
			break;
		case '1':
			result = 1;
			break;
		case '2':
			result = 2;
			break;
		case '3':
			result = 3;
			break;
		case '4':
			result = 4;
			break;
		case '5':
			result = 5;
			break;
		case '6':
			result = 6;
			break;
		case '7':
			result = 7;
			break;
		case '8':
			result = 8;
			break;
		case '9':
			result = 9;
			break;
	}
	return result;
}