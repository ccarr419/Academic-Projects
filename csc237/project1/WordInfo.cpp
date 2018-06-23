/**
// Author: 	Christian Carreras
// File:	WordInfo.cpp
// Purpose:	The cpp file for the WordInfo class.
//		Implements the code to retrieve data
//		private members with gets and change those
//		members with sets. Operators are also used
//		for easier access to private members.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "WordInfo.h"
using namespace std;

//Constructor
WordInfo::WordInfo(string wrd, int cnt)
{	setWord(wrd);
	setCount(cnt);
}

//User can set the value for word
void WordInfo::setWord(string wrd)
{	word = wrd;
}

//User can set the value for count
void WordInfo::setCount(int cnt)
{	count = cnt;
}

//User can get the value for word
string WordInfo::getWord() const
{	return word;
}

//User can get the value for count
int WordInfo::getCount() const
{	return count;
}

//Increments count by one
void WordInfo::operator++(int)
{	count++;
}

//Stream extraction operator
//Sets word from file and sets count to one
ifstream &operator>>(ifstream &file, WordInfo &W)
{	string word;
	file >> word;
	W.setWord(word);
	W.setCount(1);
	return file;
}

//Stream insertion operator
//Displays class object to screen 
ostream &operator<<(ostream &out, const WordInfo &W)
{	out << left << setw(15) << W.getWord() << W.getCount();
	return out;
}
