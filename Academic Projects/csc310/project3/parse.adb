-- Author:		Christian Carreras
-- File Name:		symbol_table.adb
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		Takes an input file and computes the file by parsing
--			it and returning any errors found. This file uses only
--			command-line parameters and command-line switches for
--			additional options.

with ada.text_io;		use ada.text_io;
with ada.integer_text_io;	use ada.integer_text_io;
with ada.command_line;		use ada.command_line;
with gnat.command_line;		use gnat.command_line;
with ada.strings.unbounded;	use ada.strings.unbounded;
with class_io;			use class_io;
with lex;			use lex;
with lexemes;			use lexemes;
with lex_list;			use lex_list;
with symbol_table;		use symbol_table;
		
procedure parse is
inFile	: file_type;
sMap	: table.map;
lexList	: lList.vector;
i	: positive;
f	: positive;

	-- package for possible errors that may arise
	-- exceptions make program end prematurely
	package error is
		fileNotFound 	: exception;
		fileExists	: exception;
		commandLineFail	: exception;
	end error;
	
	-- Function Name:	lexemesOut
	-- Parameter(s):	j : positive : in only
	--			f : positive : in only
	--			lexList : lList.vector : in/out
	-- Returns:		n/a
	-- Purpose:		Creates a file to hold the generated lexemes
	--			if the file does not already exist.
	procedure lexemesOut(j: in positive; f: in positive;
		lexList: in out lList.vector) is
	inFile	: file_type;
	sMap	: table.map;
	begin
		-- check to make sure if the file does not already exist
		-- f: argument number of file to parse
		-- j: argument number of file to write lexemes to
		if(checkFile(argument(f))) then
			openFile(inFile, argument(f));
			computeFile(inFile, sMap, lexList, false);
			
			if (writeToFile(argument(j), lexList)) then
				put_line("'" & argument(j) & "' was created.");
			else
				put_line("File '" & argument(j) & "' already " &
					"exists, please choose another name.");
				raise error.fileExists;
			end if;
		else -- file exists already, raise error
			put_line("File '" & argument(f) & "' was not found.");
			raise error.fileNotFound;
		end if;
	end lexemesOut;
	
	-- Function Name:	symbolTableOut
	-- Parameter(s):	j: positive: in only
	--			f: positive: in only
	--			lexList : lList.vector : in/out
	-- Returns:		n/a
	-- Purpose:		Creates a file to hold the contents of the
	--			symbol table a.k.a. the identifier list with
	--			their corresponding line number
	procedure symbolTableOut(j: in positive; f: in positive;
		lexList: in out lList.vector) is
	inFile	: file_type;
	sMap	: table.map;
	begin
		-- check to make sure if the file does not already exist
		-- f: argument number of file to parse
		-- j: argument number of file to write lexemes to
		if(checkFile(argument(f))) then
			openFile(inFile, argument(f));
			computeFile(inFile, sMap, lexList, false);
			if (writeSymbolFile(argument(j), sMap)) then
				put_line("'" & argument(j) & "' was created.");
			else
				put_line("File '" & argument(j) & "' already " &
					"exists, please choose another name.");
				raise error.fileExists;
			end if;
		else -- file exists already, raise error
			put_line("File '" & argument(f) & "' was not found.");
			raise error.fileNotFound;
		end if;
	end symbolTableOut;
	
	-- Function Name:	echoFile
	-- Parameter(s):	f: positive: in only
	--			lexList : lList.vector : in/out
	-- Returns:		n/a
	-- Purpose:		prints the file to the screen as it's parsed
	procedure echoFile(f: in positive; lexList: in out lList.vector) is
	inFile	: file_type;
	sMap	: table.map;
	begin
		-- check to make sure if the file does not already exist
		-- f: argument number of file to parse
		if(checkFile(argument(f))) then
			openFile(inFile, argument(f));
			put_line("Echo file '" & argument(f) & "' to screen");
			new_line;
			computeFile(inFile, sMap, lexList, true);
			new_line;
			put_line("Echo completed.");
		else -- file exists already, raise error
			put_line("File '" & argument(f) & "' was not found");
			raise error.fileNotFound;
		end if;
	end echoFile;
	
	-- Function Name:	checkCommSwitches
	-- Parameter(s):	cmls: string : in only
	--			i : positive : in only
	--			f : positive : in only
	--			lexList : lList.vector : in/out
	-- Returns:		n/a
	-- Purpose:		Checks for command-line switches
	procedure checkCommSwitches(cmls : in string; i: in positive; 
		f: in positive; lexList: in out lList.vector) is
	cmlsStr		: unbounded_string;
	char		: character;
	idx		: positive;
	j		: positive;
	begin
		idx := 1; -- iterator index of string
		-- argument number of file to use command-line switch on
		j := i + 1; 
		-- make argument into unbounded_string
		cmlsStr := to_unbounded_string(cmls);
		char := element(cmlsStr, idx);
		-- check every char in string for command-line switch
		while idx <= length(cmlsStr) loop
			case char is
				when 'L' => -- print lex list to file
					lexemesOut(j, f, lexList);
					exit;
				when 'S' => -- print symbol table to file
					symbolTableOut(j, f, lexList);
					exit;
				when 'E' => -- print input file to screen
					echoFile(f, lexList);
					exit;
				when '/' => -- keep checking
					put("");
				when others => -- not a command-line switch
					exit;
			end case;
			idx := idx + 1; -- increment index
			char := element(cmlsStr, idx); -- get next char
		end loop;
	end checkCommSwitches;
					
begin	
	-- This program only runs from the command-line
	-- any non-command-line operation will be terminated
	if argument_count = 0 then
		put_line("This program must run from the command-line.");
		put_line("Please try again with a command-line argument.");
		
	-- There is only one command-line argument
	elsif argument_count = 1 then
		-- check if the file exists then open, compute and error check
		if checkFile(argument(1)) then
			openFile(inFile, argument(1));
			computeFile(inFile, sMap, lexList, false);
			--checkProg(lexList);
			put_line("Done");
		else -- file was not found, raise error
			put_line("File '" & argument(1) & "' was not found.");
			raise error.fileNotFound;
		end if;
	-- If there were multiple command-line arguments
	-- Min: 2, Max: 6 (1/cmls 2fname 3/cmls 4fname 5/cmls 6fname)
	elsif argument_count > 1 and argument_count <= 6 then
		-- if the parse file is first
		if checkFile(argument(1)) then
			i := 2; -- command-line switch
			f := 1; -- file to parse
			while i <= argument_count loop
				checkCommSwitches(argument(i), i, f, lexList);
				i := i + 1;
			end loop;
			--checkProg(lexList);
		-- if the parse file is second
		elsif checkFile(argument(2)) then
			-- only /E command-line switch before parse file
			if (argument(1) /= "/E") then
				put_line("Expected '/E' command-line switch");
				raise error.commandLineFail;
			else
				i := 1; -- command-line switch
				f := 2; -- file to parse
				while i <= argument_count loop
					checkCommSwitches(argument(i), i, f, 
						lexList);
					i := i + 1;
				end loop;
				--checkProg(lexList);
			end if;
		else -- command-line error
			put_line("An error has occurred within the command-line.");
			raise error.fileNotFound;
		end if;
	end if;
	
exception
	when error.fileNotFound => null;
	when error.fileExists => null;
	when error.commandLineFail => null;
end parse;
