// copy s to d.
// Again, at least with intel core2 upwards,
// rep movsb seems to be quite optimized internally.
// Older processors might have had a severe penalty on string operations,
// now it doesn't seem to pay out tring to vectorize with
// (also 64bit) regular registers.
// using 128 bit mmx registers might pay out, however.
// (showed up being 10 times faster with bzero)
void* memcpy( void*d, const void *s, int n ){
	char *ret = d;
	asm __volatile__("rep movsb" : 
		"+c"(n),"+S"(s), "+D"(d) :: "memory","cc" );
	return(ret);
}
