#include "box.h"


using namespace std;



 void box::setWidth(int width)
 {
   _width = width;
 }

 string box::toString()
 {
	 string output;

	 for (int i = 0; i< _width; i++)
	 {
		 for (int j = 0; j < _width;j++)
 		 {
			output = output + '*';  
    	 }
		 output = output + '\n';
	 }
	 return output;
 }


 box::box()
 {
	 _width = 5;
 }

 box::box(int width)
 {
	 _width = width;
 }


//                <<      cout          b;

 ostream& operator<<(ostream &os, const box &b)
 {
	 //os << "HI THERE";
	 for (int i = 0; i< b._width; i++)
	 {
		 for (int j = 0; j < b._width;j++)
 		 {
			os << '*';  
    	 }
		 os << '\n';
	 }

	 return os;
 }

