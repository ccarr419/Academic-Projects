-- Author:		Christian Carreras
-- File Name:		symbol_table.adb
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This file creates the package body (adb) file for the
--			symbol_table package. Contained within are procedures 
--			and functions that work with an ordered map of 
--			unbounded strings and positives. They check the map for 
--			an existing key and print the map to the screen/file.

with ada.text_io;			use ada.text_io;
with ada.integer_text_io;		use ada.integer_text_io;
with ada.containers.ordered_maps;
with ada.strings.unbounded;		use ada.strings.unbounded;
with lex;				use lex;
package body symbol_table is

	-- Function Name:	checkTable
	-- Parameter(s):	sMap : map : in only
	--			iStr : unbounded_string : in only
	-- Returns:		boolean: true if in the map, false if not
	-- Purpose:		Checks the table for the occurrence of a key
	--			equal to the unbounded string parameter
	function checkTable(sMap: in map; iStr: in unbounded_string) 
		return boolean is
	begin
		if (contains(sMap, iStr)) then
			return true; -- in the map
		else
			return false; -- not in the map
		end if;
	end checkTable;
	
	-- Function Name:	printTable
	-- Parameter(s):	sMap : map : in only
	-- Returns:		n/a
	-- Purpose:		Prints the whole map to the screen by the use
	--			of a loop. Prints the id (key) first then
	--			the line number (element).
	procedure printTable(sMap: in map) is
	sCursor 	: table.cursor; -- pointer
	lineNum		: positive;
	id		: unbounded_string;
	begin
		-- check if the map is empty
		-- no point printing if it is
		if(is_empty(sMap)) then
			return;
		else
			-- point the cursor at the first map key
			sCursor := first(sMap);
			-- loop while cursor is pointing a to map key
			while (has_element(sCursor)) loop 
				id := key(sCursor); -- get id (key)
				lineNum := element(sCursor); -- get lineNum
				put(to_string(id));
				put(lineNum);
				new_line;
				-- point cursor to next key
				sCursor := next(sCursor);
			end loop;
		end if;
	end printTable;			

	-- Function Name:	writeSymbolFile
	-- Parameter(s):	fname : string : in only
	--			sMap : map : in only
	-- Returns:		boolean: true if file was created, false if not
	-- Purpose:		Basically same implementation as printTable
	--			but is directed towards a file.
	--			Checks if the file exists and if the map is
--				empty before creating the file.
	function writeSymbolFile(fname: in string; sMap: in map)
		return boolean is
	outFile	: file_type;
	sCursor : table.cursor;
	lineNum	: positive;
	id	: unbounded_string;
	begin
		-- make sure file does not exist already
		if(not checkFile(fname)) then			
			if(is_empty(sMap)) then -- check if empty
				return false; -- not point creating file
			else
				createFile(outFile, fname);
				-- iterate through map and print each key with
				-- corresponding element to file
				sCursor := first(sMap);
				while (has_element(sCursor)) loop
					lineNum := element(sCursor);
					id := key(sCursor);
					put(outFile, to_string(id));
					put(outFile, lineNum);
					new_line(outFile);
					sCursor := next(sCursor);
				end loop;
			end if;
		else
			return false;
		end if;
		return true;
	end writeSymbolFile;
	
end symbol_table;
