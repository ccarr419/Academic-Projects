!********************************************************************
! Author:			Christian Carreras
! Creation Date:	November 30, 2014
! Course:			CSC 235
! Professor:		Dr. Spiegel
! Assignment:		#4
! Filename:		p4.m
! Purpose:		Asks user to enter employee information
!				based on whether they are a hourly or
!				salaried worker. Information is stored in
!				an array of 10 elements where hourly workers
!				store name, regular hours, overtime hours,
!				and hourly wage. Salaried workers store
!				name, level, and annual salary. After 10
!				employees are entered or the user chooses
!				to enter a number fewer than that, the
!				array is printed to the screen in the order
!				they were entered.
!********************************************************************
		
		define(iRegister, %l0)	! iterator register
		define(nameAdrs, %l1)	! holds address of first element in frame
		define(eltsInArray, %l2) ! number of entries
		define(eltAdrs, %l3)	! address of employee
		define(studList, -336)	! start of employee array
		
		define(empName, 0)		! employee name offset (string) 20 bytes
		define(type, 20)		! employee type offset (char) 1 byte
		
		define(regHours, 22)	! regular hours offest (half int) 2 bytes
		define(ovHours, 24)		! overtime hours offset (half int) 2 bytes
		define(hourlyWage, 26)	! hourly wage offset (half int) 2 bytes
		
		define(lvl, 22)		! level offset (char) 1 byte
		define(annSalary, 24)	! annual salary offset (half int) 2 bytes
		
		define(dummy, 8)		! dummy offset (char) 1 byte
							! holds \n from char entry
		define(maxLength, 20)	! max length of string
		
		.data
		.align 	8
	
promptName:
		.asciz 	"Enter name: "
		.align 	8
		
promptType:
		.asciz	"Hourly or salaried worker? (h or s): "
		.align	8
		
promptRegHours:
		.asciz	"Enter regular hours: "
		.align	8
		
promptOvHours:
		.asciz	"Enter overtime hours: "
		.align	8
		
promptWage:
		.asciz	"Enter wage: "
		.align	8
		
promptLvl:
		.asciz	"Enter level: "
		.align	8
		
promptSalary:
		.asciz	"Enter annual salary: "
		.align	8
		
charIn:
		.asciz	"%c%c"
		.align	8
		
intIn:	
		.asciz	"%hi"
		.align	8
		
formatHourly:
		.asciz	"Name:%20s    Type: %c    Regular Hours: %hi    Overtime Hours: %hi    Wage: $%hi\n\n"
		.align	8
		
formatSalaried:
		.asciz	"Name:%20s    Type: %c    Level: %c    Annual Salary: $%hi\n\n"
		.text
		.global	main
				
main:
		save 	%sp, (-108 - 32) & -8, %sp
		add		%fp, studList, nameAdrs
		mov		nameAdrs, eltAdrs

		call		readEmployees
		mov		eltAdrs, %o0
		call		printEmployees
		mov		eltAdrs, %o0

! end program	
done:			
		call		exit, 0
		mov		0, %o0

!********************************************************************
! Function:		readEmployees
! Parameter(s):	Base address of array Employee - import only	
! Returns:		Number of employees
! Purpose:
!********************************************************************		
		.align	8
		.global 	readEmployees
readEmployees:
		save		%sp, (-108 - 320) & -8, %sp
		mov		%i0, eltAdrs		
		call		readEmployee
		! use base address of employee as parameter
		mov		eltAdrs, %o0 
		ret
		restore

!********************************************************************
! Function:		readEmployee
! Parameter(s):	Address of Employee - import only
! Returns:		None
! Purpose:
!********************************************************************			
		.align	8
		.global	readEmployee		
readEmployee:
		save		%sp, (-108 - 32) & -8, %sp
		mov		%i0, eltAdrs
		! read name into employee address
		call		readName
		mov		eltAdrs, %o0
		
		! ask user to if employee is hourly or salaried
		set		promptType, %o0
		call		printf
		nop		
		
		! read char into employee address
		call		readChar
		add		eltAdrs, type, %o0
		! check if char entered is h or H
		! branch to hourly if entered
		ldsb		[eltAdrs+type], nameAdrs
		cmp		nameAdrs, 104
		be		hourly
		nop
		cmp		nameAdrs, 72
		be		hourly
		nop
		
salaried:
		! ask user for employee's level
		set		promptLvl, %o0
		call		printf
		nop
		call		readChar
		add		eltAdrs, lvl, %o0
		
		! ask user for employee's annual salary
		set		promptSalary, %o0
		call		printf
		nop
		call		readInt
		add		eltAdrs, annSalary, %o0
		! branch to end to avoid hourly input
		b		finish
		nop
		
hourly:
		! ask user for employee's regular hours
		set		promptRegHours, %o0
		call		printf
		nop
		call		readInt
		add		eltAdrs, regHours, %o0
		
		! ask user for employee's overtime hours
		set		promptOvHours, %o0
		call		printf
		nop
		call		readInt
		add		eltAdrs, ovHours, %o0
		
		! ask user for employee's hourly wage
		set		promptWage, %o0
		call		printf
		nop
		call		readInt
		add		eltAdrs, hourlyWage, %o0
		
finish:		
		ret
		restore

!********************************************************************
! Function:		readName
! Parameter(s):	Address where name is to be placed - import only
! Returns:		None
! Purpose:		Prompts user for name input and allocates memory
!				for a maxLength-bit string
!********************************************************************			
		.align 	8
		.global 	readName	
readName:
		save		%sp, (-108 - 20) & -8, %sp
		set		promptName, %o0
		call		printf
		mov		%i0, eltAdrs
		!		allocates memory space of maxLength bits
		call		malloc
		mov		maxLength, %o0
		st		%o0, [eltAdrs]
		! gets (get string) puts string in allocated memory space
		call		gets
		nop	
		ret
		restore

!********************************************************************
! Function:		readChar
! Parameter(s):	None
! Returns:		Character that was in input
! Purpose:		Calls scanf and places the wanted char in
!				memory space while placing dummy '\n' char
!				in a dummy memory location
!********************************************************************	
		.align	8
		.global	readChar
readChar:
		save 	%sp, (-108 - 2) & -8, %sp
		mov		%i0, eltAdrs
		set		charIn, %o0	
		mov		eltAdrs, %o1
		call		scanf
		! place carriage in dummy location
		add		eltAdrs, dummy, %o2		
		ret
		restore

!********************************************************************
! Function:		readInt
! Parameter(s):	None
! Returns:		int to adress caller's return address area
! Purpose:		Calls scanf to place int in desired memory space
!********************************************************************			
		.align	8
		.global	readInt
readInt:
		save		%sp, (-108 - 2) & -8, %sp
		mov		%i0, eltAdrs
		set		intIn, %o0		
		call		scanf
		mov		eltAdrs, %o1
		ret
		restore

!********************************************************************
! Function:		printEmployees
! Parameter(s):	Base address of array in caller's frame - import only
! Returns:		None
! Purpose:		Prints the total number of employees
!********************************************************************			
		.align	8
		.global	printEmployees
printEmployees:
		save 	%sp, (-108 - 320) & -8, %sp
		mov		%i0, eltAdrs
		call		printEmployee
		mov		eltAdrs, %o0		
		ret
		restore

!********************************************************************
! Function:		printEmployee
! Parameter(s):	Address of Employee - import only
!				Choice bit - import only
! Returns:		None
! Purpose:		Checks the tag bit to print the employee based on
!				whether the said employee is an hourly or salaried
!				worker. Output will differ.
!********************************************************************	
		.align	8
		.global	printEmployee
printEmployee:
		save		%sp, (-108 - 32) & -8, %sp
		mov		%i0, eltAdrs
		ldsb		[eltAdrs+type], nameAdrs
		 
		! if hourly, go to printHourly
		cmp		nameAdrs, 104
		be		printHourly
		nop
		cmp		nameAdrs, 72
		be		printHourly
		nop

! prints the salaried worker as name, type, level and annual salary		
printSalaried:
		set		formatSalaried, %o0
		ld		[eltAdrs], %o1
		ldsb		[eltAdrs+type], %o2
		ldsb		[eltAdrs+lvl], %o3
		ldub		[eltAdrs+annSalary], %o4
		call		printf
		nop
		! skip to end
		b		endPrint
		nop

! prints the hourly worker as name, type, regular hours, 
! overtime hours and wage		
printHourly:
		set		formatHourly, %o0
		ld		[eltAdrs], %o1
		ldsb		[eltAdrs+type], %o2
		ldub		[eltAdrs+regHours], %o3
		ldub		[eltAdrs+ovHours], %o4
		ldub		[eltAdrs+hourlyWage], %o5
		call		printf
		nop

endPrint:		
		ret
		restore	
		