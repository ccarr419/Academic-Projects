-- Author:		Christian Carreras
-- File Name:		symbol_table.ads
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		This is the package header (ads) file that states all 
--			the procedures and functions that will be written
--			in the symbol_table package body (adb) file. 
--			This package has all the necessary functions and 
--			procedures to function as map between an identifier
--			and the line number is occurred on.

with ada.containers.ordered_maps;
with ada.strings.unbounded;		use ada.strings.unbounded;
package symbol_table is 

	-- nested package for new ordered map
	-- key is an unbounded string (id)
	-- element is a positive (line number)
	package table is new ada.containers.ordered_maps(unbounded_string, 
		positive);
	use table;
	
	-- checks if an unbounded string is already in the map
	function checkTable(sMap: in map; iStr: in unbounded_string) 
		return boolean;
		
	-- print whole map, id first then line number
	procedure printTable(sMap: in map);
	
	-- print whole map to file, id first then line number
	function writeSymbolFile(fname: in string; sMap: in map) return boolean;
	
end symbol_table;
