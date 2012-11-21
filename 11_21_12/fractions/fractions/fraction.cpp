#include <iostream>
#include "fraction.h"

fraction::fraction()
{
	Top = 1;
	Bottom = 1;
}

fraction::fraction(int fractionTop, int fractionBottom)
{
	Top = fractionTop;
	Bottom = fractionBottom;
}

double fraction::ToDouble()
{
	double result = (double) Top / (double) Bottom;
	return result;
}


//mutator
void fraction::reduce()
{
	if ((double) Bottom / (double) Top > 0)
	{
      int common = Bottom;
	  while (common > 0)
	  {
		  if ((Bottom % common == 0) && (Top % common == 0))
		  {
			  Top = Top / common;
			  Bottom = Bottom / common;
			  break;
		  }
		  common--;
	  }
	}
}

ostream& operator <<(ostream& output, fraction& val1)
{

	if (val1.Top < val1.Bottom)
	{
		output << val1.Top << "/" << val1.Bottom;
	}
	else
	{
		int whole = val1.Top / val1.Bottom;
		int remainder = val1.Top % val1.Bottom;
		output << whole << " and " << remainder << "/" << val1.Bottom;
	}

	return output;
}

fraction& operator +(fraction& val1, fraction& val2)
{
	/*int i1 = 5;
	int i2 = 6;
	int sum = i1 + i2;*/
	fraction sum;

	
	
	if (val1.Bottom == val2.Bottom)
	{
		sum.Top = val1.Top + val2.Top;
		sum.Bottom = val1.Bottom;
	}
	else
	{
		sum.Top = (val1.Top * val2.Bottom) + (val2.Top * val1.Bottom);
		sum.Bottom = val1.Bottom * val2.Bottom;
	}

	return sum;
}
