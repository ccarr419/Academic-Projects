-- Author:		Christian Carreras
-- File Name:		lexemes.adb
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This file creates the package body (adb) file for the
--			lexemes package. Contained within are procedures and
--			functions that initializes the lexeme to a given string
--			or another lexeme, adds a charType or string to a
--			lexeme, prints the lexeme to the screen or to a file,
--			or checks equality to an unbounded string.
--			A lexeme is a basically an unbounded string with
--			methods fit for a parser.

with ada.text_io;		use ada.text_io;	
with ada.strings.unbounded;	use ada.strings.unbounded;
with class_io;			use class_io;
package body lexemes is

	-- enum package is an enumeration of charType
	-- required for adding a charType to a lexeme
	package enum is new ada.text_io.enumeration_io(charType);
	use enum;	
	
	-- Function Name:	initialize
	-- Parameter(s):	iStr : string : in only
	-- Returns:		lexeme 
	-- Purpose:		sets lexeme equal to given string
	function initialize(iStr: in string) return lexeme is
	newLexeme : lexeme;
	begin
		set_unbounded_string(newLexeme, iStr);
		return newLexeme;
	end initialize;
	
	-- Function Name:	initialize
	-- Parameter(s):	iStr - lexeme - in only
	-- Returns:		lexeme
	-- Purpose:		sets lexeme equal to another lexeme
	function initialize(iStr: in lexeme) return lexeme is
	newLexeme : lexeme;
	begin
		newLexeme := iStr;
		return newLexeme;
	end initialize;

	-- Function Name:	addClass
	-- Parameter(s):	lexStr : lexeme : in/out
	--			class : charType : in only
	-- Returns:		n/a
	-- Purpose:		sets a lexeme equal to a charType
	procedure addClass(lexStr: in out lexeme; class: in charType) is
	tempStr : string(1 .. 10);
	begin
		-- enumerate charType 'class'
		enum.put(tempStr, class);
		addString(lexStr, tempStr);
	end addClass;
	
	-- Function Name:	addString
	-- Parameter(s):	lexStr : lexeme : in/out
	--			iStr : string : in only
	-- Returns:		n/a
	-- Purpose:		sets a lexeme equal to a string
	procedure addString(lexStr: in out lexeme; iStr: in string) is
	begin
		lexStr := initialize(iStr);
	end addString;
	
	-- Function Name:	printLexeme
	-- Parameter(s):	lexStr : lexeme : in only
	-- Returns:		n/a
	-- Purpose:		prints the lexeme parameter to the screen
	procedure printLexeme(lexStr: in lexeme) is
	begin
		put_line(to_string(lexStr));
	end printLexeme;
	
	-- Function Name:	printToFile
	-- Parameter(s):	outFile : file_type : in/out
	--			lexStr : lexeme : in only
	-- Returns:		n/a
	-- Purpose:		prints the lexeme parameter to the given file
	procedure printToFile(outFile: in out file_type; lexStr: in lexeme) is
	begin
		put_line(outFile, to_string(lexStr));
	end printToFile;
	
	-- Function Name:	= operator
	-- Parameter(s):	left : lexeme : in only
	--			right : unbounded_string : in only
	-- Returns:		boolean: true if equal, false if not
	-- Purpose:
	function "=" (left: in lexeme; right: in unbounded_string) 
		return boolean is
	begin
		if left = right then
			return true;
		else
			return false;
		end if;
	end "=";

end lexemes;