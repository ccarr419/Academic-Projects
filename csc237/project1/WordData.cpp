/***************************************
 *    File:    WordData.cpp            *
 *    Prepared by: Dr. Spiegel         *
 *                                     *
 ***************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "WordData.h"

using namespace std;


WordData::WordData(string wrd, int cnt)
{
	setWordData(word, count);	
}

void WordData::setWord(string wrd)
{
	word = wrd;
}

void WordData::setCount(int cnt)
{
	count = cnt;
}

void WordData::setWordData(string wrd, int cnt)
{
	setWord(wrd);
	setCount(cnt);
}

string WordData::getWord() const
{
	return(word);
}

int WordData::getCount() const
{
	return(count);
}

void WordData::incCount(int amt) 
{
	setCount(getCount()+amt);
}

