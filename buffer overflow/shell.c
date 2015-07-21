/*program successfully overwrites the return address on the stack with the address of the shellcode, but fails to halt nevertheless. Receive a SGSEGV. The shellcode is the opcode translation of the following assembly:

	movl $1, %eax
	movl $0, %ebx
	int $0x80

for exit system call
*/

#include <stdio.h>
void branch (void) {
	printf ("Should not print\n");
}
/*char shellcode [] =
                "\xb8\x01\x00\x00\x00"
                "\xbb\x00\x00\x00\x00"
                "\xcd\x80";

//below is a better version of this shellcode (uses interrupt to exit with status 0, but removes all the nulls (\x00) from above shellcodes.
//this makes sure that our whole string is executed and not terminated upon encountering the first \x00 NULL value
*/
char shellcode [] =
		"\x31\xc0"
		"\xb0\x01"
		"\x31\xdb"
		"\xcd\x80";

void core (void) {
	int *ret;

	ret = (int *)&ret + 4;
	(*ret) = (int) shellcode;
//	branch ();
}
int main () {
	core ();
	branch ();
	return (0);
}
