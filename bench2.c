#if 0
COMPILE fprintf printf fopen ultodec ultohex signal itodec \
	fclose malloc_brk 

mini_buf 4000

return
#endif


int volatile bench;
void sigalrm(int sig){
	if ( bench & 3 ){
		bench--;
	} 
	
	//if ( bench & 4 ){ // save system elapsed time
}




// benchmark a function, with up to four arguments 
// Inline assembly has amongst others the advantage, that calls 
// to the function will not get optimized out
// by gcc.
// This tries to minimize the impact of loading the code into the cachelines.
long fbench(void *code, ... );
asm(R"(
jmp 9f
fbench:
	push %rbx
	push %r15
	push %r9
	push %r8
	push %rcx
	push %rdx
	push %rsi
	mov %rdi,%r15
	xor %rbx,%rbx #counter
	movq $2,bench
	jmp 2f

.align 64
1:
	inc %rbx
2:
// setup arguments
// push/pop are 1byte opcodes
// movq/leaq would have 6 to 8 bytes
// having more than 28 Bytes in the inner loop also has a performance drop here,
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
	cmp $0x1,bench 
	je 1b  #count, bench==1
	ja 2b  #warmup, bench>1
	
	mov %rbx,%rax
	add $40,%rsp
	pop %r15
	pop %rbx

	retq
9:
)");


typedef struct { 
	FILE *file;
	char *name[32];
} benchstr;

void bzero( void *s, unsigned int n ); 
asm( R"(
bzero:
	xor %eax,%eax
	mov %esi,%ecx
	rep stosb 
	retq
)" );

void bzero_sse2(void *s, int n);
asm( R"(
bzero_sse2: 
	xor %eax,%eax 
	cmp $15,%esi
	jg 5f
	mov %esi,%ecx
	jmp 3f
5:
	test $0xf,%rdi
	jz 4f /* address is aligned */
	mov %rdi,%rcx 
	and $0xf,%ecx 
	sub $16,%ecx
	neg %ecx
	sub %ecx,%esi
	rep stosb

4:
	mov %esi,%ecx
	and $0xf,%ecx  /* rest, modulo 16 */
1:
	shr $4,%rsi 
	dec %rsi 
	js 3f
 
	pxor %xmm1,%xmm1 
	shl $4,%rsi 
	add %rdi,%rsi 
2:
 	movdqa %xmm1,(%rdi) 
	add $16,%rdi 
	cmp %rdi,%rsi 
	jns 2b
 
3:
	jecxz 9f
	rep stosb  
9:
	retq 
)" );




int main(int argc, char **argv){

	//char __attribute__((aligned(16)))buf[32000];
#define BUFFER 1024*1024*64
	char *buf = malloc_brk( BUFFER ) ;
	 buf = buf - ( (long)buf%16 ) + 16; // align
	printf("buf: %p\n",buf);
//	char *buf = &_buf[0];
	long count = 0;

	signal( SIGVTALRM, sigalrm );
	//struct itimerval itv = { {0,200000},{1,0} }; // second time: warmup ( cpuclock, etc )
	struct itimerval itv = { {0,50000},{0,500000} }; // second time: warmup ( cpuclock, etc )
	

	//FILE *f1 = fopen("bzero.dat","w");
	FILE *f1 = fopen("bzero.dat3","w");
	setitimer( ITIMER_VIRTUAL, &itv, 0 );
	int values[] = { 1,2,4,8,16,32,64,128 ,512,1024,4000,4096,8000,0 };
	//int values[] = { 1,2,4,8,16,32,64,128 };//,512,1024,4000,4096,8000,0 };

	bench=1;
	// warmup
	while( bench ) 
		count++; 


#if 1

	fprintf(f1,"x \"stosb aligned\" \"sse2+stosb aligned\" \"stosb unaligned\" \"stosb+sse2+stosb unaligned\"\n");
	for ( int a = 1024*1024; a<=BUFFER; a+=(1024*1024)*4 ){
		count = fbench(&bzero, buf, a );
		printf("amd64 align %5d - %lu\n",a,count);
		fprintf( f1, "%d %lu",a, count );
		count = fbench(&bzero_sse2, buf, a );
		printf("sse2 align  %5d - %lu\n",a,count);
		fprintf( f1, " %lu", count );

		count = fbench(&bzero, buf+1, a );
		printf("amd64       %5d - %lu\n",a,count);
		fprintf( f1, " %lu", count );
		count = fbench(&bzero_sse2, buf+1, a );
		printf("sse2        %5d - %lu\n",a,count);
		fprintf( f1, " %lu\n", count );
		
		/*
		This doesn't show anything new..
		if ( !(a%16) ){
			count = fbench(&bzero_sse2, buf, a );
			printf("sse2 aligned  %5d - %lu\n",a,count);
			fprintf( f2, "%d %lu\n",a,count );
		} */

	}

#else

	int *i = values; 
	do {
		count = fbench(&bzero, buf, *i );
		printf("amd64 %5d - %lu\n",*i,count);
		fprintf( f1, "%d %lu", *i, count );
		count = fbench(&bzero_sse2, buf, *i );
		printf("sse2  %5d - %lu\n",*i,count);
		fprintf( f1, " %lu\n", count );

		i++;
	} while ( *i );
#endif

	fclose(f1);
	//fclose(f2);
	return(0);
}
