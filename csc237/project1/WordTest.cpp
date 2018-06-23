/**
// Author:	Christian Carreras
// File:	WordTest.cpp
// Purpose:	Thoroughly tests multiple data structures including
//		parallel arrays, classes and vectors. Also this file
//		tests those data structure by various methods such as
//		the use of an iterator or recursion.	
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "WordInfo.h"
using namespace std;

/**
// Function:	menu
// Parameters:	none
// Returns:	void
// Purpose:	Displays the menu to the user
//		after file has been located.
*/
void menu();

/**
// Function: 	openFile
// Parameters:	ifstream& - import/export
//		string& - import only
// Returns:	true if file was found
//		false if not
// Purpose:	Asks user to input a file
//		and will return a truth value
//		based on if the file was found or not
*/
bool getFile(ifstream &, string &);

/**
// Function:	options
// Parameters:	ifstream& - import only
// Returns:	only false if the user chooses to exit
// Purpose:	Selects the appropriate function
//		according to the user's choice
*/
bool options(ifstream &);

/**
// Function:	paraIt
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses parallel arrays to sort and display
//		data iteratively
*/
void paraIt(ifstream &);

/**
// Function:	paraRe
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses parallel arrays to sort and 
//		display data recursively
*/
void paraRe(ifstream &);

/**
// Function:	objectAIt
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses the WordInfo class/object to sort
//		and display data iteratively
*/
void objectAIt(ifstream &);

/**
// Function:	objectARe
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses the WordInfo class/object to sort
//		and display data recursively
*/
void objectARe(ifstream &file);

/**
// Function:	objectAPoint
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses a pointer to the WordInfo array
//		to display data recursively with the
//		help of other functions
*/
void objectAPoint(ifstream &file);

/**
// Function:	stlVecFL
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses a vector of the WordInfo type to sort
//		and display data using for loops.
*/
void stlVecFL(ifstream &);

/**
// Function:	stlVecIt
// Parameters:	ifstream& - import only
// Returns:	void
// Purpose:	Uses a vector of the WordInfo type to sort
		and display data using a vector iterator
*/
void stlVecIt(ifstream &);

/**
// Function:	openFileArray
// Parameters:	ifstream& - import only
//		string[] - import/export
//		int[] - import/export
//		string - import only
//		int& - import/export
// Returns:	void
// Purpose:	Stores the data from a file into the array
//		also calls checkDup to check for any duplicates
*/
void openFileArray(ifstream &, string[], int[], string, int&);

/**
// Function:	openFileObject
// Parameters:	ifstream& - import only
//		WordInfo[] - import/export
//		string - import only
//		int& - import/export
// Returns:	void
// Purpose:	Stores the data from a file into the array of objects
//		also calls checkDupObject to check for any duplicates
*/
void openFileObject(ifstream &, WordInfo[], string, int&);

/**
// Function:	openFileVector
// Parameters:	ifstream& - import only
// 		vector<WordInfo>& - import/export
//		WordInfo - import only
// Returns:	void
// Purpose:	Stored the data from a file into a vector of WordInfo
//		also calls checkDupVector to check for any duplicates
*/
void openFileVector(ifstream &, vector<WordInfo> &, WordInfo);

/**
// Function:	checkDup
// Parameters:	int[] - export only
//		string[] - import only
//		string - import only
//		int - import only
// Returns:	true if duplicate location found
//		false if not
// Purpose:	Checks for a duplicate location in data
//		for the functions paraIt and paraRe
*/
bool checkDup(int[], string[], string, int);

/**
// Function:	checkDupObject
// Parameters:	WordInfo[] - import/export
//		string - import only
//		int - import only
// Returns:	true if duplicate location found
//		false if not
// Purpose:	Checks for a duplicate location in data
//		for the function objectAIt, objectARe and objectAPoint
*/
bool checkDupObject(WordInfo[], string, int);

/**
// Function:	checkDupVector
// Parameters:	vector<WordInfo>& - import/export
//		WordInfo - import only
// Returns:	true if duplicate location found
//		false if not
// Purpose:	Checks for a duplicate location for a vector
//		in the function stlVecFL and stlVecIt
*/
bool checkDupVector(vector<WordInfo> &, WordInfo);

/**
// Function:	displayArray
// Parameters:	string[] - import only
//		int[] - import only
//		int - import only
//		int - import only
// Returns:	number of elements in array
// Purpose:	Displays elements of the parallel
//		arrays by the use of recursion
*/
int displayArray(string[], int[], int, int);

/**
// Function:	displayObject
// Parameters:	WordInfo[] - import only
//		int - import only
//		int - import only
// Returns:	number of elements in array
// Purpose:	Displays elements of the WordInfo
//		array by the use of recursion
*/
int displayObject(WordInfo[], int, int);

/**
// Function:	displayPointObject
// Parameters:	WordInfo* - import only
// 		int - import only
//		int - import only
// Returns:	number of elements in array
// Purpose:	Displays elements of the WordInfo
//		array by the use of pointers and recursion
*/
int displayPointObject(WordInfo*, int, int);

int main(int argc, char *argv[]) //Command-line arguments
{	ifstream inf;
	if(argc == 2) //Running the program from the command line
	{	string file = argv[1];
		if(getFile(inf, file)) //Check for file
		{	paraIt(inf); inf.close(); inf.open(file.c_str());
			cout << endl; //Close and reopen the file before every other function
			paraRe(inf); inf.close(); inf.open(file.c_str());
			cout << endl;
			objectAIt(inf); inf.close(); inf.open(file.c_str());
			cout << endl;
			objectARe(inf); inf.close(); inf.open(file.c_str());
			cout << endl;
			objectAPoint(inf); inf.close(); inf.open(file.c_str());
			cout << endl;
			stlVecFL(inf); inf.close(); inf.open(file.c_str());
			cout << endl;
			stlVecIt(inf); inf.close();
			cout << endl;
		}
		else //If the argument filename was not found
			cout << "File not found.\n";
		exit(-1);
	}
	string file;
	cout << "\nPlease enter a file: ";
	getline(cin, file);
	if(getFile(inf, file)) //If the file was found
	{	menu(); //Open menu
		bool runAgain = options(inf); //User chooses an option
		while(runAgain)
		{	inf.close();
			inf.open(file.c_str());
			menu();
			runAgain = options(inf);
		}
	}
	else //If the file was not found
		cout << "File not found.\n";
	
	return 0;
}

/**
//Displays menu to screen
*/
void menu()
{	cout << "\n1: PARALLEL ITERATIVE\n";
	cout << "2: PARALLEL RECURSIVE\n";
	cout << "3: OBJECT ARRAY ITERATIVE\n";
	cout << "4: OBJECT ARRAY RECURSIVE\n";
	cout << "5: OBJECT ARRAY POINTER RECURSIVE\n";
	cout << "6: STL VECTOR FOR LOOP\n";
	cout << "7: STL VECTOR ITERATOR\n";
	cout << "8: EXIT\n\n";
}

/**
//Lets user select one of the
//8 options from the menu
*/
bool getFile(ifstream &inf, string &file)
{	inf.open(file.c_str()); //Attempt to open the file
	if(inf.fail()) //If the file doesn't exist
		return false;
	else //If the file exists
		return true;
}

/**
//This function lets the user select an option
//and then uses a switch statement to hook up
//the code for his/her choice.
*/
bool options(ifstream &inf)
{	int answer;
	cout << "Please enter your choice: ";
	cin >> answer;
	switch(answer)
	{	case 1: //Parallel Arrays Iterative
			paraIt(inf);
			break;
		case 2: //Parallel Array Recursive
			paraRe(inf);
			break;
		case 3: //Object Array Iterative
			objectAIt(inf);
			break;
		case 4: //Object Array Recursive
			objectARe(inf);
			break;
		case 5: //Object Array Pointer-Recursive
			objectAPoint(inf);
			break;
		case 6: //STL Vector For Loop
			stlVecFL(inf);
			break;
		case 7: //STL Vector Iterative
			stlVecIt(inf);
			break;
		case 8: //Exit
			cout << "Goodbye\n";
			return false;
			break;
		default: //Error Catch
			cout << "Invalid Choice\n";
			break;
	}
	return true;
}

/**
//This function uses parallel arrays to hold and display data.
//Uses the function CheckDup to assist in duplicate data.
*/
void paraIt(ifstream &file)
{	string checkWord; //Temporary storage
	string word[10]; //Holds the words
	int count[10] = {0}; //Holds the # of times words appear
	int counter = 0;
	openFileArray(file, word, count, checkWord, counter);
	cout << "Data presented iteratively using parallel arrays:\n";
	for(int i = 0; i < counter; i++) //Display data in arrays
		cout << left << setw(15) << word[i] << count[i] << endl;
}

/**
//This function uses parallel arrays and the
//function openFileArray to hold data.
//With the help of displayArray is displays the
//data recursively.
*/
void paraRe(ifstream &file)
{	string out = "";
	string checkWord;
	string word[10];
	int count[10] = {0};
	int counter = 0;
	openFileArray(file, word, count, checkWord, counter); //Store data
	cout << "Data presented recursively using parallel arrays:\n";
	displayArray(word, count, counter, 0); //Display data
}

/**
//This function uses the WordInfo class to store information
//with the help of loops to access the data iteratively
*/
void objectAIt(ifstream &file)
{	WordInfo word[10];
	string checkWord; //Terporary storage
	int counter = 0;
	openFileObject(file, word, checkWord, counter);
	cout << "Data presented iteratively using an object array:\n";
	for(int i = 0; i < counter; i++) //Display the array of objects
		cout << word[i] << endl;
}

/**
//This funtion uses a WordInfo array to hold data.
//Then calls several functions to insert the data
//and to display the data
*/
void objectARe(ifstream &file)
{	WordInfo word[10];
	string checkWord; //Terporary storage
	int counter = 0;
	openFileObject(file, word, checkWord, counter); //Store data
	cout << "Data presented recursively using an object array:\n";
	displayObject(word, counter, 0); //Display data
}

/**
//This function uses a WordInfo array to hold data.
//Then calls several functions to insert the data
//and to display the data
*/
void objectAPoint(ifstream &file)
{	WordInfo word[10];
	string checkWord; //Terporary storage
	int counter = 0;
	openFileObject(file, word, checkWord, counter); //Store data
	cout << "Data presented recursively using pointers to an object array:\n";
	WordInfo *point = word;
	displayPointObject(point, counter, 0); //Display data
}

/**
//This function uses a vector to hold data
//then calls a function to insert the data.
//The data is displayed using a for loop
*/
void stlVecFL(ifstream &file)
{	vector<WordInfo> word; //vector of WordInfo type
	WordInfo checkWord; //Temporary object
	openFileVector(file, word, checkWord);
	cout << "Data presented with a for loop using a vector:\n";
	for(unsigned i = 0; i < word.size(); i++) //for loop to display data
		cout << word[i] << endl;
}

/**
//This function uses a vector to hold data
//then calls functions to insert and display
//the data.
*/
void stlVecIt(ifstream &file)
{	vector<WordInfo> word;
	WordInfo checkWord;
	openFileVector(file, word, checkWord);
	cout << "Data presented with an iterator using a vector:\n";
	for(vector<WordInfo>::iterator it = word.begin(); it != word.end(); ++it)
		cout << *it << endl; //Display the data using an iterator
}

/**
//This function is called by paraIt and paraRe
//it inserts the data from a file into the parallel
//arrays and checks for duplicates by calling
//the checkDup function
*/
void openFileArray(ifstream &file, string word[], int count[], string checkWord, int &counter)
{	while(file >> checkWord)
	{	if(!checkDup(count, word, checkWord, counter))
		{	if(counter < 10) //If the array is not full
			{	word[counter] = checkWord; //Put word in array
				count[counter]++; //Increment count of word
				counter++; //Increment the counter
			}
		}
	}
}

/**
//This function is called by objectAIt, objectARe and objectAPoint
//it inserts data from a file into the WordInfo array and checks
//for duplicates by call the checkDupObject function
*/
void openFileObject(ifstream &file, WordInfo word[], string checkWord, int &counter)
{	while(file >> checkWord)
	{	if(!checkDupObject(word, checkWord, counter))
		{	if(counter < 10) //If the array of object is not full
			{	word[counter].setWord(checkWord);
				word[counter]++;
				counter++;
			}
		}
	}
}

/**
//This funcion is called by stlVecFL and stlVecIt
//it inserts data from a file into the vector
//and checks from duplicates by calling the
//checkDupVector function
*/
void openFileVector(ifstream &file, vector<WordInfo> &word, WordInfo checkWord)
{	while(file >> checkWord)
	{	if(word.size() == 0) //If vector is empty
			word.push_back(checkWord);
		else //Check for duplicates
			if(!checkDupVector(word, checkWord))
				word.push_back(checkWord);
	}
}

/**
//This function checks for duplicate data using a for loop
//then returns true or false based on whether a duplicate was found.
*/
bool checkDup(int count[], string word[], string checkWord, int counter)
{	for(int i = 0; i < counter; i++)
	{	if(checkWord == word[i]) //If the word from file is already in the array
		{	count[i]++; //Increase count of word
			return true;
		}
	} //No duplicate found
	return false;
}

/**
//This function checks for duplicate data within the WordInfo
//object array, returns true or false based on results
*/
bool checkDupObject(WordInfo theWord[], string checkWord, int counter)
{	for(int i = 0; i < counter; i++)
	{	if(checkWord == theWord[i].getWord())
		{	theWord[i]++;
			return true;
		}
	} //No duplicate found
	return false;
}

/**
//This function checks for duplicate data within a vector of WordInfo
//returns true or false based on the results
*/
bool checkDupVector(vector<WordInfo> &word, WordInfo checkWord)
{	for(unsigned i = 0; i < word.size(); i++)
	{	if(checkWord.getWord() == word[i].getWord())
		{	word[i]++;
			return true;
		}
	} //No duplicate in vector
	return false;
}

/**
//This function displays the contents of parallels arrays
//by the use of recursion
*/
int displayArray(string word[], int count[], int counter, int i)
{	if(i == counter) //Display whole array
		return i;
	else
	{	cout << left << setw(15) << word[i] << count[i] << endl;
		return displayArray(word, count, counter, i+1);
	}
}

/**
//This function displays the contents of a WordInfo
//array by the use of recursion
*/
int displayObject(WordInfo word[], int counter, int i)
{	if(i == counter) //Display whole object array
		return i;
	else
	{	cout << left << setw(15) << word[i].getWord() << word[i].getCount() << endl;
		return displayObject(word, counter, i+1);
	}
}

/**
//This function displays the contents of a WordInfo
//array by the use of pointers and recursion
*/
int displayPointObject(WordInfo* word, int counter, int i)
{	if(i == counter) //Display whole object array with pointer
		return i;
	else
	{	cout << left << setw(15) << word[i].getWord() << word[i].getCount() << endl;
		return displayObject(word, counter, i+1);
	}
}
