// this relies on dynamic arrays (c99)
// move s to d, the areas are allowed to overlap.
// There is an intermediate buffer on the stack 
// If the address of s is above d,
// my tests showed it is possible to directly copy the buffers
// with memcpy (rep movsb)
// if s is below d, and the areas overlap;
// obviously this won't work;
// then memmove is needed to copy to an intermediate buffer.
// (Located on the stack - for big areas above several MB, 
// you might better rule out your own routine.)
void* memmove(void *d, void *s, int n){
	char buf[n];
	memcpy(buf,s,n);
	memcpy(d,buf,n);
	return(d);
}

