/* program is a proof of concept of execution redirection. It redirects core () to execute getpid () system call before causing a segmentation
violation.
NOTE: causes SIGSEGV during real time execution, but in GDB successfully executes getpid (), return control to main () and exits normally after executing branch (). WTF?? */

#include <stdio.h>
void branch (void) {
	printf ("Should not print\n");
}

void core (void) {
	int *ret;

	ret = (int *)&ret + 2;
//	(*ret) = (int) shellcode;
	(*ret) = (int) (0x7ffff7ad6e10);
	__asm__ __volatile__ (
		"pushq $10\n"
	);
}
int main () {
	core ();
	branch ();
	return (0);
}
