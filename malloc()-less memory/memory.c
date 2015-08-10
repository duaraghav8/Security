#include <stdio.h>
#include <unistd.h>		//header containing the brk () and sbrk ()
#include <errno.h>

int main (int argc, char *argv []) {
	void *current_address = sbrk (0);	//sbrk (0) is a special case where it doesn't extend the memory, but simply returns our current last memory address
	printf ("Current last address: %p\n", current_address);
	int blocks = 0;

	int size = sizeof (current_address);
	if (size == 8) {
		printf ("You're running a 64-bit Machine. 1 memory block is 8 bytes.\n");
	}
	else if (size == 4) {
		printf ("You're running a 32-bit Machine. 1 memory block is 4 bytes.\n");
	}

	printf ("How many blocks do you wish to extend your memory by: ");
	scanf ("%d", &blocks);

	sbrk (blocks * size);		//we take the number of blocks we want to extend from user. Multiply it by the amount of memory 1 block consumes (8 bytes for 64-bit, 4 for 32) and give this incremental value to sbrk () for memory extension.
	void *new_addr = sbrk (0);	//check the new last address again.

	printf ("Memory extended. New last address : %p\n", new_addr);
	perror ("Error Description / Success");

	return (0);
}
