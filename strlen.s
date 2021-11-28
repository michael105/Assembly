/* shows up to be faster than rep scanb; (Core2)
 same time few bytes shorter */
// int strlen(char *s);
.align 16
strlen: 
	xor %ecx,%ecx	
	dec %ecx
	xor %rax,%rax	
	jmp _strlen_Lin
_strlen_Loop:
	inc %eax 
_strlen_Lin:
	test %cl,(%rdi,%rax)
	jnz _strlen_Loop
retq

