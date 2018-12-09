	global		drawGraph_body
	section		.text

;				rdi		      rsi	  rdx      rcx
; void drawGraph_body(unsigned char *pPixelBuffer, int width, int height, int A,
; int B, int C, int D, double S);
;  r8     r9    stack    MMX0
drawGraph_body:

	;	-----------
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

	;	-----------
	;	Draw x axis
xaxisinit:
	;		Prepare counter
	mov		r11, rsi

	;		Prepare initial address:
	;			(height/2)*width*4
	mov		rax, rsi
	mul		edx
	lea		r10, [rdi + rax*2]
	mov		[r10], DWORD 0xFFFFFFFF

	;		Decrement counter
	dec		r11
	jz		graph
xaxisloop:
	add		r10, 4
	mov		[r10], DWORD 0xFFFFFFFF
	dec		r11
	jg		xaxisloop

graph:


	ret
