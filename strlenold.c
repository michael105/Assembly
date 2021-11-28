int strlen(const char*str){
	if ( !str )
		return(0);
	int a;
#ifdef ASM_amd64
	asm( R"(
	xor %%ecx, %%ecx
	dec %%ecx
	xor %%eax,%%eax	
	repne scasb	
	sub %%ecx, %%eax	
	sub $2, %%eax
 )" : "=a"(a), "+D"(str): : "ecx" );
#else
	a=0;
	while ( str[a] != 0 ){
		a++;
	}
#endif
	return (a);
}

