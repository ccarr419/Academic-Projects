/*
 * Author:		Christian Carreras
 * File:			client.cpp
 * Date:			03/07/2017
 * Due Date:		03/11/2017
 * Project:		#2
 * Course Num:		CSC552
 * Course Title:	Advanced Unix Programming
 * Professor:		Dr. Spiegel
 * School:		Kutztown University of Pennsylvania
 * Semester:		SPRING2017
 * About:			This file acts as client and prompts the user for input.
 *				The prompt will accept either two floating-point numbers
 *				or the words 'total' or 'exit'. All input will be written
 *				to a pipe to be received by the server. The server will
 *				process the information sent and send a message back in
 *				response. The client will then display the message from
 *				the server and start the prompt again until the user
 *				enters 'exit'. All errors dealing with read and write are
 *				being accounted for with the use of perror (stderr).
 */
 
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

/// * Function Name:	isSame
/// * Function Type:	inspector
/// * Parameters:		string - import only - string to be modified and compared
///					string - import only - string to be compared to
/// * Return Value:		bool - true if match, false if no match
/// * \brief			This function takes a two string arguments to compare.
/// *				It will convert each letter of the first string argument to 
/// *				upper case to ensure case insensitivity. If the string 
/// *				matches the second string then true is returned. If not 
/// *				false is returned. It is assumed that he second argument 
/// *				should be an all caps string and will always return false
/// *				if it is not.
/// *				
bool isSame(string, string);


/// * Function Name:	pkgNum
/// * Function Type:	facilitator
/// * Parameters:		string - import only - the first number in the package
/// 					string - import only - the second number in the package
/// * Return Value:		const char* - a cstring containing two numbers
/// * \brief			This function takes two string arguments and attempts to
/// *				package them together into a const char* value so it can
/// *				be written into a pipe. The output format will be:
/// *				"number1 *SPACE* number2"
/// *				This function also assumes that the strings are numeric in
/// *				nature and does not check the strings for correct format.
const char* pkgNum(string, string);

/// * Function Name:	readMessage
/// * Function Type:	facilitator
/// * Parameters:		int - import only -the fdes for the read end of the pipe
/// * Return Value:		bool - true if message sent, false if not
/// * \brief			This function takes the file descriptor that should be the
/// *				read end of a pipe and checks to see if the server wrote 
/// *				anything into the pipe. The message will be printed to the 
/// *				screen if it was properly received. If the message failed  
/// *				to be received an error message will be thrown through 
/// *				perror (stderr) and false will be returned. Otherwise true 
/// *				will be returned. This function assumes that the file
/// *				descriptor is the read end of a pipe.
bool readMessage(int);

/// * Function Name:	writeMessage
/// * Function Type:	facilitator
/// * Parameters:		int - import only -  the fdes for the write end of the pipe
/// 					const char* - import only - the message to be sent
/// 					size_t - import only - the size of the message to be sent
/// * Return Value:		bool - true if message sent, false if not
/// * \brief			This function takes the file descriptor that should be the 
/// *			     write end of a pipe and writes the message determined by 
/// *				the 2nd argument to the pipe. The message will be of the
/// *				size given in the 3rd argument. If the message could not be
/// *				sent an error message will be thrown through perror
/// *				(stderr) and false will be returned. Otherwise true will be
/// *				returned. This function assumes that the file descriptor
/// *				is the write end of a pipe. 
bool writeMessage(int, const char*, size_t);

/// \file
/// * \brief			This file acts as client and prompts the user for input.
/// *				The prompt will accept either two floating-point numbers
/// *				or the words 'total' or 'exit'. All input will be written
/// *				to a pipe to be received by the server. The server will
/// *				process the information sent and send a message back in
/// *				response. The client will then display the message from
/// *				the server and start the prompt again until the user
/// *				enters 'exit'. All errors dealing with read and write are
/// *				being accounted for with the use of perror (stderr).
int main(int argc, char** argv) {
	string TOTAL = "TOTAL", EXIT = "EXIT";
	string n1, n2; //Numbers (or commands) to be entered in prompt
	int fd[2]; //The pipe the client will be using
	
	fd[0] = atoi(argv[0]); //Convert to int to get the read end of pipe
	fd[1] = atoi(argv[1]); //Convert to int to get the write end of pipe
	
	//Display prompt to user once
	cout << "Enter two floating-point numbers ";
	cout << "or the words 'TOTAL' or ' EXIT'\n";
	
	cout << "> ";
	//Get only one input string to test if it's 'TOTAL' or 'EXIT' first
	cin >> n1; 
	
	if(isSame(n1, "TOTAL")) //User entered 'TOTAL' - write total to server
		writeMessage(fd[1], "TOTAL", 32);
		
	else if(isSame(n1, "EXIT")) //User entered 'EXIT' - write exit to server
		writeMessage(fd[1], "EXIT", 32);
	
	//If not total or exit then must get another number
	else {
		cin >> n2; //Get and package both numbers - write package to server
		writeMessage(fd[1], pkgNum(n1, n2), BUFSIZ);
	}
	
	sleep(1);	//Sleep to prevent race conditions
	readMessage(fd[0]+1); //Get message from server if any
	
	//Close pipe ends since we are done here
	close(fd[0]+1);
	close(fd[1]);
     return 0;
}

/// \details
/// * isSame will take a two strings as arguments. It will iterate through the 
///* first string turning every letter to upper case. Once the string has been 
/// * converted to all upper case then it will be compared to the second string. 
/// * If the strings match then the function will return true. If not then false 
/// * will be returned. This function ensures a case-insensitive comparison.
/// * This function also assumes that both strings are numeric and the second
/// * string is all upper case.
bool isSame(string str1, string str2) {
	//Go to each letter in str1 and make it upper case
     for(int i = 0; i < str1.length(); i++)
          str1[i] = toupper(str1[i]);
     if(str1 == str2)
          return true; //strings match
     else
          return false; //strings do not match
}

/// \details
/// * pkgNum takes two string arguments and places them inside on const char*.
/// * A stringstream is used to make the conversion. The first string is stream
/// * inserted into the stringstream followed by a space and the second string 
/// * argument. The string stream is converted into string and placed inside a 
/// * temporary holding string. The temporary string is then converted into a 
/// * cstring and returned.
const char* pkgNum(string num1, string num2) {
	stringstream str;	
	str << num1;
	str << " ";
	str << num2;
	string temp = str.str();
	return temp.c_str();
}

/// \details
/// * readMessage takes a single integer argument that represents the file
/// * descriptor of the pipe end to read out of. First a message holder of the
/// * max size allowed in the system-buffer will be made. Then a message, if one
/// * exists will be place inside the message holder. The message will then be
/// * printed to the screen. If the message failed to be received then an error
/// * message will be printed through perror (stderr) and false will be returned.
/// * Otherwise true will be returned.
bool readMessage(int fd) {
	//Create a static message container of the max size the buffer can hold
	static char message[BUFSIZ];
	//Read from pipe and place it in the message container
	if(read(fd, message, BUFSIZ) != -1) {
		cout << message;
		fflush(stdout); //Get everything out of the pipe
	}
	else {
		perror("Message failed to be received\n");
		return true;
	}
	return false;
}

/// \details
/// * writeMessage will take three arguments. The first argument is the file
/// * descriptor which represents the pipe end the client will write to. The
/// * second argument is the message to be written to the pipe. The third is the
/// * size of the message to be sent. A message of the size buf will then be
/// * constructed and sent to the file descriptor pipe end. If the message was
/// * not send then an error message will be printed through perror (stderr) and
/// * false will be returned. Otherwise true will be returned.
bool writeMessage(int fd, const char* message, size_t buf) {
	//Write into the pipe to communicate with he server
	if(write(fd, message, buf) != -1) 
		fflush(stdout); //Get everything out of the pipe
			
	else {
		perror("Message failed to be sent\n");
		return false;
	}
	return true;
}
