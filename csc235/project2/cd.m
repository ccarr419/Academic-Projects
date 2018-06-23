!	        Author:	Christian Carreras
!	 Creation Date:	October 4, 2014
!	      Due Date:	October 8, 2014
!	        Course:	CSC 235
!	Professor Name:	Dr. Spiegel
!	       Project:	2
!	      Filename:	cd.m
!	       Purpose:	Creates a number based off user entry. User entry is
!					the starting digit & total number of digits to be 
!					created. Digit numbers will be 0-9 in ascending order
!					After 9, the next digit will return to zero.

	.data
	.align 	4
	
prompt: !ask user for data
	.asciz 	"Enter starting digit & total #digits: "
	.align	4

outformat: !output and computation display
	.asciz	"The number, with %d digits, starting from %d is %d\n"
	.align	4	
	
informat: !how data should be entered
	.asciz	"%d %d"
	.align	4
	
error: !error message for invalid data entry
	.asciz	"Bad starting digit\n"
	.align	4

start: !initial digit variable
	.word 0	
digits: !total digits variable
	.word 0
	.global main

main:
	save	%sp, -96, %sp
	
	!prompt user to enter data
	set		prompt, %o0
	call		printf, 0
	nop
	
	!take data from user (cin >>)
	set		informat, %o0
	set		start, %o1
	set		digits, %o2
	call 	scanf
	nop
	
	!set registers with user entry values
	!start: initial digit(will be modified)
	set		start, %l1
	!load value to local register
	ld		[%l1], %l1
	!digits: total number digits(loop conditional)
	set		digits, %l2
	ld		[%l2], %l2
	!keep record of starting digit in another register
	mov		%l1, %l5
	
	!if(start < 0) return(-1);
	cmp		%l1, 0
	bl		forcequit
	nop
	
	!if(start > 9) return(-1);
	cmp		%l1, 9
	bg		forcequit

	!number = start++;
	mov		%l1, %l3
	add		%l1, 1, %l1
	
	!idx = 1;
	mov		1, %l4

loop: !do
	!if(idx >= digits) break;
	cmp		%l4, %l2
	bg		done
	
	!number = (number * 10) + start;
	mov		10, %o0
	mov		%l3, %o1
	call		.mul
	nop		!must wait for result, delay slot
	mov		%o0, %l3
	add		%l3, %l1, %l3

	!start = (start + 1) % 10;
	add		%l1, 1, %o0
	mov		10, %o1
	call		.rem
	nop		!must wait for result, delay slot
	mov		%o0, %l1	
	
	!idx++;
	add		%l4, 1, %l4
	
	!while(idx < digits);
	cmp		%l4, %l2
	bl		loop
	nop

done: !display final output and values
	set		outformat, %o0
	mov		%l2, %o1
	mov		%l5, %o2
	call		printf, 0
	mov		%l3, %o3
	
	!end program
	call		exit, 0
	mov		0, %o0

forcequit: !display error message & quit
	set		error, %o0
	call		printf, 0
	nop
	call		exit, 0
	mov		0, %o0
