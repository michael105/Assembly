// int strlen(const char*str);
strlen:
	xor %eax,%eax	
	test %rdi,%rdi
	jz _strlen_RET
	xor %ecx,%ecx
	dec %ecx
	repne scasb	
	sub %ecx, %eax	
	sub $2, %eax
_strlen_RET:
	retq

