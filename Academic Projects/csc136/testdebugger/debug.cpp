// File: debug.cpp
// Application for Demo class

#include <iostream>
#include "demo.h"

using namespace std;

Demo fun(Demo tmp1, Demo &tmp2);
void quick(Demo &d);

int main()
{	Demo	d1(1);
	quick(d1);
	Demo	d2(2, 20.0);
	d1 = fun(d1,d2);
	cout << d2.getX();
	d1++;
	return(0);
}

Demo fun(Demo tmp1, Demo& tmp2)
{	cout << "*";
	tmp2 = tmp1; 
	return tmp2;
}

void quick(Demo &d)
{	cout << "R";
	Demo   quickD(d);
}
