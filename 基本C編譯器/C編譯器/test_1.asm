;************** test_1.asm ****************
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
	PUSH	5
	POP	AX
	MOV	[a], AX
	PUSH	2
	POP	AX
	MOV	[b], AX
	c	DW	7
	MOV	AX, 4C00H
	INT	21H
