/* first attempt at format string bug exploitation: to reveal data. Program was launched as:
	./format "%d %x %x"
	output showed that the firt %d gave me 1000, which was precisely the value I fed to rsi. This is because printf takes its format string's address from rdi and its first argument (either direct value or address depending on the type of value) from rsi
the question is: where are the rest coming from??

ANSWER: just how printf () normally works. printf takes the first argument (the main string + format string) from rdi, second from rsi, third from rdx and so on. The second value, i.e., the one after 1000 is the value stored in RDX register at that instance. Similarily next depends on some other gen. purp. register. CASE SOLVED
*/

#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv []) {
	__asm__ __volatile__ (
		"pushq %rsi\n\t"
		"movq $10000, %rsi\n\t"
	);

	printf (argv [1]);
	printf ("\n\n");

	__asm__ __volatile__ (
		"popq %rsi\n\t"
	);

	return (0);
}
