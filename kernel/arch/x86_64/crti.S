.section .init
.global _init
.type _init, @function
_init:
	push %rbp
	movq %rsp, %rbp
	/* contents of crtbegin.o's .init section here */

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %rbp
	movq %rsp, %rbp
	/* contents of crtbegin.o's .fini section here */