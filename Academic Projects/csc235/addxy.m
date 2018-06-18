/*******************************************************
*         File:  addxy.m
*          Dir:  cis235/suns/ch02
*         Date:  February, 1999
*       Author:  HGG                                 
*     Computer:  KUNET suns
*    Assembler:  sa addxy
*      Compile:  gcc 
*      Execute:  a.out                               
*      Purpose:  To read two integers x and y, add them,
*                put the result in sum and print out.
*******************************************************/

	.data
	.align 8
prompt:	.asciz	"Enter two integers (^D to quit): "
	.align	8
formati:
	.asciz	"%d %d"
	.align 8
formato:
	.asciz	"x = %d, y = %d, sum = %d\n"
	.align 4

! automatic data for a program
	define(x, -20)
	define(y, -24)
	define(sum, -28)

	.text
	.align 4
	.global main
main:
	save %sp, (-108 -12) & -8, %sp

loop:	!while (printf(prompt),
	sethi	%hi(prompt), %o1
	call	printf,0
	or	%o1, %lo(prompt), %o0

	! scanf(formati, &x, &y)  == 2)
	set 	formati, %o0     ! formati address in o0
        add 	%fp, x, %o1      ! address of x into o1
	call 	scanf,0
	add	%fp, y, %o2      ! address of y into o2


	cmp 	%o0, 2    	 ! 2 integers read? is better else
	bne	done	         ! bad data causes an infinite loop

	! sum = x + y;  NOTE how x and y are loaded from memory

	! o1 = x 
        ld 	[%fp + x], %o1

	! o2 = y
        ld 	[%fp + y],%o2  ! 

	add	%o1, %o2, %o3     ! save in o's for printf
        st 	%o3, [%fp + sum]

	! printf(formato, x, y, sum)
	sethi	%hi(formato),%l1
	call 	printf,0
	or 	%l1,%lo(formato),%o0
	b	loop
	nop

done:	! exit
	call	exit, 0
	mov	0, %o0


