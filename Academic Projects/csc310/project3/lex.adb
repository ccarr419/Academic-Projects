-- Author:		Christian Carreras
-- File Name:		lex.adb
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This file creates the package body (adb) file for the
--			lex package. Contained within are procedures and
--			functions that checks input files, opens a file
--			parameter, creates a file with a specified file name,
--			and parses an input file by calling sub programs that
--			will take a string or character and point to the
--			corresponding lexeme to place within the lex_list.

with ada.text_io;		use ada.text_io;
with ada.integer_text_io;	use ada.integer_text_io;
with ada.strings.unbounded;	use ada.strings.unbounded;
with ada.characters.latin_1;	-- Required for tab character
with class_io;			use class_io;		-- charType
with lexemes;			use lexemes;		-- lexeme object
with lex_list;			use lex_list;		-- lexemes list
with symbol_table;		use symbol_table;	-- Id list

package body lex is
	
	package enum is new ada.text_io.enumeration_io(charType);
	use enum;

-- Function Name:	checkFile
-- Parameter(s):	fname : string : in only
-- Returns:		boolean : true if file exists, false if not
-- Purpose:		This function checks the current directory for the file
--			name parameter. checkFile attempts to open the file
--			and will return true if it exists. An exception will
--			catch the file open fail and return false.
-- Credit To:		http://rosettacode.org/wiki/Check_that_file_exists#Ada
	function checkFile(fname: in string) return boolean is
	tempFile:	file_type; -- temporary file to test file name
	begin
		open(tempFile, in_file, fname);
		close(tempFile);
		return true; -- file exists
		exception -- check if there was an error while opening
			when name_error => return false;
	end checkFile;

-- Function Name:	openFile
-- Parameter(s):	inFile : file_type : in/out
--			fname : string : in only
-- Returns:		n/a
-- Purpose:		This procedure first checks if the file exists. If the
--			file exists, then the file will be opened and the user
--			will be informed that the file was found.
--			If the file does not exist, then the user will be
--			informed of the file not being found and an
--			exception will be raised and the program will quit.
	procedure openFile(inFile: in out file_type; fname: in string) is
	begin
		if(checkFile(fname)) then -- does the file exist?
			open(inFile, in_file, fname); -- yes, open it
		end if;
	end openFile;

-- Function Name:	createFile
-- Parameter(s):	outFile : file_type : in/out
--			fname : string : in only
-- Returns:		n/a
-- Purpose:		This procedure first checks if the file given already
--			exists. If the file exists, the user is notified that
--			the file already exists and an exception is raised.
--			If the file does not exist, it is created.
	procedure createFile(outFile: in out file_type; fname: in string) is
	begin
		if(not checkFile(fname)) then -- file does not exist yet
			create(outFile, out_file, fname); -- create file
		end if;
		
	end createFile;

-- Function Name:	testString
-- Parameter(s):	iStr : unbounded_string : in only
-- Returns:		charType
-- Purpose:		This function checks the accumulated string to see
--			if it is a keyword, type def, number or id.
--			Makes sure that a bad identifier is not entered.
--			Keeps track of first id occurrence in symbol table.
	procedure testString(class: in out charType; iStr: in unbounded_string; 
		sMap: in out table.map; lineNum: in positive) is
	char	: character; -- holds element to check for number
	i	: positive; -- integer (1 to 2^32-1)
	begin
		i := 1; -- iterator
		char := element(iStr, i); -- check first element in string
		case char is
			-- check for a bad identifier in the first character
			when '0' .. '9' => -- must be a number
				-- make sure every character in string is num
				while i <= length(iStr) loop 
					char := element(iStr, i);
					case char is
						when '0' .. '9' =>
							char := ' ';
						-- not a number
						-- identifiers cannot start
						-- with a number
						when others =>
							class := badId;
							return;
					end case;
					i := i + 1; -- increment iterator
				end loop;
				class := num; -- must be a number
				
			-- must be a letter
			when 'A' .. 'Z' | 'a' .. 'z' =>
				while i <= length(iStr) loop
					char := element(iStr, i);
					-- now can be any letter, number,
					-- underscore or period
					case char is
						when 'A' .. 'Z' | 'a' .. 'z' 
						| '0' .. '9' | '_' | '.' =>
							char := ' ';
						-- encounter any special char
						when others =>
							-- label as bad id
							class := badId;
							return;
					end case;
					i := i + 1; -- increment iterator
				end loop;
			-- automatically bad identifier
			when others =>
				class := badId;
				return;
		end case;
		
		if(iStr = "program") then -- keyword
			class := progsym;
			return;
		elsif(iStr = "dec") then -- keyword
			class := decsym;
			return;
		elsif(iStr = "begin") then -- keyword
			class := beginsym;
			return;
		elsif(iStr = "end.") then -- keyword
			class := endsym;
			return;
		elsif(iStr = "int") then -- type def
			class := typesym;
			return;
		elsif(iStr = "real") then -- type def
			class := typesym;
			return;
		elsif(iStr = "Read") then -- keyword (method)
			class := readsym;
			return;
		elsif(iStr = "Write") then -- keyword (method)
			class := writesym;
			return;		
		else -- must be an id, does not match keywords or types
			-- check symbol table if the id was already entered
			if(checkTable(sMap, iStr)) then
				-- id already in table, put unique id lexeme
				class := idrp; -- identifier repeated
				return;
			else -- new identifier, add it to the table
				sMap.insert(iStr, lineNum);
				class := id;
				return;
			end if;
		end if;
	end testString;

-- Function Name:	readPreStr
-- Parameter(s):	outFile : file_type : in/out
--			iStr : unbounded_string : in/out
-- Returns:		n/a
-- Purpose:		This procedure tests a non empty string if it is equal
--			to keywords, type defs, numbers or ids then adds that
--			class to the lexeme and puts the lexeme in the lex list. 
	procedure readPreStr(outStr: in out lexeme; 
		iStr: in out unbounded_string; sMap: in out table.map; 
		lineNum: in positive; lexList: in out lList.vector) is
	class:	charType; -- hold determined terminal term
	begin
		if(length(iStr) > 0) then -- must be non empty string
			testString(class, iStr, sMap, lineNum);
			addClass(outStr, class); 
			-- the lexeme is now the selected class
			-- put the lexeme in the lex list
			putInList(lexList, outStr);
		end if;
		set_unbounded_string(iStr, ""); -- clear string
	end readPreStr;
	
-- Function Name:	computeFile
-- Parameter(s):	inFile : file_type : in/out
--			outFile : file_type : in/out
-- Returns:		n/a
-- Purpose:		This procedure reads every character in the parameter
--			inFile until end of file is reached. Letters, numbers,
--			underscores and periods are added to a string and then
--			when any character not representing those previously
--			stated are entered, readPreStr is called to determine
--			the appropriate class and write it to the lex list and
--			the current character's class is saved for next time.
--			Once a class is chosen and written to lex list, the
--			accumulative string is cleared. Once end of file is
--			reached, the input file is closed.
--			if the echoFile parameter is true, the file will be
--			printed to the screen char by char as it is computed.
	procedure computeFile(inFile: in out file_type; sMap: in out table.map; 
		lexList: in out lList.vector; echoFile: in boolean) is
	char		:	character; -- read from input file
	lineNum		:	positive;
	class		:	charType; 
	iStr		:	unbounded_string; -- dynamically sized string
	outStr		:	lexeme;
	begin
		outStr := initialize(""); -- initialize new empty lexeme
		lineNum := 1;
		while not end_of_file(inFile) loop
			set_unbounded_string(iStr, ""); -- clear string
			while not end_of_line(inFile) loop
				get(inFile, char); -- read char by char
				-- print char to screen if echoFile is true
				if echoFile then put(char); end if;
				case char is
					-- when a letter
					when 'A' .. 'Z' | 'a' .. 'z' =>
						-- concatenate char to string
						iStr := iStr & char;
						goto continue;
					-- when a number
					when '0' .. '9' =>
						iStr := iStr & char;
						goto continue;
					-- when underscore or period
					when '_' | '.' =>
						iStr := iStr & char;
						goto continue;
					-- when space/blank
					when ' ' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						goto continue;
					-- when a tab character
					when ada.characters.latin_1.ht =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						goto continue;
					-- semicolon
					when ';' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := semicolon;
					-- colon
					when ':' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := colon;
					-- comma
					when ',' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := comma;
					-- left parenthesis
					when '(' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := lParen;
					-- right parenthesis
					when ')' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := rParen;
					-- when an assign operator
					when '=' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := assignop;
					-- operator
					when '+' | '-' | '*' | '/' =>
						readPreStr(outStr, iStr, sMap, 
						lineNum, lexList);
						class := operator;
					-- default/anything else
					when others =>
						iStr := iStr & char;
						goto continue; -- continue;
				end case;
				-- add class to lexeme
				addClass(outStr, class);
				putInList(lexList, outStr);
				-- clear string
				set_unbounded_string(iStr, "");	
				-- continue tag for goto statements
				-- ada does not support continue statements
				<<continue>>
				-- filler line because something must be
				-- executed after a goto tag
				char := ' ';
				
			end loop; -- end of line
			-- write string before end of line was reached
			-- print new line if echoFile is true
			if echoFile then new_line; end if;
			readPreStr(outStr, iStr, sMap, lineNum, lexList);
			addString(outStr, "\n"); -- new line character
			putInList(lexList, outStr);
			skip_line(inFile); -- skip to next line in inFile
			lineNum := lineNum + 1;
		end loop; -- end of file
		-- close files to ensure no data leak
		close(inFile);
	end computeFile;
	
end lex;
		