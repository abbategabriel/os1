ENTRY(boot)

SECTIONS {
	. = 0x80200000;

	.text :{
		KEEP(*(.text.boot));
		*(.text .text.*);
	}

	.rodata : ALIGN(4) {
		*(.rodata .rodata.*);
	}

	.data : ALIGN(4) {
		*(.data .data.*);
	}

	.bss : ALIGN(4) {
		__bss = .;
		*(.bss .bss.* .sbss .sbss.*);
		__bss_end = .;
	}

	/*. = current address, advances as data is placed.*/ 

	. = ALIGN(4); /*align w/ 4 byte address.*/
	. += 128 * 1024; /*128KB - advance current address by 128KB*/ 
	__stack_top = .; /*current location is the stack top - dremove 4 bytes to add to stack and add 4 bytes to remove from it.*/
}
