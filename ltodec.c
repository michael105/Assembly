/* File generated from ltodec.s - , abi systemV */

/* convert a long to ascii, decimal representation. 
  This avoids a costy div instruction, instead a table 
  is precalculated and pushed onto the stack. 
  'buf' should be longer than 20 chars. 
  'prec' gives the count of digits to be represented, 
  padded with 'pad'. 
  Returns the number of digits written to buf.   
*/

int ltodec(char *buf, long l, int prec, char pad);
int ultodec(char *buf, unsigned long l, int prec, char pad);
asm( 
"ltodec: \n"
"	test %rsi,%rsi \n"
"	jns ultodec \n"
"	mov $45,%al \n"
"	stosb \n"
"	neg %rsi \n"
" \n"
"ultodec: \n"
"	xor %rax,%rax \n"
"	mov %rdi,%r9 \n"
"	push %rbx \n"
"	push %rax \n"
"	inc %rax \n"
"	mov $10,%r8 \n"
"	mov %edx,%ebx \n"
" \n"
"_ltodec_1: \n"
"	push %rax \n"
"	dec %ebx \n"
"	mulq %r8 \n"
"	jc _ltodec_3  \n"
" \n"
"	cmp %rsi,%rax \n"
"	jbe _ltodec_1 \n"
" \n"
"	mov %ecx,%eax \n"
"_ltodec_PREC: \n"
"	dec %ebx \n"
"	js  _ltodec_3 \n"
"	stosb  \n"
"	jmp _ltodec_PREC \n"
" \n"
"_ltodec_2: \n"
"	inc %eax \n"
"	sub %rcx,%rsi \n"
"	jns _ltodec_2 \n"
"	add %rcx,%rsi \n"
"	stosb \n"
"	 \n"
"_ltodec_3: \n"
"	pop %rcx \n"
"	mov $47,%eax \n"
"	test %rcx,%rcx \n"
"	jnz _ltodec_2 \n"
"	 \n"
"	// Out \n"
"	movb $0,(%rdi) \n"
"	mov %rdi,%rax \n"
"	sub %r9,%rax \n"
"	pop %rbx \n"
"	retq \n"
);


