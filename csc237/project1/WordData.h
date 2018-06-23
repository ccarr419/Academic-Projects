/***************************************
 *    File:    WordData.h              *
 *    Prepared by: Dr. Spiegel         *
 *                                     *
 ***************************************/

#ifndef WORDDATA_H
#define WORDDATA_H
#include <iostream>
#include <string>

using namespace std;

class WordData {
	
public:

	//Constructor
	WordData(string wrd = "", int cnt = 0);

	//Sets
	void setWord(string wrd);
	void setCount(int cnt);

	//Set Whole WordData Object
	void setWordData(string,int);

	//Gets
	string getWord() const;
	int getCount() const;

	//Increment
	void incCount(int amt = 1);

private:

	//variables
	string word;
	int count;


};

#endif
