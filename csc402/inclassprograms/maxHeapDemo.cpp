#include <iostream>
#include "arrayMaxHeap.h"
using namespace std;

int main()
{
	maxHeap<int> *myHeap;
	myHeap = new arrayMaxHeap<int>;
		
	cout << "Inserting into the heap...\n";
	
	myHeap->push(5);
	
	myHeap->push(1);
	
	myHeap->push(8);
	
	myHeap->push(7);
	
	myHeap->push(13);
	
	myHeap->push(22);
	
	myHeap->push(3);
	
	myHeap->push(15);
	
	myHeap->push(-6);
	
	myHeap->push(56);
	
	myHeap->push(101);
	
	if(myHeap->empty())
		cout << "The heap is empty\n\n";
	else
		cout << "The heap is not empty\n\n";
	
	while(!myHeap->empty())
	{
		cout << "The top element is: " << myHeap->top() << endl;
		cout << "The size of the heap is: " << myHeap->size() << endl;
		myHeap->print();
		myHeap->pop();
		cout << "Pop!\n\n";
	}
	
	cout << "The size of the heap is: " << myHeap->size() << endl;
	if(myHeap->empty())
		cout << "The heap is empty\n\n";
	else
		cout << "The heap is not empty\n\n";
	
	return 0;
}
