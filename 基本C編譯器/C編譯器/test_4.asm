;************** test_4.asm ****************
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
	a	DW	7
	b	DW	2
	c	DW	0
	d	DW	0
_start1:
	PUSH	WORD [a]
	PUSH	WORD [b]
	POP	BX
	POP	AX
	CMP	AX, BX
	JG	_go2
	JMP	_go3
_go2:
	PUSH	WORD [a]
	PUSH	WORD [b]
	POP	BX
	MOV	DX, 0
	POP	AX
	DIV	BX
	PUSH	AX
	POP	AX
	MOV	[c], AX
	PUSH	WORD [a]
	PUSH	WORD [b]
	POP	BX
	MOV	DX, 0
	POP	AX
	DIV	BX
	PUSH	DX
	POP	AX
	MOV	[d], AX
	itostr	c, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	itostr	d, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
_go3:
	MOV	AX, 4C00H
	INT	21H
