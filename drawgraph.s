	global		drawGraph_body
	section		.text

;				rdi		      rsi	  rdx      rcx
; void drawGraph_body(unsigned char *pPixelBuffer, int width, int height, int A,
; int B, int C, int D, double S);
;  r8     r9    stack    MMX0
drawGraph_body:

	;	Draw y axis
	;		Prepare counter
	mov		rax, rdx
	;		*(buf + width/2 * 4), 4 is bytes per pixel
	lea		r10, [rdi + rsi*2]
	mov		[r10], DWORD 0xFFFFFFFF

	;		Decrement counter
	dec		rax
	jz		xaxisinit
yaxisloop:
	lea		r10, [r10, rsi*4]
	mov		[r10], DWORD 0xFFFFFFFF
	dec		rax
	jg		yaxisloop

xaxisinit:

	ret
