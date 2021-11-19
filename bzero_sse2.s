// bzero, sse2 version.
// This is about ten times faster than bzero,
// but the address of s has to be aligned to a boundary of 16 Bytes.
// void bzero_sse2(void *s, int n);
bzero_sse2: 
	pxor %xmm1,%xmm1 
	xor %eax,%eax 
	mov %esi,%ecx 
	and $0xf,%ecx 
	shr $4,%rsi 
	dec %rsi 
	js _bzero_sse2_repb  
 
	shl $4,%rsi 
	add %rdi,%rsi 
_bzero_sse2_mxbl: 
 	movdqa %xmm1,(%rdi) 
	add $16,%rdi 
	cmp %rdi,%rsi 
	jns _bzero_sse2_mxbl 
 
_bzero_sse2_repb: 
	rep stosb  
	retq 


