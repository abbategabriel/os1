typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;


/*
What does this do? 
each symbol in the linker script is defined using extern char 
char type isnt important - we really just care about the addresses. 
we use the [] because that will return the actual start address of the region -
and not the element at the 0th byte.
*/
extern char __bss[], __bss_end[], __stack_top[];

/*
initializes the bss section to zero (0 is passed into the second argument)
*/
void *memset(void *buf, char c, size_t n) {
	uint8_t *p = (uint8_t *)buf;
	while(n--)
		*p++ = c;
	return buf;
}

void kernel_main(void) {
	memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

	for(;;);
}

//entry point into the kernel 
__attribute__((section(".text.boot"))) //controls placement of the code in the linker script.  (places at 0x80200000)
__attribute__((naked)) //tells compiler not to generate un needed code before and after the body of the function
void boot(void) {
	__asm__ __volatile__(
		"mv sp, %[stack_top]\n" //set stack pointer
		"j kernel_main\n" //jump to kernel main function
		:
		: [stack_top] "r" (__stack_top) //stack top address to %[stack_top]
	);
}





