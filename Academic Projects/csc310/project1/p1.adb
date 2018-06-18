-- Author:		Christian Carreras
-- File:			p1.adb
-- Date Created:	02/09/2015
-- Date Due:		02/15/2015
-- Class:			CSC 310
-- Instructor:		Dr. Spiegel
-- Semester:		Spring 2015
-- Purpose:		Creates a user interface in which the user can enter
--				integers into a array with a size of (10). User interface
--				controls include: inserting into the array, printing the
--				current elements of the array, change an element of the
--				array, look for an element in the array, and find the
--				average of the array. Other features include: array is
--				sorted from least to greatest, and functions to check
--				if the array is empty or full. Also searchList
--				implements a binary search due to the ordered nature
--				of the array itself.

with text_io;
use text_io;

procedure p1 is

	package number is new integer_IO (integer);
	use number;
	
	package realNumber is new float_IO (float);
	use realNumber;
	
	type intList is array (1..10) of integer;
	
	choice		: character;	-- user's choice for menu
	list			: intList;	-- list to hold integers
	value		: integer;	-- variable for input/find values
	value2		: integer;	-- variable for change values
	min, max		: integer;	-- variables for size of list
	numElts		: integer;	-- total elements in the list
	valueFloat	: float;		-- variable for float data types
	
-- Function Name:	isEmpty
-- Parameters:		numElts - integer - in only
-- Returns:		true if empty, false if not
-- Purpose:		tests if the list is empty or not
	function isEmpty(numElts: in integer) return boolean is
		begin
		if(numElts = 0) then
			return true;
		else
			return false;
		end if;
		end isEmpty;
	
-- Function Name:	isFull
-- Parameters:		max - integer - in only
--				numElts - integer - in only
-- Returns:		true if full, false if not
-- Purpose:		tests if the list is full or not
	function isFull(max: in integer; numElts: in integer) return boolean is
		begin
		if(numElts >= max) then
			return true;
		else
			return false;
		end if;
		end isFull;
		
-- Function Name:	searchList
-- Parameters:		aList - intList - in only
--				key - integer - in only
--				min - integer - in only
--				numElts - integer - in only
-- Returns:		the index of the found number,
--				or 0 if the number is not found
-- Purpose:		uses the binary search to find a
--				given element within the list
	function searchList(aList: in intList; key: in integer; min: 
	in integer; numElts: in integer) return integer is
		
		imax: integer; -- highest possible location
		imin: integer; -- lowest possible location
		imid: integer; -- approximate mid-point
		begin
		imax := numElts;
		imin := min;
		
		while imax >= imin loop
			imid := (imax + imin) / 2;
			if aList(imid) = key then
				return imid; -- midpoint is the value being searched for
				
			elsif aList(imid) < key then
				imin := imid + 1; -- value must be greater than midpoint
				
			else
				imax := imid - 1; -- value must be less than midpoint
				
			end if;			
		end loop;
		
		return 0; -- value not in the list
		end searchList;
		
-- Function Name:	swap
-- Parameters:		x - integer - in/out
--				y - integer - in/out
-- Returns:		n/a
-- Purpose:		gives the given x value to y and the given y value to x
--				is a helper function to sort
	procedure swap(x: in out integer; y: in out integer) is
		temp: integer; -- temporary holder to hold x value
		begin
		temp := x;
		x := y;
		y := temp;
		end swap;
	
-- Function Name:	sort
-- Parameters:		aList - intList - in/out
--				idx - integer - in only
--				numElts - integer - in only
-- Returns:		n/a
-- Purpose:		sorts the list from least to greatest by using the given
--				index of the value to be sorted. Sort checks it immediate
--				neighbours and swaps values if necessary
	procedure sort(aList: in out intList; idx: in integer; numElts: in integer) is
		spot: integer; -- current spot of the given index
		begin
		spot := idx;
		
		if(isEmpty(numElts)) then
			return; -- list is empty and does not need to be sorted
			
		elsif(numElts = 1) then
			return; -- list has only one element, no need to sort
			
		else
			while(spot > 0) loop
				if(spot = numElts) then -- if the value was inserted
					if(aList(spot) < aList(spot-1)) then
						-- check index if less than left neighbour
						swap(aList(spot), aList(spot-1));
						spot := spot - 1; -- swap and continue checking
					else
						return; -- already greatest value in list
					end if;
				elsif(spot = 1) then -- if value changed was first in list
					if(aList(spot) > aList(spot+1)) then
						-- check index if greater than right neighbour
						swap(aList(spot), aList(spot+1));
						spot := spot + 1; -- swap and continue checking
					else
						return; -- already smallest value in list
					end if;
				else -- index is in the middle of the list
					-- check both right and left neighbours
					if(aList(spot) < aList(spot-1)) then
						swap(aList(spot), aList(spot-1));
						spot := spot - 1;
					
					elsif(aList(spot) > aList(spot+1)) then
						swap(aList(spot), aList(spot+1));
						spot := spot + 1;
					
					else
						return; -- value is already where it needs to be
					end if;
				end if;
			end loop;
		end if;
		end sort;

	
-- Function Name:	printList
-- Parameters:		aList - intList - in only
--				numElts - integer - in only
-- Returns:		n/a
-- Purpose:		prints the list in its current least to greatest form
	procedure printList(aList: in intList; numElts: in integer) is
		i: integer;
		begin
		i := 1;
		text_io.put("Current list: ");
		while(i <= numElts) loop
			put(aList(i),0);
			text_io.put(" ");
			i := i + 1;
		end loop;
		text_io.new_line;
		end printList;
		
-- Function Name:	insert
-- Parameters:		aList - intList - in/out
--				numElts - integer - in/out
--				value - integer - in only
--				max - integer - in only
-- Returns:		n/a
-- Purpose:		takes a value and tries to insert it into the list
--				if the list is full, it fails, otherwise the value is
--				inserted into the list and the list is then sorted
	procedure insert(aList: in out intList; numElts: in out integer; value: 
	in integer; max: in integer) is
		begin
		if(isFull(max, numElts)) then -- check if list is already full
			text_io.put_line("Error. The list is full. Unable to insert");
		else
			aList(numElts+1) := value; -- add new value to end of list
			numElts := numElts + 1; -- increment number of elements in list
			sort(aList, numElts, numElts); -- new element inserted, sort
			printList(aList, numElts); -- print list to see new value
		end if;
		end insert;

-- Function Name:	change
-- Parameters:		aList - intList - in/out
--				key - integer - in only
--				min - integer - in only
--				numElts - integer - in only
--				value - integer - in only
-- Returns:		n/a
-- Purpose:		takes the key value and searches the list for the value
--				if the list is empty, the change will fail
--				otherwise it will change its value to the given value and 
--				will sort the list from that index print the list
--				*PRE: list must contain the key!*
	procedure change(aList: in out intList; key: in integer; min:
	in integer; numElts: in integer; value: in integer) is
		idx : integer; -- value to hold searchList return value
		begin
		if(isEmpty(numElts)) then -- list is empty, no need to do anything
			text_io.put_line("Error. The list is empty. Unable to change");
		else
			idx := searchList(aList, key, min, numElts);
			aList(idx) := value; -- change element to given value
			sort(aList, idx, numElts); -- new element, must sort
			printList(aList, numElts); -- show changed element in list
		end if;
		end change;

-- Function Name:	findAvg
-- Parameters:		aList - integer - in only
--				min - integer - in only
--				numElts - in only
-- Returns:		float - average of the list
-- Purpose:		finds the sum of the elements of the list and divides by
--				the total number of elements in the list to find the
--				average; average is returned as a float number
	function findAvg(aList: in intList; min: in integer; numElts: in integer)
	return float is
		sum : integer; -- sum of all the elements in the list
		i : integer; -- iterator for loop
		average : float; -- average of the list
		begin 
		sum := 0; -- initial instantiation of zero
		i := 1;
		if(isEmpty(numElts)) then
			return 0.0; -- empty list, must be zero
			
		elsif(numElts = 1) then
			return float(numElts); -- one element, average is that number
			
		else
			while(i <= numElts) loop -- add all elements together, find sum
				sum := sum + aList(i);
				i := i + 1;
			end loop; -- divide sum by total elements
			average := float(sum) / float(numElts);
			return average;
		end if;
		end findAvg;
				
-- Function Name:	menu
-- Parameters:		n/a
-- Returns:		n/a
-- Purpose:		displays the menu/choices for user interface
	procedure menu is
		begin
		text_io.new_line;
		text_io.put_line("Select:");
		text_io.put_line("P)rint Array");
		text_io.put_line("L)ook for Element");
		text_io.put_line("C)hange an Element");
		text_io.put_line("I)nsert New Element");
		text_io.put_line("F)ind Average");
		text_io.put_line("Q)uit");
		text_io.new_line;
		text_io.put("Enter your choice: ");
		end menu;
		
begin
	min := 1; -- minimum boundary of list
	max := 10; -- maximum boundary of list
	numElts := 0; -- elements in list, currently empty
	choice := ' ';
	while choice /= 'q' loop -- loops until user decides to quit
		menu;
		get(choice);
		
		if choice = 'p' then -- print array
			printList(list, numElts);
			
		elsif choice = 'l' then -- look for element
			text_io.put("Enter value to find: ");
			get(value);
			if searchList(list, value, min, numElts) > 0 then
				text_io.put_line("Found!");
			else -- value is not in the list
				text_io.put_line("Error. Not found..");
			end if;
			
		elsif choice = 'c' then -- change an element
			text_io.put("Enter value to change: ");
			get(value); -- make sure value is in list before changing it
			if searchList(list, value, min, numElts) = 0 then
				text_io.put_line("Error. That value does not exist..");
			else -- the value is in the list, ask for new value
				text_io.put("What do you want to change it to? ");
				get(value2);
				change(list, value, min, numElts, value2);
			end if;
			
		elsif choice = 'i' then -- insert new element
			text_io.put("Enter value to insert: ");
			get(value);
			insert(list, numElts, value, max);
			
		elsif choice = 'f' then -- find average
			valueFloat := findAvg(list, min, numElts);
			text_io.put("The average of the list is: ");
			-- display with 2 decimal digits
			realNumber.put(item=>valueFloat, fore=>0, aft=>2, exp=>0);
			text_io.new_line;
			
		elsif choice = 'q' then -- quit
			text_io.put_line("Goodbye.");
			
		else -- user entered none of the choices
			text_io.put_line("Error. That is not a valid choice..");
		end if;	
	end loop;
		
end p1;
