#Author:		Christian Carreras
#File:		client.cpp
#Date:		04/12/2017
#Course:		CSC 552 Adv Unix Prog
#Professor:	Dr. Spiegel
#School:		Kutztown University
#Project:		#3
#Due Date:	05/11/2017
#About:		

CC=/usr/bin/g++

#Compile whole project, make sure everything is up to date
p3: 	client.cpp server.cpp
	$(CC) -o client client.cpp
	$(CC) -o server server.cpp

#Compile just the client
client: client.cpp
	$(CC) -o client client.cpp

#Compile just the server
server: server.cpp
	$(CC) -o server server.cpp
