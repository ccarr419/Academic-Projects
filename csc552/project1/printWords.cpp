/* Author:     	Christian Carreras
*  File:       	printWords.cpp
*  Date Made:	02/13/2017	
*  Due Date:	02/17/2017
*  School:      Kutztown University
*  Class Num:	CSC 552
*  Class Name:	Advanced Unix Programming
*  Semester:	SPRING 2017
*  Professor:	Dr. Spiegel
*  Purpose:     This program opens a file given through the command-line and
*               prints the first occuring number of words specified by the
*               other command-line argument.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/*
 * Function Name: 	printWords
 * Function Type: 	facilitator
 * Arguments:     	char** - input only
 * Return Value:  	int - the number of words written
 * Purpose:       	Opens the file entered in the command-line and prints the
 *                	first n specified words in order.
 */
int printWords(char**);

using namespace std;
int main(int argc, char* argv[])
{
	return printWords(argv);
}

//Attempts to open the file and print the choosen amount of words. 
//Close the file once done.
int printWords(char** argv)
{
	string tempString; //Temporarily holds the string given by the input stream
	ifstream inf; //The input file
	//The number of words to print and number of words printed.
	int count = 0, numWords = 0;

	count = atoi(argv[2]); //Convert the argv char* to int
	inf.open(argv[1]);
	//Loop while you still have words to print and not end of file
	while(inf >> tempString && count--)
		cout << ++numWords << ":\t" << tempString << endl;
	inf.close();
	//Returns the selected number of words in the file.
	return numWords;
}
