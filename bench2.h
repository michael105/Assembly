
int volatile bench;
unsigned long volatile count;
void sigalrm(int sig){
	if ( (bench & 3) == 2 ){
		bench--;
		count=0;
	} else if ( bench & 1 ){
		bench--;
		if ( bench & 4 ){ // save system elapsed time
		}
	}
}






long bench(void *code, ... );
asm(R"(
jmp 9f
bench:
	push %rbx
	push %r15
	push %r9
	push %r8
	push %rcx
	push %rdx
	push %rsi
	mov %rdi,%r15
	xor %rbx,%rbx #counter
	mov $2,bench
	jmp 2f

.align 64
1:
	inc %rbx
2:
// setup arguments
// push/pop are 1byte opcodes
// movq/leaq would have 6 to 8 bytes
// having more than 28 Bytes in the inner loop also has a "performance drop" here,
// most possibly cause the cacheline of 32B.
// Again, as someone else showed (have to look it up), 
// it's better to keep all sizes
// a little bit below the cachesizes
	pop %rdi
	pop %rsi
	pop %rdx
	pop %rcx
	push %rcx
	push %rdx
	push %rsi
	push %rdi

	callq *%r15
	testb $0x1,bench 
	jnz 1b  #count, bench==1
	testb $0x2,bench
	jnz 2b  #warmup, bench==2
	
	mov %rbx,%rax
	add $40,%rsp
	pop %r15
	pop %rbx

	retq
9:
)");















