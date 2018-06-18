-- Author:		Christian Carreras
-- File Name:		lex.adb
-- File Created:	03/11/2015
-- Due Date:		03/20/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		2
-- Purpose:		This program takes an input file and output file name
--			as command-line arguments. The input file is checked
--			to see if it exists, the output file is then checked
--			that it does not match an already existing file.
--			If names are accepted, the input file is read character
--			by character with a recorder unbounded string to keep
--			track of the previous sequence of characters. The
--			unbounded string is required to locate keywords,
--			type defs, ids and numbers in the input file.
--			Terms are assigned to all the terminals in the language
--			and those terms are written to the output file.
--			File names can also be entered manually.

with ada.text_io;		use ada.text_io;
with ada.integer_text_io;	use ada.integer_text_io;
-- command line for command-line arguments
with ada.command_line;		use ada.command_line;
-- unbounded string for dynamically sized strings
with ada.strings.unbounded;	use ada.strings.unbounded;

procedure lex is

	-- list of all terminals in the language
	type charType is (progsym, decsym, beginsym, endsym, typesym, readsym,
				writesym, operator, lParen, rParen, id, num,
				comma, colon, semicolon);

	-- exceptions catch errors and end the program
	-- Credit To:	http://stackoverflow.com/questions/23176305/					
	package error is
		fileNotFound:	exception;
		fileNameTaken:	exception;
	end error;
	
	package class_io is new ada.text_io.enumeration_io(charType);
	use class_io;
	
	inFile, outFile:		file_type; -- files to be used
	fname:				string(1..80); -- file name
	len:				natural; -- length of manual input

-- Function Name:	checkFile
-- Parameters		fname : string : in only
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

-- Function Name:	checkFile
-- Parameters:		fname : string : in only
--			len : natural : in only
-- Returns:		boolean : true if file exists, false if not
-- Purpose:		This function is similar to previous checkFile 
--			function with the only difference being that the  
--			string length 'len' is incorporated for 
--			non command-line (manual) input.
	function checkFile(fname: in string; len: in natural) return boolean is
	tempFile:	file_type;
	begin
		-- use only the entered input, not the junk afterwards
		open(tempFile, in_file, fname(fname'first..len));
		close(tempFile);
		return true;
		exception -- error opening file, checkFile fail
			when name_error => return false;
	end checkFile;

-- Function Name:	openFile
-- Parameters:		inFile : file_type : in/out
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
			put_line("' was found."); -- yes, open it
			open(inFile, in_file, fname);
		else
			put_line("' was not found.");
			raise error.fileNotFound; -- quit program
		end if;
	end openFile;
	
-- Function Name:	openFile
-- Parameters:		inFile : file_type : in/out
--			fname : string : in only
--			len : natural : in only
-- Returns:		n/a
-- Purpose:		This procedure is similar to the previous openFile
--			procedure with the only difference being that the
--			string length 'len' is incorporated for
--			non command-line (manual) input.
	procedure openFile(inFile: in out file_type; fname: in string;
		len: in natural) is
	begin
		if(checkFile(fname, len)) then -- does the file exist?
			put_line("' was found."); -- yes, open it
			open(inFile, in_file, fname(fname'first..len));
		else
			put_line("' was not found.");
			raise error.fileNotFound; -- quit program
		end if;
	end openFile;

-- Function Name:	createFile
-- Parameters:		outFile : file_type : in/out
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
			put_line("'" & fname & "' was created.");
		else
			put_line("'" & fname & "' already exists.");
			raise error.fileNameTaken; -- file already exists
		end if;
		
	end createFile;
	
-- Function Name:	createFile
-- Parameters:		outFile : file_type : in/out
--			fname : string : in only
--			len : natural : in only
-- Returns:		n/a
-- Purpose:		This procedure is similar to the previous createFile
--			procedure with the only difference being that the
--			string length 'len' is incorporated for
--			non command-line (manual) input
	procedure createFile(outFile: in out file_type; fname: in string;
		len: in natural) is
	begin
		if(not checkFile(fname, len)) then -- file does not exist yet
			create(outFile, out_file, fname(fname'first..len));
			put_line("'" & fname(fname'first..len) -- create file
				& "' was created.");
		else
			put_line("'" & fname(fname'first..len)
				& "' already exists.");
			raise error.fileNameTaken; -- file already exists
		end if;
		
	end createFile;

-- Function Name:	testString
-- Parameters:		iStr : unbounded_string : in only
-- Returns:		charType
-- Purpose:		This function checks the accumulated string to see
--			if it is a keyword, type def, number or id.
	function testString(iStr: in unbounded_string) return charType is
	class:	charType; -- holds return value
	char:	character; -- holds element to check for number
	begin
		char := element(iStr, 1); -- check first element in string
		case char is
			when '0' .. '9' => -- must be a number
				class := num;
				return class;
			when others =>
				-- filler line, do nothing productive
				char := ' ';
		end case;
		
		if(iStr = "program") then -- keyword
			class := progsym;
			return class;
		elsif(iStr = "dec") then -- keyword
			class := decsym;
			return class;
		elsif(iStr = "begin") then -- keyword
			class := beginsym;
			return class;
		elsif(iStr = "end.") then -- keyword
			class := endsym;
			return class;
		elsif(iStr = "int") then -- type def
			class := typesym;
			return class;
		elsif(iStr = "real") then -- type def
			class := typesym;
			return class;
		elsif(iStr = "Read") then -- keyword
			class := readsym;
			return class;
		elsif(iStr = "Write") then -- keyword
			class := writesym;
			return class;		
		else -- must be an id, does not match keywords or types
			class := id;
			return class;
		end if;
	end testString;

-- Function Name:	readPreStr
-- Parameters:		outFile : file_type : in/out
--			iStr : unbounded_string : in/out
-- Returns:		n/a
-- Purpose:		This procedure tests a non empty string if it is equal
--			to keywords, type defs, numbers or ids then writes the
--			class tied to that string to the output file. 
	procedure readPreStr(outFile: in out file_type; 
		iStr: in out unbounded_string) is
	class:	charType; -- hold determined terminal term
	begin
		if(length(iStr) > 0) then -- must be non empty string
			class := testString(iStr);
			class_io.put(outFile, class); -- write to outFile
			new_line(outFile); -- write new line to outFile
		end if;
		set_unbounded_string(iStr, ""); -- clear string
	end readPreStr;
	
-- Function Name:	computeFile
-- Parameters:		inFile : file_type : in/out
--			outFile : file_type : in/out
-- Returns:		n/a
-- Purpose:		This procedure reads every character in the parameter
--			inFile until end of file is reached. Letters, numbers,
--			underscores and periods are added to a string and then
--			when any character not representing those previously
--			stated are entered, readPreStr is called to determine
--			the appropriate class and write it to the outFile and
--			the current character's class is saved for next time.
--			Once a class is chosen and written to outFile, the
--			accumulative string is cleared. Once end of file is
--			reached, all files are closed and computeFile is done.
	procedure computeFile(inFile: in out file_type; 
		outFile: in out file_type) is
	char		:	character; -- read from input file
	class		:	charType; 
	iStr		:	unbounded_string; -- dynamically sized string
	begin
		put_line("Reading input file...");
		while not end_of_file(inFile) loop
			set_unbounded_string(iStr, ""); -- clear string
			while not end_of_line(inFile) loop
				get(inFile, char); -- read char by char		
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
						readPreStr(outFile, iStr);
						goto continue;
					-- semicolon
					when ';' =>
						readPreStr(outFile, iStr);
						class := semicolon;
					-- colon
					when ':' =>
						readPreStr(outFile, iStr);
						class := colon;
					-- comma
					when ',' =>
						readPreStr(outFile, iStr);
						class := comma;
					-- left parenthesis
					when '(' =>
						readPreStr(outFile, iStr);
						class := lParen;
					-- right parenthesis
					when ')' =>
						readPreStr(outFile, iStr);
						class := rParen;
					-- operator
					when '=' | '+' | '-' | '*' | '/' =>
						readPreStr(outFile, iStr);
						class := operator;
					-- default/anything else
					when others =>
						goto continue; -- continue;
				end case;
				-- write class to output file
				class_io.put(outFile, class);
				new_line(outFile);
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
			readPreStr(outFile, iStr);
			put_line(outFile, "\n"); -- new line character
			skip_line(inFile); -- skip to next line in inFile
		end loop; -- end of file
		new_line(outFile);
		-- close files to ensure no data leak
		close(inFile);
		close(outFile);
		put_line("...done");
	end computeFile;
	
begin
	-- manual input
	if argument_count = 0 then
		put("Enter the name of your input file: ");
		get_line(fname, len); 
		-- use len to cut out junk after file name
		put("The file '" & fname(fname'first..len));
		openFile(inFile, fname, len);
		put("Enter the name of your output file: ");
		get_line(fname, len);
		createFile(outFile, fname, len);
		computeFile(inFile, outFile);
		
	-- command-line input
	elsif argument_count = 2 then
		put("The file '" & argument(1));
		openFile(inFile, argument(1));
		createFile(outFile, argument(2));
		computeFile(inFile, outFile);	
	end if;

-- end program prematurely if exception/error was raised
exception
	when error.fileNotFound => null;
	when error.fileNameTaken => null;
-- make sure file is closed to avoid data leak
-- in case error is reached between inFile opening and outFile creation
close(inFile);
	
end lex;
	
	
		