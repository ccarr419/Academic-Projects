/*
 * Author:          Christian Carreras
 * File:			server.cpp
 * Date:			03/07/2017
 * Due Date:		03/11/2017
 * Project:		#2
 * Course Num:		CSC552
 * Course Title:	Advanced Unix Programming
 * Professor:		Dr. Spiegel
 * School:		Kutztown University of Pennsylvania
 * Semester:		SPRING2017
 * About:			This file represents a server and communicates with a
 *                  client file wia pipes redirected towards stdin and stdout.
 *                  The pipe will receive messages from the client letting
 *                  the server know what commands to run. If the client sends
 *                  two floating-point numbers then a message consisting of
 *                  the sum, difference, product, and quotient of both numbers
 *                  is sent. The two numbers are then saved in a binary file
 *                  for further use. If the client sends the string 'TOTAL'
 *                  then a message holding the sum of every number entered to
 *                  to the server will be sent. Last if the client sends the
 *                  string 'EXIT' then a message comprised of every pair of
 *                  of floating point numbers is sent.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;

/// * Function Name:	toFloat
/// * Function Type:	facilitator
/// * Parameters:		string - string to turn into a float
/// * Return Value:		float - the string turned into a float
/// * \brief			This function takes a single string as an integer and
/// *				converts it into a floating-point number. Stringstreams
/// *				are used to make this conversion possible.
float toFloat(string);

/// * Function Name:	findFileSize
/// * Function Type:	facilitator
/// * Parameters:		FILE* - import only - file to find the size of
/// * Return Value:		long - the size of the file in bytes
/// * \brief			This function goes to the end of the file and counts how
/// *				many bytes are in the file which equally counts how many
/// *				characters are in the file. Once the size is found, seek
/// *				back to the beginning of the file so the server can read
/// *				the whole file if necessary.
long findFileSize(FILE*);

/// * Function Name:	findTotal
/// * Function Type:	facilitator
/// * Parameters:		char[] - import only - string carrying the numbers to add
/// * Return Value:		int - the sum of all the numbers read
/// * \brief			This function reads through the single string argument and 
/// *				separates each number contained within. Each number is 
/// *				then added to a total sum. Once the end of the file has 
/// *				been reached then the total sum calculated thus far is 
/// *				returned.
int findTotal(char[]);

/// * Function Name:	printAllNumbers
/// * Function Type:	facilitator
/// * Parameters:		char[] - import only - string carrying numbers to print
/// * Return Value:		void
/// * \brief			This function takes a single string as an argument and
/// *				separates all the numbers within the string. All the 
/// *				numbers are printed in pairs separated by a space. Each 
/// *				pair is separated by a newline. This is done until the end 
/// *				of the file is reached.
void printAllNumbers(char[]);

/// * Function Name:	printEquations
/// * Function Type:	facilitator
/// * Parameters:		string - import only - number 1 in string form
/// 					string - import only - number 2 in string form
/// * Return Value:		void
/// * \brief			This function takes two strings as arguments which will
/// *				be converted into floating-point numbers immediately.
/// *				Once floating point numbers, the server will send a message
/// *				through stdout containing the sum, difference, product,
/// *				and quotient of the two numbers. This will be seen as
/// *				four columns and two rows. First row containing the header
/// *				descriptions i.e. sum, diff, etc. and the second containing
/// *				the actual values of those operations.
void printEquations(string, string);

/// * Function Name:	writeToFile
/// * Function Type:	mutator
/// * Parameters:		string - import only - number 1 to write to file
/// 					string - import only - number 2 to write to file
/// 					FILE* - import/export - file to write to
/// * Return Value:		void
/// * \brief			This function takes three arguments. The first two
/// *				arguments are the numbers in string form to write to the 
/// *				file. The third argument is the file to write to. This 
/// *				function will write to the file in the following format:
/// *				"number *SPACE* number" by using fputs. This function
/// *				assumes that the file is created and open with write 
/// *				permissions and does not care whether it is appending, 
/// *				truncating or writing to a seeked location.
void writeToFile(string, string, FILE*);

/// * Function Name:	shutDownServer
/// * Function Type:	mutator
/// * Parameters:		FILE* - import/export - file to close
/// * Return Value:		void
/// * \brief			This function takes one file reference as an argument. It
/// *				will close the given file, close all open pipes (which will
/// *				be stdin - 0 and stdout - 1). The buffer will also be
/// *				flushed as a precautionary. This function should be the
/// *				last function called before exiting.
void shutDownServer(FILE*);

/// \file
/// * \brief			This file represents a server and communicates with a
/// *                  	client file wia pipes redirected towards stdin and stdout.
/// *                  	The pipe will receive messages from the client letting
/// *                  	the server know what commands to run. If the client sends
/// *                  	two floating-point numbers then a message consisting of
/// *                  	the sum, difference, product, and quotient of both numbers
/// *                  	is sent. The two numbers are then saved in a binary file
/// *                  	for further use. If the client sends the string 'TOTAL'
/// *                  	then a message holding the sum of every number entered to
/// *                 	to the server will be sent. Last if the client sends the
/// *                 	string 'EXIT' then a message comprised of every pair of
/// *                 	of floating point numbers is sent.
int main() {
	long lSize; //Size of the file being opened
	string num1, num2; //The numbers (or command) being sent by the server
	
	//Binary file to hold every number entered to the server ever
	//The file will be created if it does not exist and will append to the
	//end if it does. The file is open for both reading and writing if the
	//permissions exist (if it already exists prior to opening)
	FILE * nFile = fopen("Numbers.bin", "a+");
	lSize = findFileSize(nFile);	
	char buf[lSize]; //holder for reading contents of the file
	
	cin >> num1; //get first number or command
	
	//If the command entered equals "total"
	if(num1.substr(0,5) == "TOTAL") {
		//Get contents of the file and find the sum of all numbers
		fread(buf, sizeof(char), lSize, nFile);
		cout << findTotal(buf) << endl;
	}

	//If the command entered equals "exit"
	else if(num1.substr(0,4) == "EXIT") {
		//Get contents of the file and print it all in number pairs
		fread(buf, sizeof(char), lSize, nFile);
		printAllNumbers(buf);
	}
	
	//If not "total" or "exit" get another number
	else {
		cin >> num2;
		//Do basic mathematical operations on the two numbers
		printEquations(num1, num2);
		//Place the number pair in a binary file
		writeToFile(num1, num2, nFile); 
	}
	//Server is no longer needed, return system resources
	shutDownServer(nFile);
	return 0;
}

/// \details
/// * toFloat takes a single string argument to convert into a float. First the
/// * string is inserted into a stringstream for holding. Then the stream is
/// * extracted into a temporary holding floating-point number. The floating
/// * point number is then returned as the functions return value.
float toFloat(string str) {
	float temp;
	stringstream sstr;
	sstr << str;
	sstr >> temp;
	return temp;
}

/// \details
/// * findFileSize takes a single file reference as a argument. It takes the file
/// * reference and fseeks to the end of the file. From there ftell can be called
/// * to receive how many bytes are in the file. Since a char is only 1 byte, this
/// * number represents how many characters are in the file as well. Once the file
/// * size is found, fseek back to the beginning of the file for reading/writing.
long findFileSize(FILE* nFile) {
	fseek(nFile, 0, SEEK_END); //end of file
	long lSize = ftell(nFile); //returns number of bytes up to current fseek
	fseek(nFile, 0, SEEK_SET); //beginning of file
	return lSize;
}

/// \details
/// * findTotal takes a single cstring (char array) as an argument. The argument
/// * acts as a message container to search through. With the help of strtok, this
/// * function will iterate through every number in the message container with
/// * "space" being the delimiter. strtok cycles through each number until the
/// * pointer returns is NULL, meaning it has run out of numbers indicating the
/// * end of file. Each iteration the number strtok is pointing to in converted
/// * into a float and added to sum to be returned. Once every number is added to
/// * the sum then the total sum is returned.
int findTotal(char buf[]) {
	int total = 0; //Sum of all numbers
	float tempNum;
	//Return tokens in the message container with *space* as a delimiter
	//delimiter: what will separate each token (number)
	char * pch = strtok(buf, " ");	
	//pch will be NULL when it has run out of tokens to point to
	while(pch != NULL) {
		string str(pch); //Convert char* to string so toFloat can be called
		tempNum = toFloat(str); //Convert to float so it can be added
		total += tempNum;
		//Using NULL as an argument tells strtok to pick up where it left off
		pch = strtok(NULL, " ");
	}			
	return total;
}

/// \details
/// * printAllNumbers takes a single cstring (char array) as an argument. The
/// * argument acts as a message container to search through. With the help of
/// * strtok, this function will iterate through every number in the message
/// * container with "space" being the delimiter. strtok cycles through each
/// * number until the pointer returns NULL, meaning it has run out of numbers
/// * indicating the end of file. Each iteration the number strtok is pointing to
/// * is placed in a holding string until both the first number and second number
/// * are found. Once the pair are found, they are formatted on a single line and
/// * written to stdout. Then on a new line, another pair is written until every
/// * pair in the message container has been written.
void printAllNumbers(char buf[]) {
	//iterator to use as a reference for first or second number in a pair
	int i = 0; 
	//temporary holding variables
	float tempNum;
	string tempStr1 = "", tempStr2 = "";
	//Return tokens in the message container with *space* as a delimiter
	//delimiter: what will separate each token (number)
	char * pch = strtok(buf, " ");
	//pch will be NULL when it has run out of tokens to point to
	while(pch != NULL) {
		string str(pch); //convert char* to string
		//If the number is the second in the pair
		if(i % 2 != 0) {
			tempStr2 = str;
			//Format and write both numbers to stdout
			cout.width(15); cout << left << tempStr1;
			cout.width(15); cout << left << tempStr2;
			cout << endl;
		}	
		else //the number is the first of the pair
			tempStr1 = str;
		//Using NULL as an argument tells strtok to pick up where it left off
		pch = strtok(NULL, " ");
		i++; //increment the iterator to get token number
	}
}

/// \details
/// * printEquations takes two string arguments. Both string arguments are
/// * immediately converted into floats so basic mathematical operations can be
/// * performed on them. First the first row is formatted and written to display
/// * what operation the number represents. The second is formatted the same as
/// * the first but displays the results of the operation above. Everything is
/// * formatted and written to stdout independently. Every column will have a set
/// * width of 15 characters and be displayed with left justification in the
/// * column. Numbers are to be displayed with a precision of 10.
void printEquations(string num1, string num2) {
	//Convert to float for further use in operations
	float n1 = toFloat(num1);
	float n2 = toFloat(num2);
	//Write the operations use to know what the later numbers represent
	cout.width(15); cout << left << "SUM";
	cout.width(15); cout << left << "DIFF";
	cout.width(15); cout << left << "PROD";
	cout.width(15); cout << left << "QUOT";
	cout << endl;
	//Display the results of the basic mathematical operations:
	//Sum, Difference, Product, and Quotient
	cout.width(15); cout << left << setprecision(10) << n1+n2;
	cout.width(15); cout << left << setprecision(10) << n1-n2;
	cout.width(15); cout << left << setprecision(10) << n1*n2;
	cout.width(15); cout << left << setprecision(10) << n1/n2;
	cout << endl;
}

/// \details
/// * writeToFile takes two string arguments and a single file reference argument.
/// * The strings will be numbers to be inserted into the file. The numbers are
/// * written to the file individually to avoid packaging. A space character is
/// * written between the numbers and after the last number to ensure no number
/// * gets combined in the file.
void writeToFile(string num1, string num2, FILE* nFile) {
	string space = " ";
	fputs(num1.c_str(), nFile); //write num1
	fputs(space.c_str(), nFile); //write space
	fputs(num2.c_str(), nFile); //write num2
	fputs(space.c_str(), nFile); //write space
}

/// \details
/// * shutDownServer takes a single file reference argument. The file reference
/// * argument is to be closed in order to return system resources. The pipes are
/// * flushed of all contents and are closed. Since the server's pipe ends are
/// * stdin and stdout, they are closed respectively.
void shutDownServer(FILE* nFile) {
	fclose(nFile); //close file
	fflush(stdout); //flush pipe of contents
	//Close pipe ends (stdin and std out)
	close(0);
	close(1);		
}
