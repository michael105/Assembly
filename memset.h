
// this is maybe 10% slower than a vectorized version,
// but (surprising to me) 5 to 10 times faster than the c version
#define memset(s,c,n) { asm("push %%rdi\npush %%rcx\nrep stosb\npop %%rcx\npop %%rdi\n": :"a"(c), "c"(n), "D"(s): "cc", "memory" ); };


