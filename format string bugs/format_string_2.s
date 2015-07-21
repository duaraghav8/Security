/* Format string bug exploited (well, kinda -_-")
	the below assembly is that generated by gcc for the following C code. However, after generating the assembly, there was 1 addition made:
	to load the address of counter into RSI reg. This is because printf () takes its 2nd argument from RSI.

#include <stdio.h>
int main (int argc, char *argv []) {
        int counter = 55555;
        printf (argv [1]);

        return (0);
}

now compile and run like this:
	./format_string_bug_2 "xxxxxxxxxxxxxxx %n"
	this writes 15 bytes (15 'x') on to the string, then writes 15 to counter because %n takes pointer to an integer and stores the no. of bytes
	printed thus far. because printf ()takes its second argument from rsi, I had to load counter's address into rsi
	and the, TA-DA!!!
*/

	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$55555, -4(%rbp)
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	movl	$0, %eax

//	THE LINE BELOW WAS ADDED IN THE ASSEMBLY:- address of counter passed into rsi
	leaq	-4 (%rbp), %rsi

	call	printf
	movl	$0, %eax
	leave
	ret
