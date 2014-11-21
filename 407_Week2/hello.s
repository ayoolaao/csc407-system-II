	.file	"hello.c"
.globl OS_EVERYTHING_OKAY
	.bss
	.align 4
	.type	OS_EVERYTHING_OKAY, @object
	.size	OS_EVERYTHING_OKAY, 4
OS_EVERYTHING_OKAY:
	.zero	4
	.section	.rodata
.LC0:
	.string	"Hello world!"
	.text
.globl hello_world
	.type	hello_world, @function
hello_world:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$.LC0, (%esp)
	call	puts
	leave
	ret
	.size	hello_world, .-hello_world
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$4, %esp
	call	hello_world
	movl	OS_EVERYTHING_OKAY, %eax
	addl	$4, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-50)"
	.section	.note.GNU-stack,"",@progbits
