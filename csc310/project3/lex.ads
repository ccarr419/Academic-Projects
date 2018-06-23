-- Author:		Christian Carreras
-- File Name:		lex.ads
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This is the package header (ads) file that states all 
--			the procedures and functions that will be written
--			in the lex package body (adb) file. This package has
--			all the necessary functions and procedures to work with
--			files and compute them into lexemes.
--			Also works a lex list and symbol table

with ada.text_io;		use ada.text_io;
with ada.integer_text_io;	use ada.integer_text_io;
with ada.strings.unbounded;	use ada.strings.unbounded;
with class_io;			use class_io;
with lexemes;			use lexemes;
with lex_list;			use lex_list;
with symbol_table;		use symbol_table;

package lex is

	-- Checks the file if it exists or not
	-- Returns true if a file was found and false if not
	function checkFile(fname: in string) return boolean;
	
	-- Attempts to open a file from the given file name
	-- First checks if the file exists
	procedure openFile(inFile: in out file_type; fname: in string);
	
	-- Attempts to create a file from the given file name
	-- First checks if the file already exists
	procedure createFile(outFile: in out file_type; fname: in string);
	
	-- Tests the string to find the exact lexeme it is
	procedure testString(class: in out charType; iStr: in unbounded_string; 
		sMap: in out table.map; lineNum: in positive);
		
	-- Calls testString and then adds the class chosen to a lex_list object
	procedure readPreStr(outStr: in out lexeme;
		iStr: in out unbounded_string; sMap: in out table.map;
		lineNum: in positive; lexList: in out lList.vector);
		
	-- Parses through the input file and creates lexemes based on
	-- characters and strings throughout the file
	procedure computeFile(inFile: in out file_type; sMap: in out table.map; 
		lexList: in out lList.vector; echoFile: in boolean);
		
end lex;
	