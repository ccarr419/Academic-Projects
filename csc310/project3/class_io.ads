-- Author:		Christian Carreras
-- File Name:		class_io.ads
-- File Created:	04/26/2015
-- Due Date:		05/01/2015
-- Class:		CSC 310
-- Semester:		Spring 2015
-- Instructor:		Dr. Spiegel
-- Project #:		3
-- Purpose:		Creates the charType type required for parsing and
--			values for lexemes.

package class_io is 
	
	-- each value to corresponds to a different part of a grammar
	type charType is (progsym, decsym, beginsym, endsym, typesym, readsym, 
				writesym, assignop, operator, lParen, rParen, 
				id, idrp, num, comma, colon, semicolon, badId);
			
end class_io;
