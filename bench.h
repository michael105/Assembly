
/*This is for copy and paste,
 essentially, themacro BENCH try's to get the cpu running
 by running an empty loop for half a second,
 afterwards it is counted how often 'src' can be runned
 within one second.
 Sometime compiler optimizations drop in -
 it is eventually neccessary to e.g. make buffers or functions volatile,
 or to copy forth and back.

 Better check the generated assembly, sometimes I've been really
 surprised  of the optimizing tricks of gcc.
 (sort of - why should I run this million times, let's just do as if this 
  would be running, and instead lets try to count up to billions..)
*/


int volatile bench;
void sigalrm(int sig){
	bench=0;
}


#define STBENCH	setitimer( ITIMER_VIRTUAL, &itv, 0 );\
	bench=1;\
	while( bench )\
		asm("nop");\
	bench=1; count = 0;

#define BENCH(src) STBENCH;while(bench){ count++; src; }; printf("Count: %u\n",count);



int main(int argc, char **argv){

	
	bench = 1;
	signal( SIGVTALRM, sigalrm );
	struct itimerval itv = { {1,0},{0,50000} } ;
	unsigned long count = 0;

	char buf[64000];
	char buf2[64000];

	BENCH( memcpy( buf2, buf,30000 ); memcpy( buf, buf2,30000) );


	return(0);
}
