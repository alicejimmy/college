;************** test_3.asm ****************
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
_start1:
	i	DW	'$'
	MOV	word[i], 'k$'
	itostr	a, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	MOV	DX, i
	MOV	AH, 09H
	INT	21H
	newline
	MOV	AX, 4C00H
	INT	21H
