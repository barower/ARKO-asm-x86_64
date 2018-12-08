	global		drawGraph_body
	section		.text

;				rdi		      rsi	  rdx      rcx
; void drawGraph_body(unsigned char *pPixelBuffer, int width, int height, int A,
; int B, int C, int D, double S);
;  r8     r9    stack    MMX0
drawGraph_body:
	mov		[rdi], DWORD 0xFFFFFFFF
	add		rdi, 4

	ret
