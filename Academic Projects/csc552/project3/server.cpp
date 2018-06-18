/*
Author:		Christian Carreras
Filename:		server.cpp
Course:		CSC 552
About:		This project creates a real-time message server where clients
			are allowed to sign-on and message each other. All information
			about the clients and the server is location in shared memory
			and is updated accordingly.
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/mman.h>

using namespace std;

/* acad Internet address, defined in /etc/hosts */
// This is the new acad's IP address
#define SERV_HOST_ADDR "156.12.127.18"
#define BUFF_SIZE 128 //Maximum message buffer size
#define MAX_CLI_SIZE 25 //Maximum number of clients allowed on the server
#define USRNAME_SIZE 20 //Maximum username length
#define TIME_FSIZE 13 //Length of the time format string

//Server log flags
#define STD_MES 0 //Standard message
#define F_CSER 1 //Child server forked
#define T_CSER 2 //Child server terminated
#define M_SENT 3 //Message sent
#define USR_IN 4 //User logged in
#define USR_OUT 5 //User logged out
#define UNK_OUT 6 //Unknown user terminated
#define M_FAIL 7 //Message failed to send

//MES is a basic message packet to send between server and clients
typedef struct {
	long mtype;
	long number; //A number if one needs to be sent
	char username[USRNAME_SIZE]; //sender's username
	char recipient[USRNAME_SIZE]; //recipient's username
	char letter[BUFF_SIZE]; //The message
	struct sockaddr_in addr; //Address of the sender/recipient
} MES;

//A struct for the LookUpTable to contain user information
typedef struct {
	int sfd; //initial file descriptor for log out information
	bool inUse; //tells if the current slot in the table is being used
	struct sockaddr_in address; //address of the client
	char name[USRNAME_SIZE]; //username of the client
	char startTime[TIME_FSIZE]; //time the client logged in
	char lastLookUp[TIME_FSIZE]; //time the client was last looked up
} client_info;

//LookUpTable in shared memory which holds information on all active users
typedef struct {
	client_info client[MAX_CLI_SIZE];
	int numClients;
} sharedMemory;

sharedMemory* startShm(struct sockaddr_in);
void getTime(char[]);
void userExistsPrompt(int);
void serverFullPrompt(int);
void unkownUserPrompt(int, char[]);
void senIsRecpPrompt(int);
void messageStsPrompt(int, int);
void printAllUsers(int, sharedMemory*);
void sLog(int f=0, int n=0, char m[]=NULL, char u[]=NULL, char r[]=NULL);
void setSharedMem(int, int, sharedMemory*, sockaddr_in&, char[], char[]);
int logInHandler(int, int, int&, sharedMemory*, struct sockaddr_in&);
int mesHandler(int, int, int, sharedMemory*);
int lookUpServerChild(int, int, sockaddr_in&, sharedMemory*);
int startStrmSoc(struct sockaddr_in&, int);
int startDgrmSoc(struct sockaddr_in&, int);
int logUserIn(int, int, sharedMemory*, char[], sockaddr_in&);
int logUserOut(int, sharedMemory*);
int testUser(int, sharedMemory*, char[]);
int compareCaseIns(string, string);
int findUser(char[], sockaddr_in&, sharedMemory*);
int sendMessage(int, int, MES&, sharedMemory*);

main(int argc,char *argv[]) {	
	struct sockaddr_in cli_addr, serv_addr;
	int sfd, nfd, clilen, numfork = 0;
	int SERV_TCP_PORT = 15030;
	sharedMemory *shm;
	
	//Create a stream socket to listen for requests from clients
	if((sfd = startStrmSoc(serv_addr, SERV_TCP_PORT)) == -1)
		return 0; //the socket failed to be created
		
	shm = startShm(serv_addr); //Create the shared memory space
	
	cout << "Please run the program client now.\n";
	
	while(1) {	
		clilen = sizeof(cli_addr);
		//Wait until a new client tries to connect
		if((nfd = accept(sfd, (struct sockaddr *) &cli_addr,
			(socklen_t *) &clilen)) < 0)
		{	cout << "server: accept error\n"; return 0; }		
		
		//Fork a new child process to handle all the client's needs
		sLog(F_CSER, ++numfork);
		bool isParent = fork();
		if(!isParent) {
			if(!lookUpServerChild(nfd, numfork, cli_addr, shm))
			{	return 0; } //The client terminated/logged off
		}			
	}	
}

//Creates the shared memory space by using mmap
//mmap automatically cleans up when done
sharedMemory* startShm(struct sockaddr_in serv_addr) {
	int size = sizeof(sharedMemory *); //size to allocate in shared memory
	sharedMemory *shm = (sharedMemory *) mmap(&serv_addr, size, 
		PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	//Initilize all rows in shared memory to be not in use
	for(int i = 0; i < MAX_CLI_SIZE; i++) shm->client[i].inUse = false;
	shm->numClients = 0; //should be no clients yet
	return shm;
}

//Returns the formatted local time (origin of the server "EDT") in a c_str()
void getTime(char timestr[]) {
	time_t rawtime;
	time(&rawtime);
	struct tm* currentTime = localtime(&rawtime);
	//turn into string of hh:mm:ss 'timezone' in 24H format
	strftime(timestr, TIME_FSIZE, "%H:%M:%S %Z", currentTime);
}

//Send a message to the client saying the username they picked exists already
void userExistsPrompt(int fd) {
	MES out_mes;
	out_mes.number = htonl(-1);
	strncpy(out_mes.letter, "Username exists already.", 
		sizeof(out_mes.letter));
	write(fd, &out_mes, sizeof(MES));
}

//Send a message to the client saying the server is at capacity
void serverFullPrompt(int fd) {
	MES out_mes;
	out_mes.number = htonl(-1);
	strncpy(out_mes.letter, "Server is at capacity. Try again later.", 
		sizeof(out_mes.letter));
	write(fd, &out_mes, sizeof(MES));
}

//Send a message to the client saying the user they looked up does not exist
void unkownUserPrompt(int fd, char user[]) {
	MES out_mes;
	strncpy(out_mes.username, "s", sizeof(out_mes.username));
	strncpy(out_mes.letter, "The user, \"", sizeof(out_mes.letter));
	strcat(out_mes.letter, user);
	strcat(out_mes.letter, "\" does not exist.");
	write(fd, &out_mes, sizeof(MES));
}

//Send a message to the client saying the user they looked up was themselves
void senIsRecpPrompt(int fd) {
	MES out_mes;
	strncpy(out_mes.username, "s", sizeof(out_mes.username));
	strncpy(out_mes.letter, "Cannot send a message to yourself. Stop.", 
		sizeof(out_mes.letter));
	write(fd, &out_mes, sizeof(MES));
}

//Send a message to the client stating if their message sent or not
void messageStsPrompt(int sts, int fd) {
	MES out_mes;
	strncpy(out_mes.username, "s", sizeof(out_mes.username));
	if(sts != -1) {
		strncpy(out_mes.letter, "Message sent", sizeof(out_mes.letter));
		write(fd, &out_mes, sizeof(MES));
	}
	else {
		strncpy(out_mes.letter, "Message failed to send", 
			sizeof(out_mes.letter));
		write(fd, &out_mes, sizeof(MES));
		sLog(M_FAIL);
	}
}

//Make a list of all current users in sharedMemory and send to the client
void printAllUsers(int fd, sharedMemory *shm) {
	MES m_out;
	sprintf(m_out.letter, "(%d", shm->numClients);
	strcat(m_out.letter, ") USERS\n");
	strcat(m_out.letter, "--------------\n");
	for(int i = 0; i < MAX_CLI_SIZE; i++) {
		if(shm->client[i].inUse) {
			if(strlen(m_out.letter) >= BUFF_SIZE - USRNAME_SIZE) {
				write(fd, &m_out, sizeof(MES));
				strcpy(m_out.letter, "");
			}
			else {
				strcat(m_out.letter, shm->client[i].name);
				strcat(m_out.letter, "\n");
			}
		}	
	}
	write(fd, &m_out, sizeof(MES));
}

//Print log information to the server screen
//Use flags to use predetermined log messages
void sLog(int flg, int num, char mes[], char usr[], char recp[]) {
	char tstr[TIME_FSIZE];
	getTime(tstr);
	cout << "(" << tstr << ") ";
	switch(flg) {
		case 0:
			cout << "Server: " << mes << endl;
			break;
		case 1:		
			cout << "Forking new lookup server child " << num << ".\n";
			break;
		case 2:
			cout << "Terminating lookup server child " << num << ".\n";
			break;
		case 3:
			cout << "Message sent from " << usr << " to " << recp << ": ";
			cout << mes << endl;
			break;
		case 4:
			cout << usr << " logged in.\n";
			break;
		case 5:
			cout << usr << " logged out.\n" ;
			break;
		case 6:
			cout << "Unknown user terminated.\n";
			break;
		case 7:
			cout << "Failed to write message.\n";
			break;
		default:
			cout << "\n";
	}
}

//Initialize the free space in shared memory to the client's information
//Assumes that the space is free (or else information will be overriden)
void setSharedMem(int s, int fd, sharedMemory* shm, sockaddr_in &addr, 
		char usr[], char tstr[]) {
	shm->client[s].sfd = fd;
	shm->client[s].inUse = true;
	shm->client[s].address = addr;
	strncpy(shm->client[s].name, usr, sizeof(shm->client[s].name));			
	strncpy(shm->client[s].startTime, tstr, sizeof(shm->client[s].startTime));
	strncpy(shm->client[s].lastLookUp, tstr, sizeof(shm->client[s].lastLookUp));
}

//Attempts to log the client into the server. If the username picked exists
//or the server is at capacity, the user will be informed. Otherwise their
//information will be put into sharedMemory and they will be allowed to
//send messages and see shared memory data
int logInHandler(int fd, int num, int &PORT, sharedMemory *mem, 
		struct sockaddr_in &addr) {
	MES tmp;
	int slot;
	//Check if the user logs outs before logging in
	if(read(fd, &tmp, sizeof(MES)) <= 0) {
		logUserOut(fd, mem);
		sLog(T_CSER, num);
		return 0;
	}
	
	//Check if username exists or server is at capacity
	slot = testUser(fd, mem, tmp.username);
	PORT += slot; //Unique port for the client
	logUserIn(fd, slot, mem, tmp.username, addr);			
	mem->numClients++;
	return 1;
}

//Receives a message from the client and determines which course of action to
//take. Either sending a message to another client or releasing requested info
int mesHandler(int sfd, int dfd, int num, sharedMemory *shm) {
	MES tmp;
	//Check if the user logged out
	if(read(sfd, &tmp, sizeof(MES)) <= 0) { 	
		logUserOut(sfd, shm);
		shm->numClients--;
		sLog(T_CSER, num);
		return 0;
	}
	
	//Null-terminate message just in case
	tmp.letter[strlen(tmp.letter)] = '\0';
	string recipient = tmp.recipient;
	//Check if the client requested to see all active users
	if(recipient.compare("a") == 0)
		printAllUsers(sfd, shm);
	else //Otherwise send a message to the specified user
		sendMessage(dfd, sfd, tmp, shm);
	return 1;
}

//Handles all child lookUpServer duties after the fork
int lookUpServerChild(int nfd, int num, sockaddr_in &addr, sharedMemory *shm) {
	int CLI_TCP_PORT = 15225;
	//Attempt to log user in. If they logout, terminate
	if(!logInHandler(nfd, num, CLI_TCP_PORT, shm, addr))
	{	return 0; }
	
	//Set up a datagram for use in client2client messaging
	int dgrmfd = startDgrmSoc(addr, CLI_TCP_PORT);			
	
	//Once logged in, wait for messages and respond until the client logs off
	while(1) {
		if(!mesHandler(nfd, dgrmfd, num, shm))
		{	return 0; }
	}
}

//Create a stream socket for server2client communication
int startStrmSoc(struct sockaddr_in &addr, int PORT) {
	int sockfd;
	/* create a socket which is one end of a communication channel */
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{	cout << "server: cannot open stream socket\n"; return -1; }

	/* initialize server address */
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET; /* address family: Internet */
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* accept a connection on any Internet interface */
	addr.sin_port = htons(PORT); /* specify port number */

	/* associate server address with the socket */
	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{	cout << "server: cannot bind local address\n"; return -1; }

	/* specify the queue size of the socket to be 5 */
	if(listen(sockfd, MAX_CLI_SIZE) < 0)
	{	cout << "server: listen error\n"; return -1; }
	
	return sockfd;
}

//Create a datagram socket for client2client communication
int startDgrmSoc(struct sockaddr_in &addr, int PORT) {
	int sockfd;
	/* create a socket which is one end of a communication channel */
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{	cout << "server: cannot open dgram socket\n"; return -1; }
	
	return sockfd;
}

//Log the client in and attempt to get their address for use in datagrams
//Assumes the client has met all the necessary preconditions to be logged in
int logUserIn(int fd, int s, sharedMemory *shm, char usr[], 
		sockaddr_in &addr) {
	MES out_mes, tmp;
	char tstr[TIME_FSIZE];
	out_mes.number = htonl(s);
	if(write(fd, &out_mes, sizeof(MES)) == -1)
		return 0;
		
	if(read(fd, &tmp, sizeof(MES)) == -1)
		return 0;
		
	addr = tmp.addr;
	setSharedMem(s, fd, shm, addr, usr, tstr);
	sLog(USR_IN, 0, NULL, usr);
	return 1;
}

//Logs a user out and resets their space in shared memory to not being in use
int logUserOut(int fd, sharedMemory *shm) {
	char timestr[TIME_FSIZE];
	getTime(timestr);
	for(int i = 0; i < MAX_CLI_SIZE; i++) {
		if(fd == shm->client[i].sfd) {	
			sLog(USR_OUT, 0, NULL, shm->client[i].name);
			shm->client[i].inUse = false;
			return 1;
		}
	}
	sLog(UNK_OUT);
	return 0;
}

//Tests if the username given exists in shared memory or if the server is full
int testUser(int fd, sharedMemory *shm, char usr[]) {
	int fslot = -1;
	string testMESname = usr;
	for(int i = 0; i < MAX_CLI_SIZE; i++) {
		string testMMname = shm->client[i].name;
		if(shm->client[i].inUse) {
			//Check if the username exists already
			if(compareCaseIns(testMESname, testMMname)) {
				userExistsPrompt(fd);
				return -1;
			}
			if(i == MAX_CLI_SIZE-1) { //Check if server is full
				serverFullPrompt(fd);
				return -1;
			}
		}
		//Save free slot until it is made sure the username does not exist
		else { fslot = (fslot == -1 ? i : fslot); }
	}
	return fslot;
}

//Compares two strings without case-sensitivity
int compareCaseIns(string str1, string str2) {
	for(int i = 0; i < str1.length(); i++) {
		if(isalpha(str1[i]))
			str1[i] = tolower(str1[i]); 
	}
	for(int j = 0; j < str2.length(); j++) {
		if(isalpha(str2[j]))
			str2[j] = tolower(str2[j]); 
	}
	if(str1.compare(str2) == 0) return 1;
	else return 0;
}

//Find the current slot in shared memory the user resides in
//If the user does not exist, return -1
int findUser(char usr[], sockaddr_in &addr, sharedMemory* mem) {
	string testMESusr = usr;
	for(int i = 0; i < MAX_CLI_SIZE; i++) {
		string testMMname = mem->client[i].name;			
		if(mem->client[i].inUse) {
			if(compareCaseIns(testMESusr, testMMname)) {
				addr = mem->client[i].address;
				return i;
			}
		}
	}
	return -1;
}

//Send a message from one client to another. If the user exists, check if
//the user matches the sender and inform the user if so. Otherwise attempt to
//send the message to other client. 
//If the user does not exist, inform the client.
int sendMessage(int dfd, int sfd, MES &m, sharedMemory *shm) {
	MES m_out;
	int slot;
	char timestr[TIME_FSIZE];
	struct sockaddr_in recp_addr;
	string testMESrec = m.recipient;
	string testMESname = m.username;	
	
	//Check if the recipient exists
	if((slot = findUser(m.recipient, recp_addr, shm)) != -1) {
		//Check if the recipient is the sender
		if(testMESrec.compare(testMESname) == 0) {
			senIsRecpPrompt(sfd);
		}
		else {		
			sLog(M_SENT, 0, m.letter, m.username, m.recipient);	
			strncpy(m_out.username, "s", sizeof(m_out.username));
			strncpy(m_out.recipient, m.recipient, sizeof(m_out.recipient));
			//If message failed to send
			if(sendto(dfd, &m, sizeof(MES), 0, 
				(struct sockaddr *) &shm->client[slot].address,
				sizeof(shm->client[slot].address)) == -1) {
				messageStsPrompt(-1, sfd);
			}					
			else { //Message was successfully sent
				messageStsPrompt(0, sfd); 
				getTime(timestr);
				memcpy(shm->client[slot].lastLookUp, timestr, TIME_FSIZE);
				return 1;
			}
		}
	}
	//Recipient does not exist
	else { unkownUserPrompt(sfd, m.recipient); }
	return 0;
}
