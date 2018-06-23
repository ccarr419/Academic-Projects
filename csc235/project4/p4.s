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
		
			! iterator register
			! holds address of first element in frame
		 ! number of entries
			! address of employee
			! start of employee array
		
				! employee name offset (string) 20 bytes
				! employee 20 offset (char) 1 byte
		
			! regular hours offest (half int) 2 bytes
				! overtime hours offset (half int) 2 bytes
			! hourly wage offset (half int) 2 bytes
		
				! level offset (char) 1 byte
			! annual salary offset (half int) 2 bytes
		
				! 8 offset (char) 1 byte
							! holds \n from char entry
			! max length of string
		
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
		add		%fp, -336, %l1
		mov		%l1, %l3

		call		readEmployees
		mov		%l3, %o0
		call		printEmployees
		mov		%l3, %o0

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
		mov		%i0, %l3		
		call		readEmployee
		! use base address of employee as parameter
		mov		%l3, %o0 
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
		mov		%i0, %l3
		! read name into employee address
		call		readName
		mov		%l3, %o0
		
		! ask user to if employee is hourly or salaried
		set		promptType, %o0
		call		printf
		nop		
		
		! read char into employee address
		call		readChar
		add		%l3, 20, %o0
		! check if char entered is h or H
		! branch to hourly if entered
		ldsb		[%l3+20], %l1
		cmp		%l1, 104
		be		hourly
		nop
		cmp		%l1, 72
		be		hourly
		nop
		
salaried:
		! ask user for employee's level
		set		promptLvl, %o0
		call		printf
		nop
		call		readChar
		add		%l3, 22, %o0
		
		! ask user for employee's annual salary
		set		promptSalary, %o0
		call		printf
		nop
		call		readInt
		add		%l3, 24, %o0
		! branch to end to avoid hourly input
		b		finish
		nop
		
hourly:
		! ask user for employee's regular hours
		set		promptRegHours, %o0
		call		printf
		nop
		call		readInt
		add		%l3, 22, %o0
		
		! ask user for employee's overtime hours
		set		promptOvHours, %o0
		call		printf
		nop
		call		readInt
		add		%l3, 24, %o0
		
		! ask user for employee's hourly wage
		set		promptWage, %o0
		call		printf
		nop
		call		readInt
		add		%l3, 26, %o0
		
finish:		
		ret
		restore

!********************************************************************
! Function:		readName
! Parameter(s):	Address where name is to be placed - import only
! Returns:		None
! Purpose:		Prompts user for name input and allocates memory
!				for a 20-bit string
!********************************************************************			
		.align 	8
		.global 	readName	
readName:
		save		%sp, (-108 - 20) & -8, %sp
		set		promptName, %o0
		call		printf
		mov		%i0, %l3
		!		allocates memory space of 20 bits
		call		malloc
		mov		20, %o0
		st		%o0, [%l3]
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
!				memory space while placing 8 '\n' char
!				in a 8 memory location
!********************************************************************	
		.align	8
		.global	readChar
readChar:
		save 	%sp, (-108 - 2) & -8, %sp
		mov		%i0, %l3
		set		charIn, %o0	
		mov		%l3, %o1
		call		scanf
		! place carriage in 8 location
		add		%l3, 8, %o2		
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
		mov		%i0, %l3
		set		intIn, %o0		
		call		scanf
		mov		%l3, %o1
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
		mov		%i0, %l3
		call		printEmployee
		mov		%l3, %o0		
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
		mov		%i0, %l3
		ldsb		[%l3+20], %l1
		 
		! if hourly, go to printHourly
		cmp		%l1, 104
		be		printHourly
		nop
		cmp		%l1, 72
		be		printHourly
		nop

! prints the salaried worker as name, 20, level and annual salary		
printSalaried:
		set		formatSalaried, %o0
		ld		[%l3], %o1
		ldsb		[%l3+20], %o2
		ldsb		[%l3+22], %o3
		ldub		[%l3+24], %o4
		call		printf
		nop
		! skip to end
		b		endPrint
		nop

! prints the hourly worker as name, 20, regular hours, 
! overtime hours and wage		
printHourly:
		set		formatHourly, %o0
		ld		[%l3], %o1
		ldsb		[%l3+20], %o2
		ldub		[%l3+22], %o3
		ldub		[%l3+24], %o4
		ldub		[%l3+26], %o5
		call		printf
		nop

endPrint:		
		ret
		restore	
		