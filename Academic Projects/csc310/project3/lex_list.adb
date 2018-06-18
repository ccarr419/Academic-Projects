-- Author:		Christian Carreras
-- File Name:		lex_list.adb
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This file creates the package body (adb) file for the
--			lex_list package. Contained within are procedures and
--			functions that puts lexemes into a vector and gets 
--			those lexemes when needed. Printing the vector to the
--			screen and to a file is also available. This package
--			has an error checking feature which checks the lexemes
--			within the vector for syntactical and grammatical
--			correctness to a grammar.


with ada.containers.vectors;
with ada.text_io;		use ada.text_io;
with ada.integer_text_io;	use ada.integer_text_io;
with ada.strings.unbounded;	use ada.strings.unbounded;
with lexemes;			use lexemes;
with lex;			use lex;
package body lex_list is

	-- Function Name:	putInList
	-- Parameter(s):	lexList : lList.vector : in/out
	--			l : lexeme : in only
	-- Returns:		n/a
	-- Purpose:		puts the lexeme parameter in the list
	procedure putInList(lexList: in out lList.vector; l: in lexeme) is
	begin
		append(lexList, l);
	end putInList;
	
	-- Function Name:	getLexeme
	-- Parameter(s):	lCursor : lList.cursor : in only
	-- Returns:		lexeme
	-- Purpose:		gets the lexeme the cursor is pointing at
	function getLexeme(lCursor: in lList.cursor) return lexeme is
	lexElt : lexeme;
	begin
		lexElt := element(lCursor);
		return lexElt;
	end getLexeme;
	
	-- Function Name:	printList
	-- Parameter(s):	lexList : lList.vector : in only
	-- Returns:		n/a
	-- Purpose:		iterates through the list and prints every 
	--			lexeme to the screen
	procedure printList(lexList: in lList.vector) is
	lCursor : lList.cursor;
	l	: lexeme;
	begin
		if(is_empty(lexList)) then
			return;
		else
			lCursor := first(lexList);
			while (has_element(lCursor)) loop
				l := element(lCursor);
				printLexeme(l);
				lCursor := next(lCursor);
			end loop;
		end if;
	end printList;
	
	-- Function Name:	writeToFile
	-- Parameter(s):	fname : string : in only
	--			lexList : lList.vector : in only
	-- Returns:		boolean: true if file created, false if not
	-- Purpose:		iterates through the list and writes every
	--			lexeme to a file
	function writeToFile(fname: in string; lexList: in lList.vector) 
		return boolean is
	outFile	: file_type;
	lCursor : lList.cursor;
	l	: lexeme;
	begin
		if(not checkFile(fname)) then
			createFile(outFile, fname);
			if(is_empty(lexList)) then
				return false;
			else
				lCursor := first(lexList);
				while (has_element(lCursor)) loop
					l := element(lCursor);
					printToFile(outFile, l);
					lCursor := next(lCursor);
				end loop;
			end if;
		else
			return false;
		end if;
		return true;
	end writeToFile;
	
-------------------------------------------------------------------------------
	
	-- Function Name:	checkProg
	-- Parameter(s):	lexList: lList.vector
	-- Returns:		n/a
	-- Purpose:		Checks the program part of a grammar for errors
	procedure checkProg(lexList: in lList.vector) is
	lCursor		: lList.cursor;
	lineNum 	: positive;
	lexElt		: lexeme;
	errorCount	: natural;
	begin
		-- check if list is empty, if so, no point error checking
		if is_empty(lexList) then
			return;
		end if;
		lCursor := first(lexList);
		lexElt := initialize(getLexeme(lCursor));
		lineNum := 1;
		-- while not end of list
		while lCursor /= last(lexList) loop
			-- while not new line char
			while lexElt = to_unbounded_string("\n") loop
				-- if program part present
				if lexElt = to_unbounded_string("progsym") then
					-- go to next element
					lCursor := next(lCursor);
					-- check if id comes next
					if checkId1(lexList, lCursor, 
						lineNum) then
						-- id was there
						-- check dec part
						checkDec(lexList, lCursor, 
							lineNum);
					-- id was not there, need help
					else
						checkProgHelper1(lexList, 
							lCursor, lineNum);
					end if;
				-- program part not present
				else
					put(lineNum);
					put(" Expected program declaration");
					new_line;
					-- check for id came afterwards
					-- also, need help
					if checkId2(lexList, lCursor, 
						lineNum) then
						lCursor := next(lCursor);
						checkProgHelper2(lexList, 
							lCursor, lineNum);
					else -- not and id
						checkProgHelper2(lexList, 
							lCursor, lineNum);
					end if;					
				end if;					
			end loop;
			lineNum := lineNum + 1; -- increment line number
			lCursor := next(lCursor);
		end loop;
	end checkProg;
	
	-- Function Name:	checkProgHelper1
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks all possible lexemes after program
	--			has been entered
	procedure checkProgHelper1(lexList: in lList.vector;
		lCursor: in out lList.cursor; lineNum: in out positive) is
	lexElt : lexeme;
	begin
		lexElt := initialize(getLexeme(lCursor));	
		if lexElt = to_unbounded_string("progsym") then
			put(lineNum);
			put(" Program already declared");
			new_line;
			lCursor := next(lCursor);
			if checkId1(lexList, lCursor, lineNum) then
				checkDec(lexList, lCursor, lineNum);
			else
				checkProgHelper1(lexList, lCursor, lineNum);
			end if;
		elsif lexElt = to_unbounded_string("decsym") then
			put(lineNum);
			put(" Dec must be declared after a program part");
			new_line;
			lCursor := next(lCursor);
			checkDec(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("beginsym") then
			put(lineNum);
			put(" Begin must come after program and dec part");
			new_line;
			lCursor := next(lCursor);
			checkBegin(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("endsym") then
			put(lineNum);
			put(" End. must come after program, dec and begin part");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper1(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("typesym") then
			put(lineNum);
			put(" Type declaration must be in a dec statement");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper1(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("readsym") then
			put(lineNum);
			put(" Read method must come after begin statement");
			new_line;
			lCursor := next(lCursor);
			checkRead(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("writesym") then
			put(lineNum);
			put(" Write method must come after begin statement");
			new_line;
			lCursor := next(lCursor);
			checkWrite(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("num") then
			put(lineNum);
			put(" Unexpected number");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper1(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("operator") then
			put(lineNum);
			put(" Unexpected operator");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper1(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("assignop") then
			put(lineNum);
			put(" Unexpected operator");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper1(lexList, lCursor, lineNum);
		else
			put(lineNum);
			put(" Unexpected character");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper1(lexList, lCursor, lineNum);
		end if;				
	end checkProgHelper1;
	
	-- Function Name:	checkProgHelper2
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks all possible lexemes after program
	--			has not been entered
	procedure checkProgHelper2(lexList: in lList.vector;
		lCursor: in out lList.cursor; lineNum: in out positive) is
	lexElt : lexeme;
	begin
		lexElt := initialize(getLexeme(lCursor));	
		if lexElt = to_unbounded_string("progsym") then
			put(lineNum);
			put(" Program must be declared at beginning of program");
			new_line;
			lCursor := next(lCursor);
			if checkId1(lexList, lCursor, lineNum) then
				checkDec(lexList, lCursor, lineNum);
			else
				checkProgHelper1(lexList, lCursor, lineNum);
			end if;
		elsif lexElt = to_unbounded_string("decsym") then
			put(lineNum);
			put(" Dec must be declared after a program part");
			new_line;
			lCursor := next(lCursor);
			checkDec(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("beginsym") then
			put(lineNum);
			put(" Begin must come after program and dec part");
			new_line;
			lCursor := next(lCursor);
			checkBegin(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("endsym") then
			put(lineNum);
			put(" End. must come after program, dec and begin part");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper2(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("typesym") then
			put(lineNum);
			put(" Type declaration must be in a dec statement");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper2(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("readsym") then
			put(lineNum);
			put(" Read method must come after begin statement");
			new_line;
			lCursor := next(lCursor);
			checkRead(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("writesym") then
			put(lineNum);
			put(" Write method must come after begin statement");
			new_line;
			lCursor := next(lCursor);
			checkWrite(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("num") then
			put(lineNum);
			put(" Unexpected number");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper2(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("operator") then
			put(lineNum);
			put(" Unexpected operator");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper2(lexList, lCursor, lineNum);
		elsif lexElt = to_unbounded_string("assignop") then
			put(lineNum);
			put(" Unexpected operator");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper2(lexList, lCursor, lineNum);
		else
			put(lineNum);
			put(" Unexpected character");
			new_line;
			lCursor := next(lCursor);
			checkProgHelper2(lexList, lCursor, lineNum);
		end if;	
	end checkProgHelper2;
	
	-- Function Name:	checkDec
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks the dec part for correct grammar
	procedure checkDec(lexList: in lList.vector;
		lCursor: in out lList.cursor; lineNum: in out positive) is
	begin
		return;
	end checkDec;
	
	-- Function Name:	checkBegin
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks everything after begin for correct
	--			grammar
	procedure checkBegin(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive) is
	begin
		return;
	end checkBegin;
	
	-- Function Name:	checkRead
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks grammar for a read statement
	procedure checkRead(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive) is
	begin
		return;
	end checkRead;
	
	-- Function Name:	checkWrite
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks grammar for a write statement
	procedure checkWrite(lexList: in lList.vector; 
		lCursor: in out lList.cursor; lineNum: in out positive) is
	begin
		return;
	end checkWrite;
	
	-- Function Name:	checkId1
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks grammar for an id
	--			for right after a program declaration
	function checkId1(lexList: in lList.vector; lCursor: in lList.cursor; 
		lineNum: in positive) return boolean is
	lexElt : lexeme;
	begin
		lexElt := initialize(getLexeme(lCursor));
		if (lexElt = to_unbounded_string("id")) then
			return true;
		elsif (lexElt = to_unbounded_string("badId")) then
			put(lineNum);
			put(" Bad identifier name");
			new_line;	
			return true;
		else
			put(lineNum);
			put(" Expected identifier");
			new_line;
			return false;
		end if;
	end checkId1;
	
	-- Function Name:	checkId2
	-- Parameter(s):	lexList: lList.vector : in only
	--			lCursor: lList.cursor : in/out
	--			lineNum: positive: in/out
	-- Returns:		n/a
	-- Purpose:		checks grammar for an id
	--			for when program never declared but no other
	--			ids have shown up
	function checkId2(lexList: in lList.vector; lCursor: in lList.cursor; 
		lineNum: in positive) return boolean is
	lexElt : lexeme;
	begin
		lexElt := initialize(getLexeme(lCursor));
		if (lexElt = to_unbounded_string("id")) then
			put(lineNum);
			put(" Program id must come after program declaration");
			new_line;	
			return true;
		elsif (lexElt = to_unbounded_string("badId")) then
			put(lineNum);
			put(" Bad identifier name");
			new_line;	
			return true;
		else
			return false;
		end if;
	end checkId2;
			
end lex_list;
