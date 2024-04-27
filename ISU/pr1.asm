%include "rw32-2022.inc"

section .data
    ;x dd 0x09
    ;x dd 0xFF
    x dd -33
    y dd 0x0403020B
    z dd 0

section .text
CMAIN:
	push ebp
	mov ebp,esp
	; add d,s  d=d+s 
    ;   d reg, mem 
    ;   s reg, mem, imm
    ;   reg,reg; reg,mem; reg,imm; mem,reg; mem,imm
    ; sub d,s  d=d-s
    ; adc d,s  d=d+s+CF
    ; sbb d,s  d=d-s-CF

    ; INC d 
    ; DEC d 

    ; scitani dvou velkych cisel pomoci 8-bit registru

    sub al,al
    mov al,[x]
    adc al,[y]
    mov [z], al

    mov al,[x+1]
    adc al,[y+1]
    mov [z+1], al
    
    mov al,[x+2]
    adc al,[y+2]
    mov [z+2], al
    
    mov al,[x+3]
    adc al,[y+3]
    mov [z+3], al

     

    ; muze byt adc na zacatku
    ; jaka je nutna uprava pro praci se znamenkovymi cisli
    
	pop ebp
	ret
