/**
// Author:	Adam Tal
// Updated By:	Dr. Spiegel and Christian Carreras
// Course:	CSC 237
// Filename:	WordData.cpp
// Purpose:	Container of a word and its multiplicity
*/
#ifndef WORDDATA_H
#define WORDDATA_H
#include <iostream>
#include <string>

using namespace std;

class WordData {

 public:
        /**
	// Function Name:	Constructor
	// Member Type:		Constructor
	// Parameters:		string - import only
	//			int - import only
	// Returns:		N/A
	// Purpose:		Constructs the WordData object
	*/
        WordData(string wrd = "", int cnt = 1);

        /**
	// Function Name:	setWord
	// Member Type:		Mutator
	// Parameters:		string - import only
	// Returns:		void
	// Purpose:		Sets the word for the WordData object
	*/
        void setWord(string wrd);
	
	/**
	// Function Name:	setCount
	// Member Type:		Mutator
	// Parameters:		int - import only
	// Returns:		void
	// Purpose:		Sets the count for the WordData object
	*/
        void setCount(int cnt);

        /**
	// Function Name:	setWordData
	// Member Type:		Mutator
	// Parameters:		string - import only
	//			int - import only
	// Returns:		void
	// Purpose:		Sets the word and count for the WordData object
	*/
        void setWordData(string,int);

        /**
	// Function Name:	getWord
	// Member Type:		Inspector
	// Parameters:		none
	// Returns:		string
	// Purpose:		Returns the value of WordData's word
	*/
        string getWord() const;
	
	/**
	// Function Name:	getCount
	// Member Type:		Inspector
	// Parameters:		none
	// Returns:		int
	// Purpose:		Returns the value of WordData's word
	*/
        int getCount() const;

        /**
	// Function Name:	incCount
	// Member Type:		Mutator
	// Parameters:		int
	// Returns:		void
	// Purpose:		Increments count by one
	*/
        void incCount(int inc = 1);
	
	/**
	// Function Name:	< operator
	// Member Type:		Facilitator
	// Parameters:		const WordData& - import only
	// Returns:		true if less than
	//			false if not
	// Purpose:		Checks if the WorData is less than another based
	//			on string compare
	*/
	bool operator <(const WordData &) const;
	
	/**
	// Function Name:	> operator
	// Member Type:		Facilitator
	// Parameters:		const WordData& - import only
	// Returns:		true if greater than
	//			false if not
	// Purpose:		Checks if the WorData is greater than another based
	//			on string compare
	*/
	bool operator >(const WordData &) const;
	
	/**
	// Function Name:	== operator
	// Member Type:		Facilitator
	// Parameters:		const WordData& - import only
	// Returns:		true if equal to
	//			false if not
	// Purpose:		Checks if the WorData is equal to another based
	//			on string compare
	*/
	bool operator ==(const WordData &) const;

 private:

        //variables
        string word;
        int count;

};

/**
// Function Name:	<< operator
// Parameters:		ostream& - import/export
//			const WordData& - import only
// Returns:		ostream
// Purpose:		Prints a WordData object to the screen
*/
ostream &operator<<(ostream& output, const WordData &words);

#endif
