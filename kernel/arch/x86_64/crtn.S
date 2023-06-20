.section .init
	/* contents of crtend.o's .init section here */
	popq %rbp
	ret

.section .fini
	/* contents of crtend.o's .fini section here */
	popq %rbp
	ret