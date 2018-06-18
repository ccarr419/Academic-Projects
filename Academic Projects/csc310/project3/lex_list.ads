-- Author:		Christian Carreras
-- File Name:		lex_list.ads
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This is the package header (ads) file that states all 
--			the procedures and functions that will be written
--			in the lex_list package body (adb) file. The lList part
--			of this package is used to add lexemes to a vector, 
--			get an element (lexeme) from the list, print the vector 
--			to the screen and write the vector to a file.
--			This package also implements error checking of the
--			lexemes held within the vector.

with ada.containers.vectors;
with ada.text_io;		use ada.text_io;
with lexemes;			use lexemes;
package lex_list is

	-- vector to hold lexemes
	package lList is new ada.containers.vectors(natural, lexeme);
	use lList;
	
	-- get function to return the lexeme the cursor is pointing at
	function getLexeme(lCursor: in lList.cursor) return lexeme;
	
	-- puts the lexeme parameter in the list
	procedure putInList(lexList: in out lList.vector; l: in lexeme);
	
	-- prints the entire list to the screen
	procedure printList(lexList: in lList.vector);
	
	-- writes the entire list to a file
	function writeToFile(fname: in string; lexList: in lList.vector) 
		return boolean;
		
-------------------------------------------------------------------------------
	
	-- checks the program part of a program
	procedure checkProg(lexList: in lList.vector);
	
	-- helps checkProg if program was entered by a prog id was not
	procedure checkProgHelper1(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive);
	
	-- helps checkProg if program was not entered
	procedure checkProgHelper2(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive);
	
	-- checks the dec part of a program
	procedure checkDec(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive);
	
	-- checks everything that should be after a begin statement
	procedure checkBegin(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive);
	
	-- checks the correctness of a read statement
	procedure checkRead(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive);
	
	-- checks the correctness of a write statement
	procedure checkWrite(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive);
	
	-- checks if the lexeme is an id and a correct one
	function checkId1(lexList: in lList.vector; lCursor: in lList.cursor; 
		lineNum: in positive) return boolean;
	
	-- checks if the lexeme is an id and tells user it's in the wrong place
	function checkId2(lexList: in lList.vector; lCursor: in lList.cursor; 
		lineNum: in positive) return boolean;
	
end lex_list;
