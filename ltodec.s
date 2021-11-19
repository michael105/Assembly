/* convert a long to ascii, decimal representation.
  This avoids a costy div instruction, instead a table
  is precalculated and pushed onto the stack.
  'buf' should be longer than 20 chars.
  'prec' gives the count of digits to be represented,
  padded with 'pad'.
  Returns the number of digits written to buf.  
*/

// int ltodec(char *buf, long l, int prec, char pad);
// int ultodec(char *buf, unsigned long l, int prec, char pad);
asm_ltodec:
	test %rsi,%rsi
	jns asm_ultodec
	mov $45,%al
	stosb
	neg %rsi

asm_ultodec:
	xor %rax,%rax
	mov %rdi,%r9
	push %rbx
	push %rax
	inc %rax
	mov $10,%r8
	mov %edx,%ebx

L1:
	push %rax
	dec %ebx
	mulq %r8
	jc L3 /* overflow,>64bit */
IL:
	cmp %rsi,%rax
	jbe L1

	mov %ecx,%eax
LPREC:
	dec %ebx
	js  L3
	stosb 
	jmp LPREC

L2:
	inc %eax
	sub %rcx,%rsi
	jns L2
	add %rcx,%rsi
	stosb
	
L3:
	pop %rcx
	mov $47,%eax
	test %rcx,%rcx
	jnz L2
	
	// Out
	movb $0,(%rdi)
	mov %rdi,%rax
	sub %r9,%rax
	pop %rbx
	retq
