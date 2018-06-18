/*
	Author:	Christian Carreras
	File:	chainDemo.cpp
	About:	Tests every aspect of the chain class.
*/

#include <iostream>
#include "chain.h"
using namespace std;

int main()
{
	//Constructor checks
	linearList<int> *myList;
	myList = new chain<int>;
	cout << "New chain created.\n";
	
	//empty function check
	if(myList->empty())
		cout << "The chain is empty.\n";
		
	//insert function check
	myList->insert(0, 5);
	myList->insert(1, 18);
	myList->insert(2, 64);
	myList->insert(3, 12);
	myList->insert(4, 128);
	
	//output function check
	cout << "Chain now contains: ";
	myList->output(cout);
	
	//size function check
	cout << "\nChain size: " << myList->size() << endl;
	
	//get function check
	cout << "Element at index 0 is: " << myList->get(0) << endl;
	cout << "Element at index 1 is: " << myList->get(1) << endl;
	cout << "Element at index 2 is: " << myList->get(2) << endl;
	cout << "Element at index 3 is: " << myList->get(3) << endl;
	cout << "Element at index 4 is: " << myList->get(4) << endl;
	
	//indexOf function check
	cout << "The index of 128 is: " << myList->indexOf(128) << endl;
	cout << "The index of 12 is: " << myList->indexOf(12) << endl;
	cout << "The index of 64 is: " << myList->indexOf(64) << endl;
	cout << "The index of 18 is: " << myList->indexOf(18) << endl;
	cout << "The index of 5 is: " << myList->indexOf(5) << endl;
	
	//insert into list at beginning, end and middle check
	myList->insert(0, 43);
	myList->insert(6, 90);
	myList->insert(2, 27);
	cout << "Chain now contains: ";
	myList->output(cout);
	cout << "\nChain size: " << myList->size() << endl;
	
	//erase function check at beginning, end and middle
	//myList->erase(0); //Seg Fault?
	myList->erase(7);
	myList->erase(2);
	cout << "Chain now contains: ";
	myList->output(cout);
	cout << "\nChain size: " << myList->size() << endl;
	
	//copy constructor test
	//correct syntax needed
	//linearList<int> *copyList;
	//copyList = new chain<int>(*myList);
	
	return 0;
	//Destructor check upon program end
}