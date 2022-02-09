#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static inline void outb(uint16_t port, uint32_t value) {
	asm("out %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}

static inline uint32_t inb(uint16_t port) {
	uint32_t ret;
	asm("in %1, %0" : "=a"(ret) : "Nd"(port) : "memory" );
	return ret;
}

void print(const char *str) {
	outb(0xEA, (uintptr_t) str);
}

int exits(void) {
	return inb(0xEB);
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	char *p = (char*) malloc(50*sizeof(char));
	p = "Hello, world!\n";

	outb(0xEA, (uintptr_t) p);
	// print(p);
	// print(p);
	// int num_exits = exits();
	// // num to ascii (for simplicity assume single digit)
	// p[0] = '0'+num_exits;
	// // set null char
	// p[1] = '\0';
	// // print result
	// print(p);

	*(long *) 0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
