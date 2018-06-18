#include <iostream>
#include <iomanip>
#include "fraction.h"

using namespace std;

int main()
{	fraction f1(5, 6);
	fraction f2(7, 9);
	cout << f1 << endl << f2 << endl;
	f1+=f2;
	cout << f1 << endl; // 29/18
	f1.printImproper(); // 1u11/18
	cout << endl;
	f2-=f1; // 14/18 - 29/18
	cout << f2 << endl; // -15/18 = -5/6
	
			
	return 0;
}
