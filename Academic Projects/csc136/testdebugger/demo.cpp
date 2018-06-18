// File: Demo.cpp
// Implementation of Demo class

#include <iostream>
#include "demo.h"

using namespace std;

Demo::Demo(int tx, double ty)
{	cout << "N";
	x = tx;
	y = ty;
}

Demo::Demo(const Demo& d)
{	cout << "CC";
	x	= d.x;
	y	= d.y;
}

int Demo::getX() const
{	return(x);
}

Demo::~Demo()
{	cout << "X";
	x=0;
}

Demo Demo::operator=(const Demo &d)
{	cout << "Q";
	x	= d.x;
	y	= d.y;
	return *this;
}

Demo Demo::operator++(int)
{ 	Demo temp=*this;
	x++;
	return(temp);
}
