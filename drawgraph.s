	global		drawGraph_body
	section		.text

;				rdi		      rsi	  rdx       xmm0
; void drawGraph_body(unsigned char *pPixelBuffer, int width, int height, double A,
; double B, double C, double D, double S);
;   xmm1      xmm2      xmm3      xmm4
drawGraph_body:
	push rbp
	mov rbp, rsp

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
; | rcx	|				| rdx | (DESTROYED BY MUL)buffer height	|
; | rbp	| (must be preserved)		| rsp |					|
; | rsi	| (input)buffer width		| rdi | (input)buffer base address	|
; | r8	|				| r9  |	(moved from rdx)buffer height	|
; | r10	| WRITE ADDRESS			| r11 |	COUNTER				|
; | r12	| (must be preserved)		| r13 | (must be preserved)		|
; | r14	| (must be preserved)		| r15 | (must be preserved)		|
	;	Draw x axis
xaxisinit:
	;		Prepare counter
	mov		r11, rsi

	;		Save buffer height from being destroyed by mul operation
	mov 		r9, rdx

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
; | rcx	| X OFFSET IN BUFFER 		| rdx | (DESTROYED BY MUL)		|
; | rbp	| (must be preserved)		| rsp |					|
; | rsi	| (input)buffer width		| rdi | (input)buffer base address	|
; | r8	| Y OFFSET IN BUFFER 		| r9  |	(moved from rdx)buffer height	|
; | r10	| WRITE ADDRESS			| r11 |					|
; | r12	| (must be preserved)		| r13 | (must be preserved)		|
; | r14	| (must be preserved)		| r15 | (must be preserved)		|
; | xmm0| (input)A			| xmm1| (input)B			|
; | xmm2| (input)C			| xmm3| (input)D			|
; | xmm4| (input)S			| xmm5| X IN DOUBLE			|
; | xmm6| Y IN DOUBLE			| xmm7|	TEMPORARY REGISTER		|
; | xmm8| TEMPORARY REGISTER		| xmm9|	TEMPORARY REGISTER		|
graph:
	; xmm5 = (double)x
	; x = -1.0
	mov		rcx, -1
	cvtsi2sd	xmm5, rcx

	; start x offset in buffer from 0 (left)
	mov		rcx, 0

graph_iter:
	; y = D
	movsd		xmm6, xmm3

	; y += x*C
	movsd		xmm8, xmm5
	mulsd		xmm8, xmm2
	addsd		xmm6, xmm8

	; y += x*x*B
	movsd		xmm8, xmm1
	mulsd		xmm8, xmm5
	mulsd		xmm8, xmm5
	addsd		xmm6, xmm8

	; y += x*x*x*A
	movsd		xmm8, xmm0
	mulsd		xmm8, xmm5
	mulsd		xmm8, xmm5
	mulsd		xmm8, xmm5
	addsd		xmm6, xmm8

	; convert y in double to y in index
	; y = y + 1.0
	mov		rax, 1
	cvtsi2sd	xmm7, rax
	addsd		xmm6, xmm7

	; y *= (height/2)
	mov		rax, r9
	sar		rax, 1
	cvtsi2sd	xmm7, rax
	mulsd		xmm6, xmm7

	; conversion
	cvtsd2si	r8, xmm6

	; is y out of bounds? If yes, skip putting this pixel
	sub		r8, 0
	jl		calculatex
	mov		rax, r9
	sub		rax, r8
	jle		calculatex

	; calculate address on buffer
	mov		rax, r8
	mul		rsi
	lea		r10, [rdi, rax*4]
	lea		r10, [r10, rcx*4]

	; put pixel on buffer
	mov		[r10], DWORD 0x00FF0000

calculatex:
	; calculate derivative of drawed function
	; derivative = 3*A*x*x + 2*B*x + C;
	; derivative = C
	movsd		xmm7, xmm2

	; derivative += 2*B*x
	movsd		xmm8, xmm5
	mulsd		xmm8, xmm1
	mov		rax, 2
	cvtsi2sd	xmm9, rax
	mulsd		xmm8, xmm9
	addsd		xmm7, xmm8

	; derivative += 3*A*x*x
	movsd		xmm8, xmm0
	mulsd		xmm8, xmm5
	mulsd		xmm8, xmm5
	mov		rax, 3
	cvtsi2sd	xmm9, rax
	mulsd		xmm8, xmm9
	addsd		xmm7, xmm8

	; calculate step
	; step = S / sqrt(1 + derivative*derivative)
	mulsd		xmm7, xmm7
	mov		rax, 1
	cvtsi2sd	xmm8, rax
	addsd		xmm7, xmm8
	sqrtsd		xmm7, xmm7
	movsd		xmm8, xmm4	; prepare S
	divsd		xmm8, xmm7

	; add step to x
	addsd		xmm5, xmm8

	; move calculated x to temporary value
	movsd		xmm8, xmm5

	; calculate new x offset position
	; x = x + 1.0
	mov		rax, 1
	cvtsi2sd	xmm7, rax
	addsd		xmm8, xmm7

	; x *= (width/2)
	mov		rax, rsi
	sar		rax, 1
	cvtsi2sd	xmm7, rax
	mulsd		xmm8, xmm7

	; conversion
	cvtsd2si	rcx, xmm8

	; is x out of bounds? if yes, stop this procedure
	mov		rax, rcx
	sub		rax, rsi
	jle		graph_iter

end:
	mov rsp, rbp
	pop rbp
	ret
