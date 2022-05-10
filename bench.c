#if 0
COMPILE start printf ltodec itodec PRINTS exit ultodec ltodec signal memset itohex writesl writes
COMPILE gettimeofday asctime strftime setitimer strlen strnlen ansicolors rand strcpy strlen \
			  srand ultohex memmove
mini_buf 4000
STRIPFLAG '-march=core2 -mtune=core2'
OPTFLAG '-Os'
#FULLDEBUG

DEFINE ASM_amd64


return
#endif


int volatile bench;
unsigned long volatile count;
void sigalrm(int sig){
	if ( bench == 2 ){
		bench=1;
		count=0;
	} else {
		bench=0;
	}
}


int forwarded(int a, char *b ){
	//printf("fw: %d\n",a);
	//printf("adr: %p\n",b);
	//prints(b,"\n===\n");
	asm volatile("retq\njmp 2f\nnop\nnop\nnop\nnop\nnop\nnop\n1:");
	asm volatile("jmp 1f\nnop\nnop\nnop\nnop\nnop\nnop\n1:");
	asm volatile("jmp 1\nnop\nnop\nnop\nnop\nnop\nnop\n2:");
	return(a=a+a*3300);
}
int va(int a, ...);

asm( R"(
va:
mov %rsi,%rax
retq
)" );





MAIN{
		
	bench = 1;
	signal( SIGVTALRM, sigalrm );
	struct itimerval itv = { {0,200000},{0,50000} }; // second time: warmup ( cpuclock, etc )

	// itimer_virtual - only process time.
	// itimer_prof - process and system time
#define STBENCH	setitimer( ITIMER_VIRTUAL, &itv, 0 );\
	bench=1;\
	while( bench )\
		asm("nop");\
	bench=1; count = 0;

#define BENCH(src) STBENCH;while(bench){ count++; src; }; printf("Count: %u\n",count);

	BENCH();

	STBENCH;
	printf("count: %d\n",count);
	//setitimer( ITIMER_VIRTUAL, &itv, 0 );\
	bench=1;
	count=0;
	asm volatile ( R"(
	xor %%rax,%%rax
	mov $0xf,%%rcx
.align 16
L:
	inc %%rax
	test %%cl,%1
	jnz L

	)" : "=a"(count) : "m"(bench) : "rcx" );

	printf("count: %d\n",count);

	int r = va(23,57);
	printf("va: %d\n",r);
	forwarded(77,"Ok");


long fw(int a, char *b);
asm(R"(
jmp hop
fw:
//	pusha
	push %rdi
	push %rsi
	mov $1,%r14
	xor %rbx,%rbx
LP:
	inc %rbx
	mov (%rsp),%rsi
	mov 8(%rsp),%rdi
	callq forwarded
	test %r14,bench
	jnz LP
	pop %rax
	pop %rax
	mov %rbx,%rax
	retq
hop:
)");



	STBENCH;
	long l = 0;
	l = fw(33,"xx");

	printf("lx: %ld\n",l);





long fw2(void *code, ... );
asm(R"(
jmp 9f
fw2:
	push %rbx
	push %r15
	push %r9
	push %r8
	push %rcx
	push %rdx
	push %rsi
	mov %rdi,%r15
	xor %rbx,%rbx #counter
	jmp 2f

.align 64
1:
	inc %rbx
2:
// setup arguments
// push/pop are 1byte opcodes
// movq/leaq would have 6 to 8 bytes
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
/*
	mov (%rsp),%rdi
	mov 8(%rsp),%rsi
	mov 16(%rsp),%rdx
	mov 24(%rsp),%rcx
	mov 32(%rsp),%r8
	mov 40(%rsp),%r9
*/

	//lea (%rsp),%rdi
	//lea 8(%rsp),%rsi
	//lea 16(%rsp),%rdx

	printsl("==========");
	STBENCH;

	l = fw2( &forwarded, 11, "zzzzzzzzzzzzzzzzzzzz" );

	printf("l: %ld\n",l);
	
	void f(int l, char *s){ printf("ok\n"); printf("l: %d\ns: %s\n",l,s); };

	printsl("==========");

	l = fw2( &f, 17, "vx" );

	printf("l: %ld\n",l);
	char buf[2400];
	char buf2[2400];

	printsl("xxx");
	bench = 2;
	l = fw2( &memmove, buf, buf2, 1024 );
	printf("l: %ld\n",l);

	STBENCH;
	l = fw2( &memmove, buf, buf2, 1024 );
	printf("l: %ld\n",l);



	return(0);
}
