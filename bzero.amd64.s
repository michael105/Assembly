/* my experiments showed, at least here,
 there are speed optimizations possible.
 However, rep stosb is fast, and I could measure
 a real performance gain by e.g. vectorization
 only for memory areas beginning with, something about 4kB.
 Then it's on the other hand quite more sensitiv to use sse instructions */

// bzero( void *s, unsigned int n ) 
bzero:
	xor %eax,%eax
	mov %esi,%ecx
	rep stosb 
	retq
