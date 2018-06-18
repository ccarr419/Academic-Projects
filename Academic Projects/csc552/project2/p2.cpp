/// \mainpage
/// \author			Christian Carreras
/// \date				03/07/2017 (SPRING2017)
/// \brief 			CSC552: Advanced Unix Programming, 
///					Kutztown University of Pennsylvania
/// \details			This project aims to replicate a client/server environment
/// *				by using concurrent processes and IPC mechanisms.
/// *				The client and server will each have their separate process
/// *				as well as their own read and write ends from two separate
/// *				pipes. To start, two pipes are created and then a second
/// *				process is forked to separate the client and server. The
/// *				client is the parent process and the server is the child.
/// *				Each process will close the pipe ends that they will never
/// *				use. The server will redirect its pipe ends to stdin and
/// *				stdout and then exec while the client will send the file
/// *				descriptors for the pipe ends being used as arguments in
/// *				the exec function. All errors with pipes, forks, and execs
/// *				are being accounted for with the use of perror (stderr).


/*
 * File:			p2.cpp
 * Due Date:		03/11/2017
 * Project: 		#2
 */
 
#include <iostream>
#include <cstdio>
#include <sstream>
#include <sys/wait.h>
using namespace std;

/// * Function Name:	makeExec
/// * Function Type:	facilitator
/// * Parameters:		const char* - import only - executable name
/// * Return Value:		const char* - ready to be used argument for exec
/// * \brief			This function takes a single argument of const char* and 
/// *				returns a similar const char* with the exception being './' 
/// *				precedes the argument value. This is necessary for proper 
/// *				execution in a Unix environment. Without this addition to 
/// *				an executable name, every exec function will fail.
const char* makeExec(const char*);

/// * Function Name:	toCString
/// * Function Type:	facilitator
/// * Parameters:		int - import only - number to become cstring
/// * Return Value:		const char* - ready to be used argument for exec
/// * \brief			This function takes a single argument of int and returns
/// *				the equivalent in const char*. This is necessary in order
/// *				to pass the int value as a argument in any exec function.
/// *				In this project it is used to pass pipe ends to a process
/// *				so that process can send and receive information through
/// *				a single or numerous pipes.
const char* toCString(int);

/// * Function Name:	parentProcess
/// * Function Type:	mutator
/// * Parameters:		int[] - import/export - pipe 1
///					int[] - import/export - pipe 2
/// * Return Value:		void
/// * \brief			This function will be called by the parent process after
/// *				the fork. It will close any unused pipe ends in the two 
/// *				given arguments, create any necessary arguments to pass 
/// *				through exec and then finally call exec thus running the 
/// *				client executable.
void parentProcess(int[], int[]);


/// * Function Name:	childProcess
/// * Function Type:	mutator
/// * Parameters:		int[] - import/export - pipe 1
///					int[] - import/export - pipe 2
/// * Return Value:		void
/// * \brief			This function will be called by the child process after
/// *				the fork. It will close any unused pipe ends in the two 
/// *				given arguments, create any necessary arguments to pass 
/// *				through exec and then finally call exec thus running the 
/// *				server executable.
void childProcess(int[], int[]);

/// \file
/// * \brief			This project aims to replicate a client/server environment
/// *				by using concurrent processes and IPC mechanisms.
/// *				The client and server will each have their separate process
/// *				as well as their own read and write ends from two separate
/// *				pipes. To start, two pipes are created and then a second
/// *				process is forked to separate the client and server. The
/// *				client is the parent process and the server is the child.
/// *				Each process will close the pipe ends that they will never
/// *				use. The server will redirect its pipe ends to stdin and
/// *				stdout and then exec while the client will send the file
/// *				descriptors for the pipe ends being used as arguments in
/// *				the exec function. All errors with pipes, forks, and execs
/// *				are being accounted for with the use of perror (stderr).
int main() {
	pid_t isParent; //Easily differentiate between child and parent process
	//File descriptors to use for pipe creation
	int client2Server_fd[2];
	int server2Client_fd[2];
	
	//Variables to hold arguments for exec functions
	const char *client, *server, *cRead, *cWrite;	
	
	//Create the client to server pipe
	//Client will have the write end and the server will have the read end
	if(pipe(client2Server_fd) == -1) {
		perror("Pipe Error -- Client to Server pipe could not be created\n");
		return 0;
	}
	
	//Create the server to client pipe
	//Server will have the write end and the client will have the read end
	if(pipe(server2Client_fd) == -1) {
		perror("Pipe Error -- Server to Client pipe could not be created\n");
		return 0;
	}
	
	//Fork a second process and get the pid of both processes to easily
	//determine if it is the child or the parent
	isParent = fork();
	if(isParent) {	
		parentProcess(client2Server_fd, server2Client_fd);
		perror("Parent exec failed\n"); //Should only fire if exec failed
	}
	//If the process is the child
	else if(isParent == 0) {
		childProcess(client2Server_fd, server2Client_fd);
		perror("Child exec failed\n"); //Should only fire if exec failed
	}
	//If it is not the parent or the child then the fork failed
	else {
		perror("Fork Error -- could not fork another process\n");
	}
	
	return 0;
}
/// \details
/// * makeExec takes a single const char* argument named exec and concatenates
/// * with the string value "./" It then returns the cstring equivalent of that
/// * concatenation. i.e the result will look like this: "./exe"
/// * This function should be used with every exec function to ensure that it
/// * works properly in a Unix environment.
const char* makeExec(const char* exe)
{
	string suf = "./"; //Unix's way of opening an executable
	string tempStr = suf + exe;
	return tempStr.c_str();
}

/// \details
/// * toCString takes a single int argument which is to be turned into a const
/// * char * value. Stringstream will be used to correctly transfer the int value
/// * into a cstring. The int value is put into the stringstream using stream
/// * insertion. A temporary string will then hold the string equivalent of the
/// * string stream. The temporary string is then turned into the cstring
/// * equivalent and returned.
const char* toCString(int num)
{
	stringstream sstr;
	sstr << num;
	string tempStr = sstr.str();
	return tempStr.c_str();
}

/// \details
/// * The parent process will implement the client side of the project. First all
/// * unused pipe ends will be closed by using the array parameters given. Then
/// * the client executable will be be transformed into the correct format so
/// * exec can use it properly. Lastly the pipe ends that will be used will be
/// * transformed into const char* so they can be used as arguments in the exec.
void parentProcess(int c2s[], int s2c[]) {
	const char *client, *cRead, *cWrite;
	//Close unused pipe ends
	close(c2s[0]);
	close(s2c[1]);
	//Create arguments for exec
	client = makeExec("client");		
	cRead = toCString(s2c[0]);
	cWrite = toCString(c2s[1]);
	//Exec to client process
	execlp(client, cRead, cWrite, NULL);
}

/// \details
/// * The child process will implement the server side of the project. First all
/// * usused pipe ends will be closed by using the array parameters given. Then 
/// * the pipe ends that will be used will be redirected towards stdin and stdout 
/// * since the server will only communicate with the client. The redirection is 
/// * done by the dup2 function. Lastly the server executable will be transformed 
/// * into the correct format so exec can use it properly. 
void childProcess(int c2s[], int s2c[]) {
	const char *server;
	//Close unused pipe ends
	close(s2c[0]);		
	close(c2s[1]);
	dup2(c2s[0], 0); //Redirect to stdin
	dup2(s2c[1], 1); //Redirect to stdout
	server = makeExec("server"); //Create argument for exec
	execlp(server, NULL);
}
