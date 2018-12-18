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
; | rax	|				| rbx |					|
; | rcx	|				| rdx |					|
; | rbp	|				| rsp |					|
; | rsi	|				| rdi |					|
; | r8	|				| r9  |					|
; | r10	|				| r11 |					|
; | r12	|				| r13 |					|
; | r14	|				| r15 |					|
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
; | rax	|				| rbx |					|
; | rcx	|				| rdx |					|
; | rbp	|				| rsp |					|
; | rsi	|				| rdi |					|
; | r8	|				| r9  |					|
; | r10	|				| r11 |					|
; | r12	|				| r13 |					|
; | r14	|				| r15 |					|
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
; | rax	|				| rbx |					|
; | rcx	|				| rdx |					|
; | rbp	|				| rsp |					|
; | rsi	|				| rdi |					|
; | r8	|				| r9  |					|
; | r10	|				| r11 |					|
; | r12	|				| r13 |					|
; | r14	|				| r15 |					|
; | xmm0|				| xmm1|					|
; | xmm2|				| xmm3|					|
; | xmm4|				| xmm5|					|
; | xmm6|				| xmm7|					|
graph:
	; xmm5 = (double)x
	; x = -1.0
	mov		rcx, -1
	cvtsi2sd	xmm5, rcx

	; rcx = x index in buffer is zero
	mov		rcx, 0

	; r8 = CALCULATE y offset here
	; xmm6 = (double)y
	movsd		xmm6, xmm5
	mulsd		xmm6, xmm2
	cvtsd2si	r8, xmm6

	;patrz na kod do osi x
	mov		rax, r8
	mul		rsi
	lea		r10, [rdi, rax*4]
	mov		[r10], DWORD 0x00FF0000
	ret
