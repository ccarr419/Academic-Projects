-- Author:		Christian Carreras
-- File Name:		lexemes.ads
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This is the package header (ads) file that states all 
--			the procedures and functions that will be written
--			in the lexemes package body (adb) file. This package 
--			has all the necessary functions and procedures to add
--			strings and charTypes (class_io) to lexemes. Also
--			has the functionality to print to screen or a file.
--			A lexeme is a unbounded string package.

with ada.text_io;		use ada.text_io;
with ada.strings.unbounded;	use ada.strings.unbounded;
with class_io;			use class_io;
package lexemes is

	type lexeme is private;
	
	-- initialize the lexeme as the given string
	function initialize(iStr: in string) return lexeme;
	
	-- initialize the lexeme as another lexeme
	function initialize(iStr: in lexeme) return lexeme;
	
	-- make the lexeme equal to a charType
	procedure addClass(lexStr: in out lexeme; class: in charType);
	
	-- make  the lexeme equal to a string
	procedure addString(lexStr: in out lexeme; iStr: in string);
	
	-- print lexeme to screen
	procedure printLexeme(lexStr: in lexeme);
	
	-- print lexeme to file
	procedure printToFile(outFile: in out file_type; lexStr: in lexeme);
	
	-- equality operator overload
	-- check if lexeme (left) is equal to an unbounded string (right)
	function "=" (left: in lexeme; right: in unbounded_string) 
		return boolean;
	private
		type lexeme is new unbounded_string;
end lexemes;
	