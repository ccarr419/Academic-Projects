# Author:			Christian Carreras
# File:			README.txt
# Date:			03/07/2017
# Due Date:		03/11/2017
# Project:		#2
# Course Num:		CSC552
# Course Title:	Advanced Unix Programming
# Professor:		Dr. Spiegel
# School:			Kutztown University of Pennsylvania
# Semester:		SPRING2017

Doxygen Link: http://acad.kutztown.edu/~ccarr419/csc552/project2/html/index.html

Design Decisions & Bugs:

* In the client, the file descriptor used for the read
	end of the pipe used has to have it's number
	increased by one to work. I believe this has to
	with a bug with my toCString function in p2 since
	it actually copies the write file descriptor.
	
* In the client, I had to hard code the size for write
	in the case of "TOTAL" and "EXIT" because my sizeof
	functions were causing the writes to not work

* In the server, any two numbers that are both five digits
	or more or add up to 10 or more digits gets the
	wrong answers. I have no clue how this happens
	because once 1,000,000,000 is hit the numbers get
	mad. I would like to assume this has to do with the
	size of float or the size of the message buffer.
	
* In the server, I could not get fread to work when fwrite
	was used. fputs was used in its place and then fread
	worked fine.
	
* In the server, if the second number is entered has
	decimal places, it will almost always be rounded
	down. Again I this might have to do with the nature
	of floats but I am not sure.
	
* In the server, substr had to be used to match the
	entered command to "total" or "exit". This was
	because there was some garbage hanging around
	at the end of the entered command that made it
	not equal to those strings. This one I have no
	clue about, maybe something with cstrings and pipes?
	
* In the server, the sum will be off by a small amount
	if decimals are used. Again I believe this has
	to deal with floats but maybe an error with fputs
	because the numbers in the file are matching the
	output from fread.
	
* In the server and client, I had to skip a loop
	implementation because of time restraints. The
	user enters one command to the client/server, it
	fires, and it is done.
	