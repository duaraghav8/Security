#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BLOCK_SIZE sizeof (data)
#define MEMORY_SIZE 135168

typedef struct meta_data* info;
typedef struct meta_data {
	int size;
	int free;
	struct meta_data *next;
	struct meta_data *prev;
} data;

void* memory (int size) {
	if (size > MEMORY_SIZE) {
		//we will not focus on this case right now
		return (NULL);
	}

//	void *current = (void *) sbrk (0);
	int *final = (int *) sbrk (MEMORY_SIZE);

	if (final == (int *) -1) {
		return (NULL);
	}
	data block;

	block.size = size;
	block.free = 0;
	block.next = (int *)(final + BLOCK_SIZE + size);
	block.prev = NULL;

	strcpy ((char *)final, (char *) &block);
	final += BLOCK_SIZE;

	return ( (void *) final );
}

int main (int argc, char *argv []) {
	int *number = (int *) memory (sizeof (int) * 20);
	for (int i = 0; i < 20; i++) {
		number [i] = (i * i);
		printf ("%d\n", number [i]);
	}

	return (0);
}
