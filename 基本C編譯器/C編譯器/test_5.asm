;************** test_5.asm ****************
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
_start1:
	a	DW	6
	b	DW	1
_go2:
	PUSH	WORD [a]
	PUSH	WORD [b]
	POP	BX
	POP	AX
	CMP	AX, BX
	JG	_go3
	JMP	_go4
_go3:
	itostr	a, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	PUSH	WORD [a]
	PUSH	1
	POP	BX
	POP	AX
	SUB	AX, BX
	PUSH	AX
	POP	AX
	MOV	[a], AX
	JMP	_go2
_go4:
	MOV	AX, 4C00H
	INT	21H
