;************** test_6.asm ****************
;
	ORG	100H
	JMP	_start1
_intstr	DB	'     ','$'
_buf	TIMES 256 DB ' '
	DB 13,10,'$'
%include	"dispstr.mac"
%include	"itostr.mac"
%include	"readstr.mac"
%include	"strtoi.mac"
%include	"newline.mac"
	a	DW	0
	b	DW	0
_start1:
	JMP	_go2
kk:
	JMP	_start2
_start2:
	PUSH	WORD [a]
	PUSH	WORD [b]
	POP	BX
	POP	AX
	SUB	AX, BX
	PUSH	AX
	POP	AX
	MOV	[a], AX
	RET
_go2:
	JMP	_start3
_start3:
	PUSH	6
	POP	AX
	MOV	[a], AX
	PUSH	2
	POP	AX
	MOV	[b], AX
	CALL	kk
	itostr	a, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	itostr	b, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	MOV	AX, 4C00H
	INT	21H
