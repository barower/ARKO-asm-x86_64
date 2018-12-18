	global		drawGraph_body
	section		.text

;				rdi		      rsi	  rdx       xmm0
; void drawGraph_body(unsigned char *pPixelBuffer, int width, int height, double A,
; double B, double C, double D, double S);
;   xmm1      xmm2      xmm3      xmm4
drawGraph_body:

;------------------------------------------------------------------------------
; Registers in this section:
;  ----------------------------------------------------------------------------
; | rax	| COUNTER			| rbx |	(must be preserved)		|
; | rcx	|				| rdx | (input)buffer height		|
; | rbp	| (must be preserved)		| rsp |					|
; | rsi	| (input)buffer width		| rdi | (input)buffer base address	|
; | r8	|				| r9  |					|
; | r10	| WRITE ADDRESS			| r11 |					|
; | r12	| (must be preserved)		| r13 | (must be preserved)		|
; | r14	| (must be preserved)		| r15 | (must be preserved)		|
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
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Registers in this section:
;  ----------------------------------------------------------------------------
; | rax	| TEMPORARY REGISTER		| rbx |	(must be preserved)		|
; | rcx	|				| rdx | (input)buffer height		|
; | rbp	| (must be preserved)		| rsp |					|
; | rsi	| (input)buffer width		| rdi | (input)buffer base address	|
; | r8	|				| r9  |					|
; | r10	| WRITE ADDRESS			| r11 |	COUNTER				|
; | r12	| (must be preserved)		| r13 | (must be preserved)		|
; | r14	| (must be preserved)		| r15 | (must be preserved)		|
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
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Registers in this section:
;  ----------------------------------------------------------------------------
; | rax	| TEMPORARY REGISTER		| rbx |	(must be preserved)		|
; | rcx	| X OFFSET IN BUFFER 		| rdx | (input)buffer height		|
; | rbp	| (must be preserved)		| rsp |					|
; | rsi	| (input)buffer width		| rdi | (input)buffer base address	|
; | r8	| Y OFFSET IN BUFFER 		| r9  |					|
; | r10	| WRITE ADDRESS			| r11 |					|
; | r12	| (must be preserved)		| r13 | (must be preserved)		|
; | r14	| (must be preserved)		| r15 | (must be preserved)		|
; | xmm0| (input)A			| xmm1| (input)B			|
; | xmm2| (input)C			| xmm3| (input)D			|
; | xmm4| (input)S			| xmm5| X IN DOUBLE			|
; | xmm6| Y IN DOUBLE			| xmm7|	TEMPORARY REGISTER		|
graph:
	; xmm5 = (double)x
	; x = -1.0
	mov		rcx, -1
	cvtsi2sd	xmm5, rcx

	; start x offset in buffer from 0 (left)
	mov		rcx, 0

	; y = D
	movsd		xmm6, xmm3

	; convert y in double to y in index
	cvtsd2si	r8, xmm6

	; calculate address on buffer
	mov		rax, r8
	mul		rsi
	lea		r10, [rdi, rax*4]
	mov		[r10], DWORD 0x00FF0000
	ret
