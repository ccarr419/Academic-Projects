/* Author:		Christian Carreras
*  File:		p1.cpp
*  Date Made:	02/13/2017	
*  Due Date:	02/17/2017
*  School:		Kutztown University
*  Class Num:	CSC 552
*  Class Name:	Advanced Unix Programming
*  Semester:	SPRING 2017
*  Professor:	Dr. Spiegel
*  Purpose:		Project 1 simulates a shell by taking command-line arguments
*				containing the names of two programs to execute and a file to
*				read. The first program will count the total number of words 
*				contained within that file and return that value. The second 
*				program will print the first n words in the file where n is 
*				value returned by the first program.
*/

/*
 * Function Name: 	beginProcess
 * Function Type: 	facilitator
 * Arguments:     	char** - input only
 * Return Value:  	int - the number of words printed
 * Purpose:      	Begins the process of forking and executing the programs
 *					supplied by the command-line.
 */
int beginProcess(char**);

/*
 * Function Name: 	makeExec
 * Function Type: 	facilitator
 * Arguments:     	const char* - input only
 * Return Value:  	const char* - the new executable
 * Purpose:       	Adds the necessary './' to the given file name to ensure
 *					it executes in a exec command.
 */
const char* makeExec(const char*);

/*
 * Function Name: 	toCString
 * Function Type: 	facilitator
 * Arguments:     	int - input only
 * Return Value:  	const char* - new argument suitable for an exec command.
 * Purpose:       	Converts an integer to a const char* value for exec use.
 */
const char* toCString(int);

/*
 * Function Name: 	waitOnProcess
 * Function Type: 	inspector
 * Arguments:     	int - input/output
 * Return Value:  	int - the number returned by the processing being waited on
 * Purpose:       	Makes the parent process wait until its child process has 
 *					terminated. Once its child process havs terminated, get the 
 *					return value of the child and return it.
 */
int waitOnProcess(int&);

#include <iostream>
#include <sstream>
#include <sys/wait.h>

using namespace std;
int main(int argc, char* argv[])
{
	cout << "Words Printed: " << beginProcess(argv) << endl;
	return 0;
}
	
int beginProcess(char** argv)
{
	int status, wordCount = 0;
	const char* exec1 = argv[1]; //program#1
	const char* exec2 = argv[3]; //program#2
	const char* file = argv[2]; //file to count words
	
	//Fork a process to count the total words in a file
	if(fork() == 0) //If child
		execvp(makeExec(exec1), argv+1);

	else //If parent
	{
		wordCount = waitOnProcess(status);
		//Fork another process to print n words in a file
		if(fork() == 0) //If child
		{
			/* This next line of code is very perculiar and I have no
			understanding as to why it is so important. Without it the next
			program fails to get the correct arguments and will return 0;
			With it it will function correctly and give appropriate output.
			I feel as though I am overlooking something dealing with the
			nature of const char* variables but it is still very odd. It seems
			that the last argument before NULL in execlp will be "./" if not
			for the next line of code. I will leave it for now until I can
			find out why these lines of code react in such a way...*/
			cout << makeExec(exec2) << toCString(wordCount) << endl;
			
			execlp(makeExec(exec2), exec2, file, toCString(wordCount), NULL);
		}
		
		else //If parent
			wordCount = waitOnProcess(status);
	}
	return wordCount;
}

//Take the program name and add "./" to make it usable in exec functions.
const char* makeExec(const char* exe)
{
	string suf = "./";
	string temp = suf + exe;
	return temp.c_str();
}

//Convert an int to a cString to make it usable in exec functions.
const char* toCString(int num)
{
	stringstream str;
	str << num;
	string temp = str.str();
	return temp.c_str();
}

//Have a partent process wait until its child has terminated then return
//the child's return value.
int waitOnProcess(int &status)
{
	wait(&status);
	return WEXITSTATUS(status);
}
