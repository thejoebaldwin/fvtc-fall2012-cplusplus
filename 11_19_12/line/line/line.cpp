#include <conio.h>
#include <iostream>
#include "line.h"
#include <string>
using namespace std;

    //default constructor
    line::line()
	{
		_width = 5;
		_height = 1;
	}

	line::line(int w, int h)
	{
		_width = w;
		_height = h;
	}


	void line::setHeight(int h)
	{
		//limit the height to 100
		if (h < 100)
		{
		 _height = h;
		}
		else
		{
		 _height = 100;
		}
	}
	void line::setWidth(int w)
	{
		_width = w;
	}
	string line::toString()
	{
		string output;
		//?
		for (int i = 0; i < _height; i++)
		{
			for (int j = 0; j < _width; j++)
			{
              output = output + "*";
			}
			output = output + '\n';
		}
		return output;
	}
