#include <iostream>

using namespace std;


template <class elt> 
class arrayList{
	private:
		elt *element; // all items are int type
		int listSize; // number of elements in array
		int arrayLength; // capacity of the 1D array
	
	public:
		//constructor
		arrayList();
		arrayList(int);
//		arrayList(arrayList &);
		~arrayList(){delete [] element;}
		
		int size() const{return listSize;}
		int length() const {return arrayLength;}
		bool empty() const {return listSize==0;}
		
		void add(const elt&); //add new item at end of the arrayList
		 // insert new item at the specific position
		void insert(int theIndex, const elt &theElement);
		// remove the item fro the specific position
		void erase(int theIndex);
		// find the index of the element
		int indexOf(elt &theElement) const;
		// get the item at the index
		int get(int theIndex) const;
		void output(ostream &out) const;
		
	private:
		//change 1D array length
		void changeArrayLength(int);
		bool checkIndex(int) const;
};

//Constructor
arrayList::arrayList<elt>()
{
    element = new elt;
    listSize = 0;
    arrayLength = 10;
}

//Constructor w/ set array length
arrayList::arrayList(int length)
{
	element = new elt;
	listSize = 0;
	arrayLength = (length > 0 ? length : 10);
}

//Add an element to the array
void arrayList::add(const elt theElement)
{
	if(size() < length())
	{
		element[listSize] = theElement;
		listSize++;
	}
}

//Insert an element into the array at a specific index
void arrayList::insert(int theIndex, const elt &theElement)
{
	if(theIndex >= 0 && theIndex < length())
	{
		if(checkIndex(theIndex))
		{
			erase(theIndex);
			element[theIndex] = theElement;
		}
		else
		{
			element[theIndex] = theElement;
		}
		listSize++;
	}
	else
		return;
}

//Erase an element from the array according to its index
void arrayList::erase(int theIndex)
{
	element[theIndex] = NULL;
	listSize--;
}

//Return the index of the given element
int arrayList::indexOf(elt &theElement) const
{
	for(int i = 0; i < length(); i++)
		if(element[i] == theElement)
			return i;
	return -1;
}

//Return the element at the given index
int arrayList::get(int theIndex) const
{
	if(checkIndex(theIndex))
		return element[theIndex];
	else
		return -1;
}

//Output the whole array
void arrayList::output(ostream &out) const
{
	for(int i = 0; i < length(); i++)
	{
		if(checkIndex(i))
		{
			out << get(i);
			out << " ";
		}
	}
}

//Change the array length
void arrayList::changeArrayLength(int newLength)
{
	if(newLength > 0)
	{
		if(newLength < length())
		{	for(int i = newLength-1; i < length()-1; i++)
			{	erase(i); }
		}
		arrayLength = newLength;
	}			
}

//Check to see if there is an element at the given index
bool arrayList::checkIndex(int theIndex) const
{
	if(element[theIndex] != NULL)
		return true;
	else
		return false;
}

int main()
{
	arrayList list(5);
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	list.output(cout);
	cout << endl;
	list.insert(4, 9);
	list.insert(2, 75);
	list.insert(0, 13);
	list.output(cout);
	cout << endl;
	list.erase(4);
	list.erase(1);
	list.output(cout);
	cout << endl;
	return 0;
}
