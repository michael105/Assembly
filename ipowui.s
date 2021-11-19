// int ipowui(int x, unsigned int n);
ipowui:
	xor %eax,%eax
	inc %eax
	jmp L1
L0:
	imul %edi,%edi
	nop
L1:
	sar %esi
	jnc L2
	mul %edi
L2:
	jnz L0
 	retq
