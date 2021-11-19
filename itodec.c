/* File generated from itodec.s - , abi systemV */

int itodec(char*buf, unsigned int i, int prec,char pad );
int uitodec(char*buf, unsigned int i, int prec,char pad );

asm( 
" \n"
"itodec: \n"
"	test %esi,%esi \n"
"	jns asm_uitodec \n"
"	mov $45,%al \n"
"	stosb \n"
"	neg %esi \n"
" \n"
"uitodec: \n"
"	mov %esi,%eax \n"
"	pushw $0x800 \n"
"	mov %rdx,%r9 \n"
"	mov $0xcccccccd,%r10 \n"
"_itodec_MUL: \n"
"	mulq %r10  \n"
"	shr $35,%rax  \n"
"	imul $10,%rax,%r8  \n"
"	sub %r8,%rsi \n"
"	add $48,%esi  \n"
"	pushw %si  \n"
"	dec %r9 \n"
"	mov %rax,%rsi \n"
"	test %rax,%rax \n"
"	jnz _itodec_MUL \n"
"	 \n"
"	mov %cl,%al  \n"
"_itodec_WR0:  \n"
"	dec %r9w  \n"
"	js _itodec_WRITE \n"
"	stosb \n"
"	jmp _itodec_WR0 \n"
" \n"
"_itodec_WRITE: \n"
"	popw %ax \n"
"	stosb \n"
"	test $0x800,%ax \n"
"	jz _itodec_WRITE \n"
"	 \n"
"	retq \n"
" \n"
);


