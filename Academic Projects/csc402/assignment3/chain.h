/*
	Author:	Christian Carreras
	File:	chain.h
	About:	The chain class is a child of the linearList abstract class.
		Member functions override linearList's member functions
		through polymorphism. A chain is made up of chain nodes.
*/

#include <iostream>
#include <assert.h>
#include "chainNode.h"
#include "linearList.h"
using namespace std;

template<class T>
class chain : public linearList<T> {
	public:
		chain();
		chain(const chain<T>& theChain);
		~chain();
		bool empty() const { return listSize == 0; }
		int size() const { return listSize; }
		T& get(int theIndex) const;
		int indexOf(const T& theElement) const;
		void erase(int theIndex);
		void insert(int theIndex, const T& theElement);
		void output(ostream& out) const;
		
	protected:
		void checkIndex(int theIndex) const;
		chainNode<T>* firstNode;
		int listSize;
};

template<class T> chain<T>::chain()
{
	firstNode = NULL;
	listSize = 0;
}

template<class T> chain<T>::chain(const chain<T>& theChain)
{
	if(theChain.empty())
	{
		listSize = theChain.listSize;
		firstNode = theChain.firstNode;
	}
	else
	{
		chainNode<T> *p = firstNode;
		for(chainNode<T> *currentNode = theChain.firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		{	
			p = currentNode;
			p = p->next;
			listSize++;
		}
	}
}

template<class T> chain<T>::~chain()
{
	while(firstNode != NULL)
	{
		chainNode<T> *nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T> T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	chainNode<T> *currentNode = firstNode;
	for(int i = 0; i < theIndex; i++)
		currentNode = currentNode->next;
	return currentNode->element;
}

template<class T> int chain<T>::indexOf(const T& theElement) const
{
	chainNode<T> *currentNode = firstNode;
	int index = 0;
	while(currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		index++;
	}
	if(currentNode == NULL)
		return -1;
	else
		return index;
}

template<class T> void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T> *deleteNode;
	if(theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T> *p = firstNode;
		for(int i = 0; i < theIndex - 1;  i++)
			p = p->next;
			
		deleteNode = p->next;
		p->next = deleteNode->next;
	}
	delete deleteNode;
	listSize--;
}

template<class T> void chain<T>::insert(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	if(theIndex == 0)
		firstNode = new chainNode<T>(theElement, firstNode);
	else
	{
		chainNode<T> *p = firstNode;
		for(int i = 0; i < theIndex - 1; i++)
			p = p->next;
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}

template<class T> void chain<T>::output(ostream& out) const
{
	for(chainNode<T> *currentNode = firstNode;
	currentNode != NULL;
	currentNode = currentNode->next)
		out << currentNode->element << " ";
}

template<class T> void chain<T>::checkIndex(int theIndex) const
{
	chainNode<T> *p = firstNode;
	for(int i = 0; i < theIndex; i++)
	{
		assert(p);
		p = p->next;
	}
}

//Explicit initializers so template class knows what types it can use
template class chain<int>;
template class chain<char>;
template class chain<bool>;
template class chain<float>;
template class chain<double>;
template class chain<long>;
template class chain<string>;
