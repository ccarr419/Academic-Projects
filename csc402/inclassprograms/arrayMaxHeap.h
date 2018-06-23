#include <iostream>
#include "maxHeap.h"
using namespace std;

template<class T>
class arrayMaxHeap : public maxHeap<T>
{	private:
		T* root;
		int heapSize;
		int arrayLength;
		
		void changeArrayLength(int);
		int getParentIndex(int theIndex) {return theIndex/2;}
		int getLeftChildIndex(int theIndex) {return theIndex*2;}
		int getRightChildIndex(int theIndex) {return theIndex*2+1;}
	
	public:
		arrayMaxHeap();
		
		bool empty() const {return heapSize == 0;}
		int size() const {return heapSize;}
		
		void push(const T& theKey);
		T pop();
		T top() const;
		void heapify(T*);
		void print() const;
};

template<class T>
arrayMaxHeap<T>::arrayMaxHeap()
{
	heapSize = 0;
	arrayLength = 10;
	root = new T[arrayLength];
}

template<class T>
void arrayMaxHeap<T>::push(const T& theKey)
{
	if(heapSize-1 == arrayLength)
		changeArrayLength(2*arrayLength);
	
	if(empty())
	{
		root[heapSize+1] = theKey;
		heapSize++;
		return;
	}
	
	root[heapSize+1] = theKey;
	heapSize++;
	int theIndex = heapSize;	
	
	while(theIndex > 1)
	{
		int parentIndex = getParentIndex(theIndex);
		if(root[theIndex] < root[parentIndex])
			break;
		
		else
		{
			swap(root[theIndex], root[parentIndex]);
			theIndex = parentIndex;
		}		
	}
}

template<class T>
T arrayMaxHeap<T>::pop()
{
	if(size() == 1)
	{
		heapSize--;
		return NULL;
	}
	
	root[1] = root[heapSize];
	heapSize--;
	
	int theIndex = 1;
	while(theIndex < heapSize/2+1)
	{
		int leftChildIndex = getLeftChildIndex(theIndex);
		int rightChildIndex = getRightChildIndex(theIndex);
		
		if(root[theIndex] < root[leftChildIndex] 
		&& root[leftChildIndex] > root[rightChildIndex])
		{
			swap(root[theIndex], root[leftChildIndex]);
			theIndex = leftChildIndex;
		}
		
		else if(root[theIndex] < root[rightChildIndex] 
		&& root[rightChildIndex] > root[leftChildIndex])
		{
			swap(root[theIndex], root[rightChildIndex]);
			theIndex = rightChildIndex;
		}
		
		else
			break;
	}
	
	return theIndex;
}

template<class T>
T arrayMaxHeap<T>::top() const
{	return root[1]; }

/*template<class T>
void arrayMaxHeap<T>::heapify(T* theKey)
{
	
}*/

template<class T>
void arrayMaxHeap<T>::changeArrayLength(int newLength)
{
	T* tmp = new T[newLength];
	copy(root+1, root+heapSize, tmp);
	arrayLength = newLength;
	delete [] root;
	root = tmp;
}

template<class T>
void arrayMaxHeap<T>::print() const
{
	for(int i = 1; i <= heapSize; i++)
		cout << root[i] << ' ';
	cout << endl;
}

template class arrayMaxHeap<int>;
