# Author:			Christian Carreras
# File:			makefile
# Date:			03/07/2017
# Due Date:		03/11/2017
# Project:		#2
# Course Num:		CSC552
# Course Title:	Advanced Unix Programming
# Professor:		Dr. Spiegel
# School:			Kutztown University of Pennsylvania
# Semester:		SPRING2017
# About:			The purpose of this makefile is to compile each file
#				necessary in project #2. Each file can be compiled together
#				by issuing the command 'make' or 'make p2' or they can be
#				compiled individually by entering 'make client' or
#				'make server'. This makefile uses the basic g++ compiler
#				and adds a debug flag in the case of gdb debugging needs.

CC=/usr/bin/g++
DebugFlag=-g

#Compile whole project, make sure everything is up to date
p2: p2.cpp client.cpp server.cpp
	$(CC) $(DebugFlag) -o p2 p2.cpp
	$(CC) $(DebugFlag) -o client client.cpp
	$(CC) $(DebugFlag) -o server server.cpp

#Compile just the client
client: client.cpp
	$(CC) $(DebugFlag) -o client client.cpp

#Compile just the server
server: server.cpp
	$(CC) $(DebugFlag) -o server server.cpp
