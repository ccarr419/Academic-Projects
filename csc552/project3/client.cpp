/*
Author:		Christian Carreras
Filename:		client.cpp
Course:		CSC 552
About:		This project creates a real-time message client that will
			attempt to connect to a server. Clients will be allowed to
			message other clients once logged-in. All information about
			clients on a local machine is held in shared memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <ifaddrs.h>
#include <ctype.h>
#include <sys/shm.h>

using namespace std;

/* acad's Internet address, defined in /etc/hosts */
#define SERV_HOST_ADDR "156.12.127.18"
#define BUFF_SIZE 128
#define USRNAME_SIZE 20
#define MAX_CLIENTS 25
#define TIME_FSIZE 13

typedef struct {
	long mtype;
	long number;
	char username[USRNAME_SIZE];
	char recipient[USRNAME_SIZE];
	char letter[BUFF_SIZE];
	struct sockaddr_in addr;
} MES;

typedef struct {
	char name[USRNAME_SIZE];
	char startTime[TIME_FSIZE];
	char lastMsgTime[TIME_FSIZE];
	int numMsg;
	pid_t pid;
} LOCAL_INFO;

typedef struct {
	LOCAL_INFO localInfo[MAX_CLIENTS];
	int numClients;
	int totalMsgs;
} LOCAL_DIR;

void getTime(char[]);
void logOff(LOCAL_DIR*, int, int);
void updateInfo(LOCAL_DIR*, int);
void splitMessage(string, MES&, sockaddr_in&, int);
void clientAddr2Ser(sockaddr_in&, sockaddr_in&, int, int);
bool findBlankSpaces(string);
bool checkMessage(char[]);
int setLocalInfo(LOCAL_DIR*, string);
int compareCaseIns(string, string);
int readMessages(int, int);
int sendMessage(string, MES&, sockaddr_in&, int);
int execExit();
int execAll(int, MES&, sockaddr_in&);
int execList(LOCAL_DIR*);
int testUsername(string);
int registerUser(int, int&, string, sockaddr_in&);
int startStrmSock(sockaddr_in&, int);
int startDgrmSock(sockaddr_in&);
char* parseInput(char[]);
struct sockaddr_in getLocalAddrs();
string login(int, int, int&, char*[], sockaddr_in&);

main(int argc, char* argv[])
{
	key_t key = 5678;
	int sockfd, dgrmfd, shmid, num;
	int CLI_TCP_PORT = 15225;
	int SERV_TCP_PORT = 15030;
	int size = sizeof(LOCAL_DIR);
	struct sockaddr_in serv_addr, cli_addr;	
	LOCAL_DIR *dir;	
	MES mes_out;
	string tmpMessage, tmpName; 
	
	sockfd = startStrmSock(serv_addr, SERV_TCP_PORT);

	tmpName = login(argc, sockfd, CLI_TCP_PORT, argv, serv_addr);
	if(tmpName == "") {
		close(sockfd);
		return 0;
	}

	if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) 
	{	cout << "shmget error\n"; close(sockfd); return 0; }
	
	if ((dir = (LOCAL_DIR *) shmat(shmid, NULL, 0)) == (LOCAL_DIR *) -1) 
	{	cout << "shmat error\n"; close(sockfd); return 0; }
	
	num = setLocalInfo(dir, tmpName);
	clientAddr2Ser(serv_addr, cli_addr, CLI_TCP_PORT, sockfd);
	dgrmfd = startDgrmSock(cli_addr);
	
	strncpy(mes_out.username, tmpName.c_str(), USRNAME_SIZE);
	cout << "\n<**> ";
	cout << "Welcome to the chat room, " << mes_out.username << endl;
	
	while(1) {
		cout << "<" << mes_out.username << ">\n";
		getline(cin, tmpMessage);
		char message[tmpMessage.length()+1];
		char *recp;
		strcpy(message, tmpMessage.c_str());
		
		if(tmpMessage == "");
		
		else if(compareCaseIns(tmpMessage, "EXIT")) {
			if(execExit())
				break;
		}
		
		else if(compareCaseIns(tmpMessage, "ALL")) {
			execAll(sockfd, mes_out, serv_addr);
			continue;
		}
		
		else if(compareCaseIns(tmpMessage, "LIST")) {
			execList(dir);
			continue;
		}

		else if((recp = parseInput(message)) != NULL) {		
			tmpMessage.erase(0, strlen(recp)+1);
			strncpy(mes_out.recipient, recp, USRNAME_SIZE);
			
			if(tmpMessage.length() < 1)
				cout << "<**> " << "No message written. Try again.\n\n";
			else
				if(sendMessage(tmpMessage, mes_out, serv_addr, sockfd))
					updateInfo(dir, num);
		}
		
		sleep(1);
		if(!readMessages(sockfd, dgrmfd)) continue;
	}
	
	logOff(dir, shmid, sockfd);
	return 0;
}

void getTime(char timestr[]) {
	time_t rawtime;
	time(&rawtime);
	struct tm* currentTime = localtime(&rawtime);
	strftime(timestr, TIME_FSIZE, "%H:%M:%S %Z", currentTime);
}

void logOff(LOCAL_DIR *dir, int shmid, int sockfd) {
	dir->numClients--;
	if(dir->numClients == 0)
		shmctl(shmid, IPC_RMID, (shmid_ds *) NULL);
	close(sockfd);
}

void updateInfo(LOCAL_DIR *dir, int num) {
	char timestr[TIME_FSIZE];
	getTime(timestr);
	dir->totalMsgs++;
	dir->localInfo[num].numMsg++;
	strcpy(dir->localInfo[num].lastMsgTime, timestr);
}

void splitMessage(string tmes, MES &m_out, sockaddr_in &addr, int fd) {
	MES tmp;
	int i = 0;
	size_t mes_size;
	do {
		string tmpStr = tmes.substr((i*(BUFF_SIZE-1)), tmes.length());
		mes_size = tmpStr.length();
		strncpy(m_out.letter, tmpStr.c_str(), BUFF_SIZE-1);			
		if(sendto(fd, &m_out, sizeof(MES),0,
			(struct sockaddr *) &addr, sizeof(addr)) == -1)
		{ 	cout << "client: write error\n"; return; }
		
		i++;						
		sleep(1);		
		if(read(fd, &tmp, sizeof(MES)) == -1)
		{ 	return; }
		
		cout << "<**> " << tmp.letter << "(" << i << ")\n";						
	} while(mes_size >= BUFF_SIZE);
	cout << endl;
}

void clientAddr2Ser(sockaddr_in &to, sockaddr_in &from, int PORT, int fd) {
	MES init;
	from = getLocalAddrs();
	from.sin_port = PORT;	
	init.addr = from;
	sendto(fd, &init, sizeof(MES),0, (struct sockaddr *) &to,
		sizeof(to));
}

bool findBlankSpaces(string tmp) {
	for(int i = 0; i < tmp.length(); i++) {
		if(tmp[i] == ' ')
			return true;
	}
	return false;
}

bool checkMessage(char tmp[]) {
	if(tmp[0] == ' ')
		return true;
	return false;
}

int setLocalInfo(LOCAL_DIR* dir, string tmpName) {
	char timestr[TIME_FSIZE];
	int num = dir->numClients++;
	if(!num)
		dir->totalMsgs = 0;
		
	getTime(timestr);
	strncpy(dir->localInfo[num].name, tmpName.c_str(), USRNAME_SIZE);
	strcpy(dir->localInfo[num].startTime, timestr);
	strcpy(dir->localInfo[num].lastMsgTime, timestr);
	dir->localInfo[num].numMsg = 0;
	dir->localInfo[num].pid = getpid();
	return num;
}

int readMessages(int sfd, int dfd) {
	MES tmp;
	if(read(sfd, &tmp, sizeof(MES)) != -1)
		cout << "<**> " << tmp.letter << "\n\n";
	if(read(dfd, &tmp, sizeof(MES)) != -1)
		cout << "<" << tmp.username << ">\n" << tmp.letter << "\n\n";
	return 1;
}

int sendMessage(string tmes, MES &m_out, sockaddr_in &addr, int fd) {
	if(tmes.length() >= BUFF_SIZE) {	
		splitMessage(tmes, m_out, addr, fd);
		//updateInfo(dir, num);
	}
			    
	else 
	{	strncpy(m_out.letter, tmes.c_str(), BUFF_SIZE-1); 
		if(sendto(fd, &m_out, sizeof(MES),0,
			(struct sockaddr *) &addr, sizeof(addr)) == -1)
		{ 	cout << "client: write error\n"; return 0; }
		//updateInfo(dir, num);
	}
	return 1;
}

int execExit() {
	string tmpStr;
	cout << "\n<**> " << "Are you sure you want to quit? (y or n)\n";
	cout << "<**> ";
	getline(cin, tmpStr);
	if((tolower(tmpStr[0])) == 'y') { cout << "<**> Goodbye\n\n"; return 1; }
	else if((tolower(tmpStr[0])) != 'n') cout << "<**> Invalid entry\n";
	cout << endl;
	return 0;
}

int execAll(int sfd, MES &m, sockaddr_in &addr) {
	MES tmp;
	strcpy(m.recipient, "a");
	if(sendto(sfd, &m, sizeof(MES),0,(struct sockaddr *) &addr,
		sizeof(addr)) == -1)
	{ 	cout << "client: write error\n"; return 0; }
	
	sleep(1);
		
	if(read(sfd, &tmp, sizeof(MES)) != -1)
		cout << "\n<**>\n" << tmp.letter;
			
	if(read(sfd, &tmp, sizeof(MES)) != -1)
		cout << tmp.letter;
			
	if(read(sfd, &tmp, sizeof(MES)) != -1)
		cout << tmp.letter;
	cout << "<**>\n\n";
	return 1;
}

int execList(LOCAL_DIR *ld) {
	cout << "<**>\n";
	for(int i = 0; i < ld->numClients; i++) {
		cout << ld->localInfo[i].name << "; ";
		cout << ld->localInfo[i].startTime << "; ";
		cout << ld->localInfo[i].lastMsgTime << "; ";
		cout << ld->localInfo[i].numMsg << "; ";
		cout << ld->localInfo[i].pid << ";\n";
	}
	cout << "<**>\n\n";
}

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

int testUsername(string tmpName) {
	if(findBlankSpaces(tmpName))
		cout << "Remove all blank spaces and try again.\n";
	else if(tmpName.length() == 0)
		cout << "Please enter a username.\n";
	else if(tmpName.length() >= USRNAME_SIZE)
		cout << "Username is too long. Try again.\n";
	else if(tmpName.length() <= 2)
		cout << "Username is too short. Try again.\n";
	else if(compareCaseIns(tmpName, "EXIT"))
		cout << "Username cannot be keyword. Try again.\n";
	else if(compareCaseIns(tmpName, "ALL"))
		cout << "Username cannot be keyword. Try again.\n";
	else if(compareCaseIns(tmpName, "LIST"))
		cout << "Username cannot be keyword. Try again.\n";
	else return 1;
	return 0;
}

int registerUser(int sfd, int &PORT, string tmpName, sockaddr_in &addr) {
	MES init, tmp;
	strncpy(init.username, tmpName.c_str(), sizeof(init.username));
	if(sendto(sfd, &init, sizeof(MES),0, (struct sockaddr *) &addr,
		sizeof(addr)) == -1)
	{ 	cout << "client: write"; return 0; }
	
	sleep(1);
		
	if(read(sfd, &tmp, sizeof(MES)) == -1);
	else if(ntohl(tmp.number) != -1) {
		PORT += ntohl(tmp.number);
		return 1;
	}
			
	cout << tmp.letter << endl;
	return 0;
}

int startStrmSock(sockaddr_in &addr, int PORT) {
	int sfd, flags;
	/* create a socket which is one end of a communication channel */
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{ 	cout << "client: cannot open stream socket"; return -1;  }

	/* specify server address */
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;  /* address family: Internet */
	addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	addr.sin_port = htons(PORT);
	
	cout << "Connecting to server...\n";
	
	if(connect(sfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
     {	cout << "client: cannot connect to server\n"; return -1; }
	
	if ((flags = fcntl(sfd, F_GETFL, 0)) < 0) 
	{	cout << "client: cannot get socket's flag\n"; return -1; }

	if (fcntl(sfd, F_SETFL, flags | O_NONBLOCK) < 0) 
	{	cout << "client: cannot change socket to non-blocking\n"; return -1; }
	
	return sfd;
}

int startDgrmSock(sockaddr_in &addr) {
	int dfd, flags;
	if((dfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{	cout << "client: cannot open dgram socket\n"; return -1; }
	
	if(bind(dfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{	cout << "client: cannot bind local address\n"; return -1; }
	
	if ((flags = fcntl(dfd, F_GETFL, 0)) < 0) 
	{	cout << "client: cannot get socket's flag\n"; return -1; }

	if (fcntl(dfd, F_SETFL, flags | O_NONBLOCK) < 0) 
	{	cout << "client: cannot change socket to non-blocking\n"; return -1; }
	
	return dfd;
}

char* parseInput(char str[]) {
	char* recp;
	if(checkMessage(str)) {
		cout << "\n<**> ";
		cout << "Remove all unnecessary blank spaces and try again.\n\n";
		return NULL;
	}
		
	else {
		recp = strtok(str, " ");
		if(strlen(recp) <= 2) {
			cout << "\n<**> " << "Recipient name too short. Try again.\n\n";
			return NULL;
		}
			
		else if(strlen(recp) >= 15) {
			cout << "\n<**> " << "Recipient name too long. Try again.\n\n";
			return NULL;
		}
	}
	return recp;
}

struct sockaddr_in getLocalAddrs() {
	struct ifaddrs *addrs, *tmpAddrs;
	struct sockaddr_in *homeAddress;
	getifaddrs(&addrs);
	tmpAddrs = addrs;
	
	while (tmpAddrs) {
		if (tmpAddrs->ifa_addr && tmpAddrs->ifa_addr->sa_family == AF_INET)
			homeAddress = (struct sockaddr_in *) tmpAddrs->ifa_addr;
		tmpAddrs = tmpAddrs->ifa_next;
	}
	freeifaddrs(addrs);
	return *homeAddress;
}

string login(int argc, int sfd, int &PORT, char *argv[], sockaddr_in &addr) {
	string tmpName;
	if(argc > 1) {
		tmpName = argv[1];
		if(testUsername(tmpName)) {
			if(!registerUser(sfd, PORT, tmpName, addr)) {
				return "";
			}
			return tmpName;
		}
		else {
			return "";
		}
	}
	
	else {
		cout << "Please enter your username: ";
		while(1) {
			getline(cin, tmpName);
			if(testUsername(tmpName)) {
				if(registerUser(sfd, PORT, tmpName, addr)) 
					break;
				else 
					return "";
			}
		}
		return tmpName;
	}
}
