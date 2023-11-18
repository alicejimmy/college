;************** test_2.asm ****************
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
	a	DW	'$'
	MOV	word[a], 'a$'
	b	DW	'$'
	MOV	word[b], 'b$'
	c	DW	'$'
	MOV	word[c], 'c$'
	MOV	AX, 4C00H
	INT	21H
