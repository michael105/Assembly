// bzero( void *s, unsigned int n ) 
bzero:
	xor %eax,%eax
	mov %esi,%ecx
	rep stosb 
	retq
