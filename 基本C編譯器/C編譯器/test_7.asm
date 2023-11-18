;************** test_7.asm ****************
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
	i	DW	1
	j	DW	1
	k	DW	0
_start1:
_go2:
	PUSH	WORD [i]
	PUSH	5
	POP	BX
	POP	AX
	CMP	AX, BX
	JLE	_go3
	JMP	_go4
_go3:
	PUSH	1
	POP	AX
	MOV	[j], AX
_go5:
	PUSH	WORD [j]
	PUSH	5
	POP	BX
	POP	AX
	CMP	AX, BX
	JLE	_go6
	JMP	_go7
_go6:
	PUSH	WORD [i]
	PUSH	WORD [j]
	POP	BX
	POP	AX
	MUL	BX
	PUSH	AX
	POP	AX
	MOV	[k], AX
	MOV	word[_intstr], ' $'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	MOV	word[_intstr], ' $'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	itostr	i, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	MOV	word[_intstr], '*$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	itostr	j, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	MOV	word[_intstr], '=$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	itostr	k, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	PUSH	WORD [j]
	PUSH	1
	POP	BX
	POP	AX
	ADD	AX, BX
	PUSH	AX
	POP	AX
	MOV	[j], AX
	JMP	_go5
_go7:
	newline
	PUSH	WORD [i]
	PUSH	1
	POP	BX
	POP	AX
	ADD	AX, BX
	PUSH	AX
	POP	AX
	MOV	[i], AX
	JMP	_go2
_go4:
	MOV	AX, 4C00H
	INT	21H
