/* Author:  	Christian Carreras
*  File:       	countWords.cpp
*  Date Made:	02/13/2017	
*  Due Date:	02/17/2017
*  School:      Kutztown University
*  Class Num:	CSC 552
*  Class Name:	Advanced Unix Programming
*  Semester:	SPRING 2017
*  Professor:	Dr. Spiegel
*  Purpose:     This program opens a file given through the command-line and
*               counts how many words are in the file. It will return the
*               number of words that were in the file.
*/

#include <iostream>
#include <fstream>
#include <string>

/*
 * Function Name: 	countTotalWords
 * Function Type: 	facilitator
 * Arguments:     	char** - input only
 * Return Value:  	int - the number of words in the file
 * Purpose:       	Opens the file entered in the command-line and counts all
 *                	the words in the file.
 */
int countTotalWords(char**);

using namespace std;
int main(int argc, char* argv[])
{
	return countTotalWords(argv);
}

//Attempts to open the file and count all the words. Close the file once done.
int countTotalWords(char** argv)
{
	string tempString; //Temporarily holds the string given by the input stream
	ifstream inf; //The input file
	int wordCounter = 0;

	inf.open(argv[1]);
	//Loop until the end of the file
	while(inf >> tempString)
		wordCounter++;
	inf.close();
	//Returns the number of words in the file.
	return wordCounter;
}
