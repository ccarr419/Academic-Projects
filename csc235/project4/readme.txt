Author:		Christian Carreras
Class:		CSC 235
Assignment:	#4
File:		readme.txt
Date Created:	December 4, 2014

Problems encountered in Project 4
1.) Segfaults and Bus Errors for multiple entries
	a.) Ctrl-D did not end data entry
	b.) Skipped name entry after first employee
	
	Notes on 1: I kept to one entry as I didn't have time to fix issues
				with multiple entries
				
2.) Half int values do not show up properly

	Notes on 2: I found that the value depends on values of 2^8
				i.e. if value is 256-511, output will be one
					if value is 512-767, output will be two.
				etc.
				
3.) Cannot get smaller fit of data members within frame width
	a.) Bus Errors for any other location of data members

	Notes on 3: Only works for the way the data is currently spaced
	
4.) 4-bit ints did not work for any value of frame
	a.) Bus Errors
	
Other notes on Project 4
1.) Search not implemented - I could not get multiple entries to work
2.) SearchEmployee not implemented - I could not get multiple entries to work
3.) I did not fully understand the tagged bit so it was left out.
	a.) In its place I read the char again and tested whether it was h or H
4.) Parameter values and return values were not precise to specifications
	as I wanted it work first before I had it exact. I could not find out
	how to do certain means of passing parameters or returning values.
5.) The incompleteness of the project came down to a time issue.
				
