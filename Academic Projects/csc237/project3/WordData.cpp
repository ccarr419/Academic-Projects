/**
// Author:	Adam Tal
// Updated By:	Dr. Spiegel and Christian Carreras
// Course:	CSC 237
// Filename:	WordData.cpp
// Purpose:	Implementations of member functions for
//		designed to contain a word and its
//		multiplicity in data
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "WordData.h"

using namespace std;

/**
//Constructor
*/
WordData::WordData(string wrd, int cnt)
{
        setWordData(wrd, cnt);
}

/**
//Sets the given string as the word
*/
void WordData::setWord(string wrd)
{
        word = wrd;
}

/**
//Sets the given int as the count
*/
void WordData::setCount(int cnt)
{
        count = cnt;
}

/**
//Sets the WordData object with the given string and int
*/
void WordData::setWordData(string wrd, int cnt)
{
        setWord(wrd);
        setCount(cnt);
}

/**
//Returns WordData's word
*/
string WordData::getWord() const
{
        return(word);
}

/**
//Returns WordData's count
*/
int WordData::getCount() const
{
        return(count);
}

/**
//Increments WordData's count by one
*/
void WordData::incCount(int inc)
{
        count+=inc;
}

/**
//Checks if the WordData object is less than another
*/
bool WordData::operator<(const WordData &w) const
{	string baseWord = getWord();
	string checkWord = w.getWord();
	if(baseWord.compare(checkWord) < 0)
		return true; //First word is less than the other
	else
		return false;
}

/**
//Checks if the WordData object is greater than another
*/
bool WordData::operator>(const WordData &w) const
{	string baseWord = getWord();
	string checkWord = w.getWord();
	if(baseWord.compare(checkWord) > 0)
		return true; //First word is greater than the other
	else
		return false;
}

/**
//Checks if the WordData object is equal to another
*/
bool WordData::operator==(const WordData &w) const
{	string baseWord = getWord();
	string checkWord = w.getWord();
	if(baseWord == checkWord)
		return true; //Words are equal
	else
		return false;
}

/**
//Prints the WordData object to the screen
*/
ostream &operator<<(ostream& output, const WordData &words)
{
  output<<words.getWord()<<"\t\t"<<words.getCount();
  return output;
}
