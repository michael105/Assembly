// int asm_itodec(char*buf, unsigned int i, int prec,char pad );
// int asm_uitodec(char*buf, unsigned int i, int prec,char pad );

asm_itodec:
	test %esi,%esi
	jns asm_uitodec
	mov $45,%al
	stosb
	neg %esi

asm_uitodec:
	mov %esi,%eax
	pushw $0x800
	mov %rdx,%r9
	mov $0xcccccccd,%r10
LMUL:
	mulq %r10 /* rax=rax*r10 */
	shr $35,%rax /* rax is now rax/10 */
	imul $10,%rax,%r8 
	sub %r8,%rsi
	add $48,%esi 
	pushw %si 
	dec %r9
	mov %rax,%rsi
	test %rax,%rax
	jnz LMUL
	
	mov %cl,%al /* pad */
LWR0: 
	dec %r9w /* prec digits */
	js LWRITE
	stosb
	jmp LWR0

LWRITE:
	popw %ax
	stosb
	test $0x800,%ax
	jz LWRITE
	
	retq

